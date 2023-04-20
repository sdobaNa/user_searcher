#pragma comment(lib, "netapi32.lib")

#include <napi.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <lmaccess.h>
#include <typeinfo>
#include <stdlib.h>
#include <codecvt>

using namespace std;

Napi::Boolean ValidateUser(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  string name;
  boolean flag = false;

  USER_INFO_0* buffer;
  DWORD entries;
  DWORD total_entries;
  DWORD resume_handle = 0;

  name = info[0].As<Napi::String>().Utf8Value();

  NET_API_STATUS users = NetUserEnum(
    NULL, 0, 0,
    (BYTE**)&buffer,
    4096,
    &entries,
    &total_entries,
    &resume_handle
  );

  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

  for (unsigned i = 0; i < entries; i++){
    std::wstring ws(buffer[i].usri0_name);
    if(name == converter.to_bytes( ws )){
      flag = true;
      break;
    }
  }

  return Napi::Boolean::New(env, flag);
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "ValidateUser"), Napi::Function::New(env, ValidateUser));
    return exports;
};

NODE_API_MODULE(validate_user, init);