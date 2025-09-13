struct  RequestConext {
    request_method,
    request_path,
    response_code,
    response_content_type

    Callback<std::string(Request&)>
};


struct  RequestHandler {


    template<
    class Body, class Allocator,
    class Send>
    void operator()(beast::string_view doc_root, 
    http::request<Body, http::basic_fields<Allocator>>&& req,
    Send&& send) {

    }
};