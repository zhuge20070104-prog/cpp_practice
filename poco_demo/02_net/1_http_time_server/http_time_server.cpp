#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Exception.h"
#include "Poco/ThreadPool.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/StreamCopier.h"

#include "nlohmann/json.hpp"
#include <iostream>

using Poco::Net::ServerSocket;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPRequestHandlerFactory;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPServerParams;
using Poco::Timestamp;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::ThreadPool;
using Poco::Util::ServerApplication;
using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using json = nlohmann::ordered_json;


// Return a HTML document with the current date and time
class TimeRequestHandler: public HTTPRequestHandler {
public:
TimeRequestHandler(std::string const& format): _format(format) {}

void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());

    Timestamp now;
    std::string dt(DateTimeFormatter::format(now, _format));
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/html");
    std::ostream& ostr = response.send();
    ostr << "<html><head><title>HTTPTimeServer powered by POCO C++ Libraries</title>";
    ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
    ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
    ostr << dt;
    ostr << "</p></body></html>";
}
private:
std::string _format;
};

class JsonRequestHandler: public HTTPRequestHandler {
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        Application& app = Application::instance();
        app.logger().information("Request from " + request.clientAddress().toString());
        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");
        std::ostream& ostr = response.send();
        json js;
        js["name"] = "ZhangSan";
        js["age"] = 18;
        js["work"] = "Software Engineer for Testing";
        ostr << js.dump(4);
    }
};

class JsonReadRequestHandler: public HTTPRequestHandler {
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) override {
        Application& app = Application::instance();
        app.logger().information("Request from " + request.clientAddress().toString());
        std::cout << "Method: " << request.getMethod() << std::endl;
        poco_assert(request.getMethod() == "POST");
        
        auto& req_stream = request.stream();
        auto content_len = request.getContentLength(); 
        std::string req_str(content_len, 0);
        req_stream.read((char*)req_str.data(), content_len);
        
        std::cout << "Request parameters: " << req_str << std::endl;

        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");
        json js = json::parse(req_str);
        js["name"] = "Lisi";
        js["age"] = 150;
        js["job"] = "C++ Developer";
        
        std::ostream& ostr = response.send();
        ostr << js.dump(4);
    }
};

class TimeRequestHandlerFactory: public HTTPRequestHandlerFactory {
public:
    TimeRequestHandlerFactory(std::string const& format): _format(format) {}
    
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) override {
        if(request.getURI() == "/") {
            return new TimeRequestHandler(_format);
        } else if(request.getURI() == "/json") {
            return new JsonRequestHandler();
        } else if(request.getURI() == "/json_read") {
            return new JsonReadRequestHandler();
        } else {
            return nullptr;
        }      
    }
private:
    std::string _format;
};

class HTTPTimeServer: public Poco::Util::ServerApplication {
public:
    HTTPTimeServer():_helpRequested(false) {}
    ~HTTPTimeServer() {}

protected:
    void initialize(Application& self) override {
        loadConfiguration();
        ServerApplication::initialize(self);
    }

    void uninitialize() override {
        ServerApplication::uninitialize();
    }

    void defineOptions(OptionSet& options) override {
        ServerApplication::defineOptions(options);
        options.addOption(
            Option("help", "h", "Display information on command line arguments")
                .required(false)
                .repeatable(false)
        );
    }

    void handleOption(const std::string& name, const std::string& value) override {
        ServerApplication::handleOption(name, value);
        if(name == "help") {
            _helpRequested = true;
        }
    }

    void displayHelp() {
        HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("A web server that serves the current date and time");
        helpFormatter.format(std::cout);
    }

    int main(std::vector<std::string> const& args) {
        if(_helpRequested) {
            displayHelp();
        } else {
            unsigned short port = (unsigned short)config().getInt("HTTPTimeServer.port", 9980);
            std::string format(config().getString("HTTPTimeServer.format", DateTimeFormat::SORTABLE_FORMAT));
            int maxQueued = config().getInt("HTTPTimeServer.maxQueued", 100);
            int maxThreads = config().getInt("HTTPTimeServer.maxThreads", 16);
            ThreadPool::defaultPool().addCapacity(maxThreads);

            HTTPServerParams* pParams = new HTTPServerParams;
            pParams->setMaxQueued(maxQueued);
            pParams->setMaxThreads(maxThreads);

            ServerSocket svs(port);
            HTTPServer srv(new TimeRequestHandlerFactory(format), svs, pParams);
            srv.start();
            waitForTerminationRequest();
            srv.stop();
        }
        return Application::EXIT_OK;
    }
private:
    bool _helpRequested;
};


int main(int argc, char* argv[]) {
    HTTPTimeServer app;
    return app.run(argc, argv);
}