import sys
import time
import quickfix as fix

class Application(fix.Application):
    	def onCreate(self, sessionID): return
    	def onLogon(self, sessionID): return
    	def onLogout(self, sessionID): return
    	def toAdmin(self, sessionID, message): return
    	def fromAdmin(self, sessionID, message): return
    	def toApp(self, sessionID, message): return
    	def fromApp(self, message, sessionID): return


try:
    file = sys.argv[1]
    settings = fix.SessionSettings( file )
	application = Application()
	storeFactory = fix.FileStoreFactory( settings )
	logFactory = fix.ScreenLogFactory( settings )
    initiator = fix.SocketInitiator( application, storeFactory, settings, logFactory )
    # initiator.start() ?

    while 1: # listen up the tradebook for incoming messages
        time.sleep(1)

except (fix.ConfigError, fix.RuntimeError) as e:
    print(e)
