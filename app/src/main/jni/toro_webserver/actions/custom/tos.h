namespace CustomEndpoints
{
	namespace TOS
	{
		void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
		{
			if (mg_http_match_uri(hm, "/tos")) {
				torowebserver_log = false;
				std::string tosContent = "<h1>hai</h1>";
				LOGI("toro_webserver: Request to fake TOS");
				mg_http_reply(c, 200, "", "%s", tosContent.c_str());
			}
		}
	}
}