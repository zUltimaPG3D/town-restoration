namespace NeptuneAPI
{
    namespace Language
    {
        nlohmann::json successJson = {
			{"isSuccess", true},
			{"data", {
				{
					{"langCulture", "en_US"},
					{"name", "영어(미국)"},
					{"displayName", "English"},
				},
				{
					{"langCulture", "ko_KR"},
					{"name", "한국어(대한민국)"},
					{"displayName", "한국어"},
				},
				{
					{"langCulture", "ja_JP"},
					{"name", "일본어(일본)"},
					{"displayName", "日本語"},
				},
				{
					{"langCulture", "zh_CN"},
					{"name", "중국어 간체(중국)"},
					{"displayName", "中文(简体)"},
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