#include <iostream>
#include <memory>
#include "HttpServer.h"

using namespace http;
// 初始化HttpServer静态类成员
mg_serve_http_opts HttpServer::serverOpt_;
std::string HttpServer::rootPath_ = "./web";
std::unordered_map<std::string, ReqHandler> HttpServer::s_handler_map;
std::unordered_set<mg_connection *> HttpServer::s_websocket_session_set;

bool handle_fun1(const std::string& url, const std::string& body, mg_connection *c, OnRspCallback rsp_callback) {
    // do sth
    std::cout << "handle fun1" << std::endl;
    std::cout << "url: " << url << std::endl;
    std::cout << "body: " << body << std::endl;

    rsp_callback(c, "rsp1");

    return true;
}

bool handle_fun2(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback) {
    // do sth
    std::cout << "handle fun2" << std::endl;
    std::cout << "url: " << url << std::endl;
    std::cout << "body: " << body << std::endl;

    rsp_callback(c, "rsp2");

    return true;
}

int main(int argc, char *argv[]) {
    std::string port = "7999";
    auto server = std::make_shared<HttpServer>();
    // add handler
    server->AddHandler("/api/fun1", handle_fun1);
    server->AddHandler("/api/fun2", handle_fun2);
    server->port(port)->serve();


    return 0;
}