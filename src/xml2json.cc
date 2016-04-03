#include <node.h>
#include <v8.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "xml2json.hpp"

using namespace v8;
using namespace std;

struct Baton
{
    uv_work_t request;
    Persistent<Function> callback;

    char        inputFile[256];
    char        outputFile[256];
};

static void Work(uv_work_t *req)
{
    Baton *baton = static_cast<Baton *>(req->data);

	fstream _fileXml(baton->inputFile);
  	ofstream _fileJson;

  	string _json_str;

  	if(_fileXml.is_open()) {

  	  	ostringstream oss;
  	  	oss << _fileXml.rdbuf();

  	  	const auto _json_str = xml2json( oss.str().data() );


  	  	_fileJson.open(baton->outputFile, fstream::out);
  	  	if(_fileJson.is_open()) {

  	  	    _fileJson << _json_str << endl;
  	  	    _fileJson.close();
  	  	}

  	  	_fileXml.close();
  	}
}

static void After(uv_work_t *req,int status)
{
    Baton *baton = static_cast<Baton *>(req->data);

    Handle<Value> argv[] =
        {
            Handle<Value>(String::New(baton->inputFile)),
            Handle<Value>(String::New(baton->outputFile))
        };

    baton->callback->Call(Context::GetCurrent()->Global(),2,argv);

    baton->callback.Dispose();
    delete baton;
}

Handle<Value> ConvertAsync(const Arguments &args)
{
	HandleScope scope;

	if (args.Length() < 3) {
    	ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
	}

    Baton *baton = new Baton;

    Handle<Function> cb = Handle<Function>::Cast(args[2]);

    baton->request.data = baton;

    String::Utf8Value input(args[0]);
    strncpy(baton->inputFile, *input, sizeof(baton->inputFile));
    String::Utf8Value output(args[1]);
    strncpy(baton->outputFile, *output, sizeof(baton->outputFile));

    baton->callback = Persistent<Function>::New(cb);
    uv_queue_work(uv_default_loop(), &baton->request, Work, After);

    return Undefined();
}

void init(Handle<Object> exports) {
	exports->Set(
        String::NewSymbol("convertFile"),
		FunctionTemplate::New(ConvertAsync)->GetFunction()
  	);
}

NODE_MODULE(xml2json, init)
