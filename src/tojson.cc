#include <nan.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tojson.h"  // NOLINT(build/include)
#include "xml2json.h"

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

std::string Convert (std::string input) {

	std::fstream xmlFile(input.c_str());
	std::string jsonString;

	if(xmlFile.is_open()) {

	  	std::ostringstream oss;
	  	oss << xmlFile.rdbuf();

	  	jsonString = xml2json( oss.str().data() );

	  	xmlFile.close();
	}

	return jsonString;
}

class ToJson : public AsyncWorker {
 public:
  ToJson(Callback *callback, std::string input)
    : AsyncWorker(callback), input(input) {}
  ~ToJson() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
    result = Convert(input);
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    HandleScope scope;

    v8::Local<v8::Object> res = Nan::NewBuffer(result.length()).ToLocalChecked();
    memcpy(node::Buffer::Data(res), result.c_str(), result.length());

    Local<Value> argv[] = {
        Null(), 
        res
    };

    callback->Call(2, argv);
  }

 private:
  	std::string input;
  	std::string result;
};

// Asynchronous access to the `ConvertAsync()` function
NAN_METHOD(ConvertToJson) {

  String::Utf8Value _input(info[0]->ToString());
  std::string input = std::string(*_input);

  assert(info[1]->IsFunction());

  Callback *callback = new Callback(info[1].As<Function>());

  AsyncQueueWorker(new ToJson(callback, input));
}