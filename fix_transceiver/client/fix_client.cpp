#include "fixclient_session.hpp"
#include <sessionwrapper.hpp>

// Client Session Main
int main(int argc, char const *argv[]) {

	using namespace FIX8;

	ClientSession<fixclient_session_client>::ClientSession_ptr mc;
	mc = new ClientSession<fixclient_session_client>(CLIENTWRAP::ctx(), 
	    "fix_session_client.xml", "fss_test");
	mc->start(true);

	return 0 ;
}

// Closest thing to compiling:
// g++ fix_client.cpp -I/usr/include/fix8 -lfix8 -std=c++11

