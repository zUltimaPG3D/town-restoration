namespace LineSDK
{
	namespace Auth
	{
		namespace GetNID
		{
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
			void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
			{
				if (mg_http_match_uri(hm, "/linegames/getnid")) {
					torowebserver_log = false;
					
					LOGI("toro_webserver: Request to getnid");
					mg_http_reply(c, 200, "", "%s",	getnidJson.dump().c_str());
				}
			}
		}
	}
}