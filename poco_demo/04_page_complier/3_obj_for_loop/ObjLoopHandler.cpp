#include "ObjLoopHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTMLForm.h"
#line 2 "/cpp_practice/poco_demo/04_page_complier/3_obj_for_loop/obj_loop_p.cpsp"

    #include <string>
    #include <vector>


using namespace std::string_literals;


void ObjLoopHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/html"s);

	Poco::Net::HTMLForm form(request, request.stream());
	std::ostream& responseStream = response.send();
	responseStream << "\n";
#line 7 "/cpp_practice/poco_demo/04_page_complier/3_obj_for_loop/obj_loop_p.cpsp"

    struct Person {
        std::string name;
        int age;
    };
    std::vector<Person> persons {{"ZhangSan", 18}, {"Lisi", 22}, {"WangWu", 33}, {"ZhaoLiu", 34}};
	responseStream << "\n";
	responseStream << "<html>\n";
	responseStream << "<head>\n";
	responseStream << "<title>ObjLoopHandler powered by POCO C++ Libraries and PageCompiler</title>\n";
	responseStream << "<meta http-equiv=\"refresh\" content=\"1\">\n";
	responseStream << "</head>\n";
	responseStream << "<body>\n";
#line 20 "/cpp_practice/poco_demo/04_page_complier/3_obj_for_loop/obj_loop_p.cpsp"
 for(auto const& person: persons) { 	responseStream << "\n";
	responseStream << "<p style=\"text-align: center; font-size: 48px;\">";
#line 21 "/cpp_practice/poco_demo/04_page_complier/3_obj_for_loop/obj_loop_p.cpsp"
	responseStream << ( person.name );
	responseStream << " &nbsp;&nbsp; ";
#line 21 "/cpp_practice/poco_demo/04_page_complier/3_obj_for_loop/obj_loop_p.cpsp"
	responseStream << (person.age);
	responseStream << "</p>\n";
#line 22 "/cpp_practice/poco_demo/04_page_complier/3_obj_for_loop/obj_loop_p.cpsp"
 } 	responseStream << "\n";
	responseStream << "</body>\n";
	responseStream << "</html>";
}
