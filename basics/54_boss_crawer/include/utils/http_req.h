#ifndef _FREDRIC_HTTP_REQ_H_
#define _FREDRIC_HTTP_REQ_H_

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPSClientSession.h>  
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <sstream>
#include <map>

/***
 * http_req_t is a https client, which is based on the Poco library,
 * The usage is as belows 
 * std::string resp;
    bool req_ok = http_req_t::send_http_request(req_type_t::get,
        "https://www.zhipin.com:443/wapi/zpgeek/search/joblist.json?scene=1&query=%E6%B5%8B%E8%AF%95%E5%BC%80%E5%8F%91&city=101020100&experience=&payType=&partTime=&degree=&industry=&scale=&stage=&position=&jobType=&salary=&multiBusinessDistrict=&multiSubway=&page=2&pageSize=30",
        {   {"Sec-Ch-Ua", R"("Chromium";v="124", "Microsoft Edge";v="124", "Not-A.Brand";v="99")"},
            {"Cookie", "wd_guid=eeeb3491-7581-4c30-a605-ed20b5850811; historyState=state; _bl_uid=IUlqev2X67d21dd247U3n5vabwsb; lastCity=101020100; __g=-; Hm_lvt_194df3105ad7148dcf2b98a91b5e727a=1713506343,1715906605; __zp_stoken__=ae3bfw44XwrEFPVpQB1cbRnsEw4hRbkrCvXlWSlFrwrVTTMOLwpNyaMK%2BX1DCsmPCm11MwqzDiXnCrcOJwptZwr9Ewp5NwqXCpcO6wp3CmsSfw7VNxKbEiMKvwrHCkD84DAwCDwAYGA4bBA8PDhsEGBgOGwQYGA4bBDoiw7YBMD9ISyBCRkYZRFVUQVpAD1pORj4xBmgbBjE7MUs%2BPcOIMcK1wpbCtDHCv8KTw4s9wr%2FDoUs2PTHCv0UtKsKxw5sHwr8UDcK8w7ghwr3Dm1rCskkBw4FrccKAwqHCscOaLzwzwrHEvj4%2FH0s8MkkwPEkyPy88EMObaHfCg8Ktw4vDhSAxHDo%2FMDc6Mj8wNTwwIzA0Szg%2FPSFIARsDDBslSMKxVcKxw5Q%2FMA%3D%3D; __c=1715906605; __l=l=%2Fwww.zhipin.com%2Fshanghai%2F&r=&g=&s=3&friend_source=0&s=3&friend_source=0; __a=96540295.1713170242.1713496020.1715906605.29.4.18.29; Hm_lpvt_194df3105ad7148dcf2b98a91b5e727a=1715914788; __zp_sname__=daff8e85; __zp_sseed__=qB2wV9miNIcDSbJGjo/3e4VMIYW92CvxTyauZ8P5cuQ=; __zp_sts__=1715922595735"},
            {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36 Edg/124.0.0.0"},
            {"Cache-Control", "max-age=0"},
            {"Connection", "keep-alive"},
            {"Host", "www.zhipin.com"},
            {"Accept-Encoding", "gzip, deflate, br, zstd"},
            {"Accept-Language", "en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7"},
            {"Accept", "text/html"}
        },
        "",
        resp
        );

     bool req_ok_bing = http_req_t::send_http_request(req_type_t::get,
        "https://cn.bing.com:443/",
        {
            {"Accept", "text/html"},
            {"Content-Encoding", "gzip"}
        },
        "",
        resp
        );
    std::cout << resp << std::endl;
*/

enum req_type_t {
    get,
    post
};

struct http_req_t {
    static bool send_http_request(req_type_t req_type,
                                        std::string const& url,
                                        std::map<std::string, std::string> const& headers,
                                        std::string const& contents,
                                        std::string& resp_out);
};
#endif
