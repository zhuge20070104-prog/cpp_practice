#ifndef ObjLoopHandler_INCLUDED
#define ObjLoopHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class ObjLoopHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // ObjLoopHandler_INCLUDED
