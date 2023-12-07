namespace NeptuneAPI
{
	namespace Auth
	{
		namespace Generic
		{
			namespace RegisterPushToken
			{
				nlohmann::json registerPushJson = {
					{"isSuccess", true},
					//{"msg", "haii :3"},
				};
				void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
				{
					if (mg_http_match_uri(hm, "//api/v1/push/token/register/forClient")) {
						torowebserver_log = false;
						
						LOGI("toro_webserver: Request to register token");
						mg_http_reply(c, 200, "", "%s",	registerPushJson.dump().c_str());
					}
				}
			}
		}
	}
}