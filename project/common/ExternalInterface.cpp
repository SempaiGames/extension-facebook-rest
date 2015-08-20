#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif

#include <hx/CFFI.h>
#include <hxcpp.h>

#include <string>
#include <vector>

#include <Facebook.h>

#define safe_alloc_string(a) (alloc_string(a!=NULL ? a : ""))

AutoGCRoot* _onTokenChange;
AutoGCRoot* _onLoginSuccessCallback;
AutoGCRoot* _onLoginCancelCallback;
AutoGCRoot* _onLoginErrorCallback;

void extension_facebook::onTokenChange(const char *token) {
	if (_onTokenChange==NULL) {
		return;
	}
	val_call1(_onTokenChange->get(), safe_alloc_string(token));
}

void extension_facebook::onLoginSuccessCallback() {
	if (_onLoginSuccessCallback==NULL) {
		return;
	}
	val_call0(_onLoginSuccessCallback->get());
}

void extension_facebook::onLoginCancelCallback() {
	if (_onLoginCancelCallback==NULL) {
		return;
	}
	val_call0(_onLoginCancelCallback->get());
}

void extension_facebook::onLoginErrorCallback(const char *error) {
	if (_onLoginErrorCallback==NULL) {
		return;
	}
	val_call1(_onLoginErrorCallback->get(), safe_alloc_string(error));
}

static value extension_facebook_init(value onTokenChange) {
	_onTokenChange = new AutoGCRoot(onTokenChange);
	extension_facebook::init();
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_init, 1);

static value extension_facebook_logOut() {
	extension_facebook::logOut();
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_logOut, 1);

static value extension_facebook_logInWithPublishPermissions(value permissions) {
	int n = 0;
	if (permissions!=NULL) {
		n = val_array_size(permissions);
	}
	std::vector<std::string> stlPermissions;
	for (int i=0;i<n;++i) {
		std::string str(val_string(val_array_i(permissions, i)));
		stlPermissions.push_back(str);
	}
	extension_facebook::logInWithPublishPermissions(stlPermissions);
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_logInWithPublishPermissions, 1);

static value extension_facebook_logInWithReadPermissions(value permissions) {
	int n = 0;
	if (permissions!=NULL) {
		n = val_array_size(permissions);
	}
	std::vector<std::string> stlPermissions;
	for (int i=0;i<n;++i) {
		std::string str(val_string(val_array_i(permissions, i)));
		stlPermissions.push_back(str);
	}
	extension_facebook::logInWithReadPermissions(stlPermissions);
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_logInWithReadPermissions, 1);

static value extension_facebook_setOnLoginSuccessCallback(value fun) {
	_onLoginSuccessCallback = new AutoGCRoot(fun);
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_setOnLoginSuccessCallback, 1);

static value extension_facebook_setOnLoginCancelCallback(value fun) {
	_onLoginCancelCallback = new AutoGCRoot(fun);
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_setOnLoginCancelCallback, 1);

static value extension_facebook_setOnLoginErrorCallback(value fun) {
	_onLoginErrorCallback = new AutoGCRoot(fun);
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_setOnLoginErrorCallback, 1);

static value extension_facebook_appInvite(value appLinkUrl, value previewImageUrl) {
	extension_facebook::appInvite(
		appLinkUrl==NULL ? "" : std::string(val_string(appLinkUrl)),
		previewImageUrl==NULL ? "" : std::string(val_string(previewImageUrl))
	);
	return alloc_null();
}
DEFINE_PRIM(extension_facebook_appInvite, 2);

static value extension_facebook_shareLink(
	value contentURL,
	value contentTitle,
	value imageURL,
	value contentDescription) {

	extension_facebook::shareLink(
		contentURL==NULL ? "" : std::string(val_string(contentURL)),
		contentTitle==NULL ? "" : std::string(val_string(contentTitle)),
		imageURL==NULL ? "" : std::string(val_string(imageURL)),
		contentDescription==NULL ? "" : std::string(val_string(contentDescription))
	);

	return alloc_null();

}
DEFINE_PRIM(extension_facebook_shareLink, 4);

extern "C" void extension_facebook_main () {
	val_int(0); // Fix Neko init
}
DEFINE_ENTRY_POINT (extension_facebook_main);

extern "C" int extension_facebook_register_prims () {
	return 0;
}