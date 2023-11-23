#include "../mongoose/mongoose.h"
#include <thread>
#include "../json.hpp"

#include "actions/getClientVersionInfo.h"
#include "actions/gameServer_list.h"
#include "actions/getLoginToken.h"
#include "actions/policy_agree.h"
#include "actions/tos.h"
#include "actions/getnid.h"
#include "actions/register_push.h"
#include "actions/default_success.h"

std::thread webserver_thread;

static void toro_webserver_event(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_HTTP_MSG) {
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;

		if (mg_http_match_uri(hm, "//api/api_version/getClientVersionInfo")) {
			LOGI("toro_webserver: Request to getClientVersionInfo");
			mg_http_reply(c, 200, "", "%s",	clientVersionInfoJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "//api/langCulture/game/useList")) {
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
		} else if (mg_http_match_uri(hm, "//api/gameServer/list")) {
			LOGI("toro_webserver: Request to list (gameServer)");
			mg_http_reply(c, 200, "", "%s",	gameServer_listJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "//api/v1/login/guest/getLoginToken")) {
			LOGI("toro_webserver: Request to getLoginToken (guest login)");
			mg_http_reply(c, 200, "", "%s",	loginTokenJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "//api/policy/v2/nid/agree/request/byPfSessionToken/forClient")) {
			LOGI("toro_webserver: Request to policy agree (guest login)");
			mg_http_reply(c, 200, "", "%s",	policyAgreeJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "/linegames/getnid")) {
			LOGI("toro_webserver: Request to getnid");
			mg_http_reply(c, 200, "", "%s",	getnidJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "/linegames_log/sendlog")) {
			LOGI("toro_webserver: Request to sendlog");
			mg_http_reply(c, 200, "", "%s",	defaultSuccessJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "//api/v1/push/token/register/forClient")) {
			LOGI("toro_webserver: Request to register token");
			mg_http_reply(c, 200, "", "%s",	registerPushJson.dump().c_str());
		} else if (mg_http_match_uri(hm, "/tos")) {
			LOGI("toro_webserver: Request to fake TOS");
			mg_http_reply(c, 200, "", "%s", tosContent.c_str());
		} else {
			LOGI("toro_webserver: Request to undefined endpoint %s", hm->uri.ptr);
		}
	}
}

void toro_webserver_thread()
{
	LOGI("toro_webserver: Webserver thread started (and not listening)");
	struct mg_mgr mgr;
	mg_mgr_init(&mgr);
	mg_log_set(MG_LL_DEBUG);
	mg_http_listen(&mgr, "http://localhost:15151", toro_webserver_event, NULL);
	LOGI("toro_webserver: Webserver thread started (and listening)");
	for (;;) mg_mgr_poll(&mgr, 1000);
}

void init_toro_webserver()
{
	LOGI("toro_webserver: Starting webserver thread");
	webserver_thread = std::thread(&toro_webserver_thread);
	webserver_thread.detach();
}