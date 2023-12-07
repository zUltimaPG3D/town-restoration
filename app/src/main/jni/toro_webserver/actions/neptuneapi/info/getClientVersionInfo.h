namespace NeptuneAPI
{
	namespace Versioning
	{
		nlohmann::json clientVersionInfoJson = {
			{"isSuccess", true},
			{"data", {
				{"client_version_status", "ONLINE"}, // 😁
				{"server_addr", "http://localhost:15151/"},
				{"patch_addr", "http://localhost:15151/"},
				{"countryInfo", {
					{"countryCd", "US"},
					{"gdprTargetYn", "N"},
				}},
				{"countryTermsInfos", {
					{
						{"cd", "TERMS_OF_SERVICES"},
						{"required", true},
						{"url", "https://localhost:15151/tos"},
					},
					{
						{"cd", "PRIVACY_POLICY"},
						{"required", true},
						{"url", "https://localhost:15151/tos"},
					},
					{
						{"cd", "PRIVACY_POLICY_FULLTEXT"},
						{"required", true},
						{"url", "https://localhost:15151/tos"},
					},
					{
						{"cd", "USE_OF_PUSH_NOTIFICATIONS"},
						{"required", false},
						{"url", "https://localhost:15151/tos"},
					},
				}},
				{"maintenance_msg", ""},
				{"guest_mode_on_yn", "Y"},
				{"applied_white_yn", "N"},
				{"customValue", ""},
				{"out_link_url", ""},
			}},
		};

		void Listen(struct mg_connection*& c, struct mg_http_message*& hm) {
			if (mg_http_match_uri(hm, "//api/api_version/getClientVersionInfo")) {
				torowebserver_log = false;
				LOGI("toro_webserver: Request to getClientVersionInfo");
				mg_http_reply(c, 200, "", "%s",	clientVersionInfoJson.dump().c_str());
			}
		}
	}
}