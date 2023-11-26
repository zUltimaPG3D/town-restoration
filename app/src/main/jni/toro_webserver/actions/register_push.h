if (mg_http_match_uri(hm, "//api/v1/push/token/register/forClient")) {
	log = false;
	nlohmann::json registerPushJson = {
		{"isSuccess", true},
		//{"msg", "haii :3"},
	};
	LOGI("toro_webserver: Request to register token");
	mg_http_reply(c, 200, "", "%s",	registerPushJson.dump().c_str());
}