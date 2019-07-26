#include <napi.h>
#include <algorithm>
#include <ctime>

#define MAX_STARTUP_DELAY 1

namespace Addon {
	time_t startup;

	Napi::String getKey(const Napi::CallbackInfo &info) {
		Napi::Env env = info.Env();
		time_t now = time(0);
		if (difftime(now, startup) <= MAX_STARTUP_DELAY) {
			return Napi::String::New(env, PSK);
		} else {
			return Napi::String::New(env, "Expired");
		}
	}

	Napi::String getSalt(const Napi::CallbackInfo &info) {
		Napi::Env env = info.Env();
		time_t now = time(0);
		if (difftime(now, startup) <= MAX_STARTUP_DELAY) {
			return Napi::String::New(env, PSKSALT);
		} else {
			return Napi::String::New(env, "Expired");
		}
	}

	Napi::Object Init(Napi::Env env, Napi::Object exports) {
		exports.Set(Napi::String::New(env, "getKey"), Napi::Function::New(env, getKey));
		exports.Set(Napi::String::New(env, "getSalt"), Napi::Function::New(env, getSalt));
		startup = time(0);
		return exports;
	}

	NODE_API_MODULE(addon, Init)
}  // namespace Addon