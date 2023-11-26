if (mg_http_match_uri(hm, "//api/v1/login/guest/getLoginToken")) {
	log = false;
	nlohmann::json loginTokenJson = {
		{"success", true},
		{"data", {
			{"newGnidYn", "Y"},
			{"gnidHash", "DEADBEEF"},
			{"pfSessionToken", "this_is_a_test_pfsessiontoken"},
			{"countryCreated", "US"},
			{"policyAgreeInfo", {
				{"termsAgreeUnixTS", 0},
				{"privacyAgreeUnixTS", 0},
				{"ageCheckCompletedUnixTS", 0},
				{"privacyTransferAgreeUnixTS", 0},
				{"nightPushAgreeYn", "Y"},
				{"nightPushAgreeUnixTS", 0},
				{"pushAgreeYn", "Y"},
				{"pushAgreeUnixTS", 0},
				{"needAgreePushYn", "N"},
				{"needReAgreePolicyYn", "N"},
			}},
			{"linkedPlatformIdList", {
				99
			}},
		}},
	};
	LOGI("toro_webserver: Request to getLoginToken (guest login)");
	mg_http_reply(c, 200, "", "%s",	loginTokenJson.dump().c_str());
}