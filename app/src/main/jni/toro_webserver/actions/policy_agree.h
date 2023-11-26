if (mg_http_match_uri(hm, "//api/policy/v2/nid/agree/request/byPfSessionToken/forClient")) {
	log = false;
	nlohmann::json policyAgreeJson = {
		{"success", true},
	};
	LOGI("toro_webserver: Request to policy agree (guest login)");
	mg_http_reply(c, 200, "", "%s",	policyAgreeJson.dump().c_str());
}