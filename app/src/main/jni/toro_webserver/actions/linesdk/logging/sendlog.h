namespace LineSDK
{
	namespace Logging
	{
		namespace SendLog
		{
			void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
			{
				if (mg_http_match_uri(hm, "/linegames_log/sendlog")) {
					torowebserver_log = false;
					LOGI("toro_webserver: Request to sendlog");
					mg_http_reply(c, 200, "", "%s",	defaultSuccessJson.dump().c_str());
				}
			}
		}
	}
}