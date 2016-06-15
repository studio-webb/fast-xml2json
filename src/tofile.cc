#include <nan.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tofile.h"  // NOLINT(build/include)
//#include "convert.h"  // NOLINT(build/include)
#include "include/xml2json.h"

using v8::Function;
using v8::Local;
using v8::Number;
using v8::String;
using v8::Value;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;
using Nan::NewBuffer;

std::string ConvertFile (std::string inputFile, std::string outputFile) {

	std::fstream xmlFile(inputFile.c_str());
	std::ofstream jsonFile;

	std::string jsonString;

	if(xmlFile.is_open()) {

	  	std::ostringstream oss;
	  	oss << xmlFile.rdbuf();

	  	jsonString = xml2json( oss.str().data() );

	  	jsonFile.open(outputFile.c_str(), std::fstream::out);
	  	if(jsonFile.is_open()) {

	  	    jsonFile << jsonString << std::endl;
	  	    jsonFile.close();
	  	}

	  	xmlFile.close();
	}

	return jsonString;
}

class ToFile : public AsyncWorker {
 public:
  ToFile(Callback *callback, std::string inputFile, std::string outputFile)
    : AsyncWorker(callback), inputFile(inputFile), outputFile(outputFile)  {}
  ~ToFile() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
    result = ConvertFile(inputFile, outputFile);
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    HandleScope scope;

    v8::Local<v8::Object> res = Nan::NewBuffer(result.length()).ToLocalChecked();
    memcpy(node::Buffer::Data(res), result.c_str(), result.length());

    Local<Value> argv[] = {
        Null()
      , res
    };

    callback->Call(2, argv);
  }

 private:
 	std::string inputFile;
 	std::string outputFile;
  	std::string result;
};

// Asynchronous access to the `ConvertToFile()` function
NAN_METHOD(ConvertToFile) {

	String::Utf8Value input(info[0]);
	std::string inputFile = std::string(*input);

	String::Utf8Value output(info[1]);
	std::string outputFile = std::string(*output);

	assert(info[2]->IsFunction());

	Callback *callback = new Callback(info[2].As<Function>());

	AsyncQueueWorker(new ToFile(callback, inputFile, outputFile));
}