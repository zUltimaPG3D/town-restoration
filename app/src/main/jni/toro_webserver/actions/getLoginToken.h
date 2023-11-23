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