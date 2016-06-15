#include <nan.h>
#include "tofile.h"
#include "tojson.h"

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

NAN_MODULE_INIT(InitAll) {
  Set(target, New<String>("convertToFile").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(ConvertToFile)).ToLocalChecked());

  Set(target, New<String>("convertFile").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(ConvertToFile)).ToLocalChecked());

  Set(target, New<String>("convertToJson").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(ConvertToJson)).ToLocalChecked());
}

NODE_MODULE(xml2json, InitAll)
