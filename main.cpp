#include <iostream>
#include <memory>
#include "HttpServer.h"

using namespace http;
// 初始化HttpServer静态类成员
ExporterChannel channel;
std::map<std::string, std::string> ret;

bool handle_fun(const std::string &url, const std::string &body, mg_connection *c, OnRspCallback rsp_callback) {
    // do sth

    rsp_callback(c, "");

    return true;
}

int main(int argc, char *argv[]) {
    std::string port = "7999";
    auto server = std::make_shared<HttpServer>();
    // add handler
    channel.push({"123", "456"});
//    ret.insert({"123", "456"});
    server->AddHandler("/metrics", handle_fun);
    server->port(port)->serve();


    return 0;
}