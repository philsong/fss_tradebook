// Server Session Main
int main(int argc, char const *argv[]) {

	ServerSession<fixserver_session_server>::ServerSession_ptr ms;
	ms = new ServerSession<fixserver_session_server>(SERVERWRAP::ctx(), "fix_session_server.xml", "fss_test");
	 
	while (!term_received) {
	    if (!ms->poll())
	        continue;
	    SessionInstance<myfix_session_server>::SessionInstance_ptr inst(new SessionInstance<myfix_session_server>(*ms));
	    inst->start(true);
	    inst->stop();
	}	

	return 0;
}