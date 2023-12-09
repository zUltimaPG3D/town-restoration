#include "../mongoose/mongoose.h"
#include <thread>
#include "../json.hpp"

bool torowebserver_log = true;

#define GAME_STATUS "OFFLINE"
#define MAINTENANCE_MSG ""

#include "actions/default_success.h"

#include "../SWUTS/services/adjust.h"

std::thread webserver_thread;

#pragma region Server Includes
#include "actions/neptuneapi/info/getClientVersionInfo.h"
#include "actions/neptuneapi/info/gameServer_list.h"
#include "actions/neptuneapi/info/language_list.h"

#include "actions/neptuneapi/login/getLoginToken.h"
#include "actions/neptuneapi/login/policy_agree.h"
#include "actions/linesdk/auth/getnid.h"
#include "actions/neptuneapi/login/register_push.h"

#include "actions/linesdk/logging/sendlog.h"

#include "actions/custom/tos.h"
#pragma endregion

// #define SERVER_DEBUG

static void toro_webserver_event(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;

		torowebserver_log = true;

		////
		//// (Neptune) Game info endpoints
		////
		{
			NeptuneAPI::Versioning::Listen(c, hm);
			NeptuneAPI::Servers::Listen(c, hm);
			NeptuneAPI::Language::Listen(c, hm);
		}
		
		////
		//// (Neptune) Login endpoints
		////
		{
			NeptuneAPI::Auth::Guest::LoginToken::Listen(c, hm);
			NeptuneAPI::Auth::Generic::Policy::Listen(c, hm);
			LineSDK::Auth::GetNID::Listen(c, hm);
			NeptuneAPI::Auth::Generic::RegisterPushToken::Listen(c, hm);	
		}

		////
		//// Analytics replacement endpoint listeners
		////
		{
			SWUTS::Adjust::listen_adjustsdk(c, hm);
		}

		////
		//// Misc. endpoints
		////
		{
			LineSDK::Logging::SendLog::Listen(c, hm);
			CustomEndpoints::TOS::Listen(c, hm);
		}

		#ifdef SERVER_DEBUG
		torowebserver_log = true;
		#endif

		if (torowebserver_log)
		{
			LOGI("toro_webserver: Generic request to endpoint %s", hm->uri.ptr);
		}
	}
}

void toro_webserver_log(char ch, void *param) {
	// stub
}

void toro_webserver_thread()
{
	LOGI("toro_webserver: Webserver thread started (and not listening)");
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);
	// mg_log_set_fn(toro_webserver_log, param);
	mg_log_set(MG_LL_DEBUG);
	mg_http_listen(&mgr, HTTP_SERVER_URL, toro_webserver_event, NULL);
	LOGI("toro_webserver: Webserver thread started (and listening)");
	for (;;) mg_mgr_poll(&mgr, 1000);
}

void init_toro_webserver()
{
	LOGI("toro_webserver: Starting webserver thread");
	webserver_thread = std::thread(&toro_webserver_thread);
	webserver_thread.detach();
}