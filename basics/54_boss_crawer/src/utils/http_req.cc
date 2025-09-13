#include "utils/http_req.h"

bool http_req_t::send_http_request(req_type_t req_type,
                                     std::string const& url,
                                     std::map<std::string, std::string> const& headers,
                                     std::string const& contents,
                                     std::string& resp_out) {
    try {
        Poco::URI uri(url); 
        Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());
        auto http_method = Poco::Net::HTTPRequest::HTTP_GET;
        if(req_type == req_type_t::post) {
            http_method = Poco::Net::HTTPRequest::HTTP_POST;
        }
        std::cout << uri.getPathAndQuery() << std::endl;
        Poco::Net::HTTPRequest request(http_method, uri.getPathAndQuery(), Poco::Net::HTTPMessage::HTTP_1_1);
        // 设置请求头
        for(auto const& header_pair: headers) {
            request.set(header_pair.first, header_pair.second);
        }

        std::ostream& ostr = session.sendRequest(request);  
        ostr << contents;

        // 接收响应  
        Poco::Net::HTTPResponse response;  
        std::istream& rs = session.receiveResponse(response);
        if(response.getStatus() != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            // 输出响应状态  
            std::cout << "Response status: " << response.getStatus() << " " << response.getReason() << std::endl; 
            resp_out = response.getReason();
            return false;
        }
        // 读取并输出响应体  
        std::ostringstream oss;  
        Poco::StreamCopier::copyStream(rs, oss);
        resp_out = oss.str();
        return true;
    } catch(Poco::Exception& ex) {
        std::cout << "Exception occurred: " << ex.displayText() << std::endl;
        resp_out = ex.displayText();
        return false;
    }
}
