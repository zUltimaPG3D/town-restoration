void listen_adjustsdk(struct mg_connection*& c, struct mg_http_message*& hm)
{
    if (mg_http_match_uri(hm, "/test")) {
		LOGI("SWUTS(Adjust): Request to test");
		mg_http_reply(c, 200, "", "");
	}
}