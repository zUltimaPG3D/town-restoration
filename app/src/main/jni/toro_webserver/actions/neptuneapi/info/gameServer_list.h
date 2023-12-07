namespace NeptuneAPI
{
	namespace Servers
	{
		nlohmann::json gameServer_listJson = {
			{"isSuccess", true},
			{"data", {
				{
					{"gameServerId", "DEADBEEF"},
					{"gameServerNm", "DEADBEEF"},
				},
			}},
		};
		void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
		{
			if (mg_http_match_uri(hm, "//api/gameServer/list")) {
				torowebserver_log = false;
				
				LOGI("toro_webserver: Request to list (gameServer)");
				mg_http_reply(c, 200, "", "%s",	gameServer_listJson.dump().c_str());
			}
		}
	}
}