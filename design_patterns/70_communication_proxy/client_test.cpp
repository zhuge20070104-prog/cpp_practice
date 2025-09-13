#include "http_client.hpp"


void test_get() {
    auto res = GET("127.0.0.1", "8080", "/conaninfo.txt");

    std::cout << "Result Code:" << res.res.result_int() << std::endl;
    std::cout << res.res << std::endl;

    res = GET("127.0.0.1", "8080", "/");

    // Get Status Code
    std::cout << "Result Code:" << res.res.result_int() << std::endl;
    // Get Response Body
    std::cout << res.res.body() << std::endl;

    std::cout << "Get all response fields using iteration: \n";
    for(auto const& field : res.res) {
        std::cout << field.name() << "---> " << field.value() << "\n";
    } 

    std::cout << "Get all response fields using key names: \n";
    std::cout << "Server: " << res.res[http::field::server] << std::endl;
    std::cout << "Content Type: " << res.res[http::field::content_type] << std::endl;
    std::cout << "Content Length: " << res.res[http::field::content_length] << std::endl;
}


void test_post() {
    std::string body = R"({"x": 3, "y": 2})";
    auto res1 = POST("127.0.0.1", "8080", "/plus", body);
      // Get Status Code
    std::cout << "Result Code:" << res1.res.result_int() << std::endl;
    // Get Response Body
    std::cout << res1.res.body() << std::endl;

    std::cout << "Get all response fields using iteration: \n";
    for(auto const& field : res1.res) {
        std::cout << field.name() << "---> " << field.value() << "\n";
    } 
}

void test_pingpong() {
    auto res = GET("127.0.0.1", "8080", "/api/pingpong/hello");
    std::cout << res.res.body() << std::endl;

    res = GET("127.0.0.1", "8080", "/api/pingpong/ping");
    std::cout << res.res.body() << std::endl;
}

void test_query_param() {
    auto res = GET("127.0.0.1", "8080", "/query?a=b&c=d");
    std::cout << res.res.body() << std::endl;
}


int main(int argc, char** argv) {    
    test_get();
    test_post();
    test_pingpong();
    test_query_param();
    return EXIT_SUCCESS;
}