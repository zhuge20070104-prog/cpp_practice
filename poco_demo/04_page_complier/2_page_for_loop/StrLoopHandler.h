#ifndef StrLoopHandler_INCLUDED
#define StrLoopHandler_INCLUDED


#include "Poco/Net/HTTPRequestHandler.h"


class StrLoopHandler: public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};


#endif // StrLoopHandler_INCLUDED
