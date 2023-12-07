namespace NeptuneAPI
{
	namespace Auth
	{
		namespace Generic
		{
			namespace Policy
			{
				nlohmann::json policyAgreeJson = {
					{"success", true},
				};
				void Listen(struct mg_connection*& c, struct mg_http_message*& hm)
				{
					if (mg_http_match_uri(hm, "//api/policy/v2/nid/agree/request/byPfSessionToken/forClient")) {
						torowebserver_log = false;
						
						LOGI("toro_webserver: Request to policy agree (guest login)");
						mg_http_reply(c, 200, "", "%s",	policyAgreeJson.dump().c_str());
					}
				}
			}
		}
	}
}