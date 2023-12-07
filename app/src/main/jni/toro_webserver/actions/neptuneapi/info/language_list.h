namespace NeptuneAPI
{
    namespace Language
    {
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
        void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
        {
            if (mg_http_match_uri(hm, "//api/langCulture/game/useList")) {
				torowebserver_log = false;
				LOGI("toro_webserver: Request to useList (langCulture)");
				
				mg_http_reply(c, 200, "", "%s",	successJson.dump().c_str());
			}
        }
    }
}