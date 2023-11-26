if (mg_http_match_uri(hm, "/linegames/getnid")) {
	log = false;
	nlohmann::json getnidJson = {
		{"isSuccess", true},
		{"data", {
			{"gnidStatus", ""},
			{"blockStatus", ""},
			{"countryCreated", "US"},
			{"nid", 1},
			{"gnid", "getnid_test_gnid"},
		}},
	};
	LOGI("toro_webserver: Request to getnid");
	mg_http_reply(c, 200, "", "%s",	getnidJson.dump().c_str());
}