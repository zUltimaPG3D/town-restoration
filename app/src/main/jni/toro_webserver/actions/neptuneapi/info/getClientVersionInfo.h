namespace NeptuneAPI
{
	namespace Versioning
	{
		std::string tos_url = std::string(HTTP_SERVER_URL) + "tos";
		nlohmann::json clientVersionInfoJson = {
			{"isSuccess", true},
			{"data", {
				{"client_version_status", GAME_STATUS},
				{"server_addr", HTTP_SERVER_URL},
				{"patch_addr", HTTP_SERVER_URL},
				{"countryInfo", {
					{"countryCd", "US"},
					{"gdprTargetYn", "N"},
				}},
				{"countryTermsInfos", {
					{
						{"cd", "TERMS_OF_SERVICES"},
						{"required", true},
						{"url", tos_url},
					},
					{
						{"cd", "PRIVACY_POLICY"},
						{"required", true},
						{"url", tos_url},
					},
					{
						{"cd", "PRIVACY_POLICY_FULLTEXT"},
						{"required", true},
						{"url", tos_url},
					},
					{
						{"cd", "USE_OF_PUSH_NOTIFICATIONS"},
						{"required", false},
						{"url", tos_url},
					},
				}},
				{"maintenance_msg", MAINTENANCE_MSG},
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