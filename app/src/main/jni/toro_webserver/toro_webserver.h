#include "../mongoose/mongoose.h"
#include <thread>
#include "../json.hpp"

#include "actions/default_success.h"

#include "../SWUTS/services/adjust.h"

std::thread webserver_thread;

// #define SERVER_DEBUG

static void toro_webserver_event(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;

		bool log = true;

		////
		//// (Neptune) Game info endpoints
		////
		{
			#include "actions/getClientVersionInfo.h"

			if (mg_http_match_uri(hm, "//api/langCulture/game/useList")) {
				log = false;
				LOGI("toro_webserver: Request to useList (langCulture)");
				nlohmann::json successJson = {
					{"isSuccess", true},
					{"data", {
						{
							{"langCulture", "en-US"},
							{"name", "English (en-US)"},
							{"displayName", "English (en-US)"},
						},
					}},
				};
				mg_http_reply(c, 200, "", "%s",	successJson.dump().c_str());
			}

			#include "actions/gameServer_list.h" 
		}
		
		////
		//// (Neptune) Login endpoints
		////
		{
			#include "actions/getLoginToken.h"
			
			#include "actions/policy_agree.h"

			#include "actions/getnid.h"

			#include "actions/register_push.h"
		}

		////
		//// Analytics replacement endpoint listeners
		////
		{
			listen_adjustsdk(c, hm);
		}

		////
		//// Misc. endpoints
		////
		{
			if (mg_http_match_uri(hm, "/linegames_log/sendlog")) {
				log = false;
				LOGI("toro_webserver: Request to sendlog");
				mg_http_reply(c, 200, "", "%s",	defaultSuccessJson.dump().c_str());
			}
			
			#include "actions/tos.h"
		}

		#ifdef SERVER_DEBUG
		log = true;
		#endif

		if (log)
		{
			LOGI("toro_webserver: Generic request to endpoint %s", hm->uri.ptr);
		}
	}
}

void toro_webserver_thread()
{
	LOGI("toro_webserver: Webserver thread started (and not listening)");
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);
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