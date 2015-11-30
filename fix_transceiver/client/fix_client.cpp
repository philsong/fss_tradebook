// Client Session Main
int main(int argc, char const *argv[]) {

	ClientSession<fixclient_session_client>::ClientSession_ptr mc;
	mc = new ClientSession<fixclient_session_client>(CLIENTWRAP::ctx(), 
	    "fix_session_client.xml", "fss_test");
	mc->start(true);

	return 0 ;
}
