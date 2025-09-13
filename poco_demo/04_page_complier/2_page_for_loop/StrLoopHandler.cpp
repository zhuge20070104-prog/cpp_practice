#include "StrLoopHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#line 2 "/cpp_practice/poco_demo/04_page_complier/2_page_for_loop/str_loop_p.cpsp"

    #include <string>
    #include <vector>


using namespace std::string_literals;


void StrLoopHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html"s);

	Poco::Net::HTMLForm form(request, request.stream());
	std::ostream& responseStream = response.send();
	responseStream << "\n";
#line 7 "/cpp_practice/poco_demo/04_page_complier/2_page_for_loop/str_loop_p.cpsp"

    std::vector<std::string> names {"ZhangSan", "Lisi", "WangWu", "ZhaoLiu"};
	responseStream << "\n";
	responseStream << "<html>\n";
	responseStream << "<head>\n";
	responseStream << "<title>StrLoopHandler powered by POCO C++ Libraries and PageCompiler</title>\n";
	responseStream << "<meta http-equiv=\"refresh\" content=\"1\">\n";
	responseStream << "</head>\n";
	responseStream << "<body>\n";
#line 16 "/cpp_practice/poco_demo/04_page_complier/2_page_for_loop/str_loop_p.cpsp"
 for(auto const& name: names) { 	responseStream << "\n";
	responseStream << "<p style=\"text-align: center; font-size: 48px;\">";
#line 17 "/cpp_practice/poco_demo/04_page_complier/2_page_for_loop/str_loop_p.cpsp"
	responseStream << ( name );
	responseStream << "</p>\n";
#line 18 "/cpp_practice/poco_demo/04_page_complier/2_page_for_loop/str_loop_p.cpsp"
 } 	responseStream << "\n";
	responseStream << "</body>\n";
	responseStream << "</html>";
}
