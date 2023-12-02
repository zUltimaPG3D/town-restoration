if (mg_http_match_uri(hm, "//api/gameServer/list")) {
	log = false;
	nlohmann::json gameServer_listJson = {
		{"isSuccess", true},
		{"data", {
			{
				{"gameServerId", "DEADBEEF"},
				{"gameServerNm", "DEADBEEF"},
			},
		}},
	};
	LOGI("toro_webserver: Request to list (gameServer)");
	mg_http_reply(c, 200, "", "%s",	gameServer_listJson.dump().c_str());
}