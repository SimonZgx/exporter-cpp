#pragma once

#include <string>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <atomic>

#include "mongoose.h"

// 定义http返回callback
typedef void OnRspCallback(mg_connection *c, std::string);
// 定义http请求handler
using ReqHandler = std::function<bool(std::string, std::string, mg_connection *c, OnRspCallback)>;

namespace http {
    class HttpServer : public std::enable_shared_from_this<HttpServer> {
    public:
        HttpServer();

        ~HttpServer() = default;

        std::shared_ptr<HttpServer> port(const std::string &port) {
            port_ = port;
            return this->shared_from_this();
        }

        std::shared_ptr<HttpServer> rootPath(const std::string &rootPath) {
            port_ = rootPath;
            return this->shared_from_this();
        }

        bool serve(); // 启动httpserver
        bool Close(); // 关闭
        void AddHandler(const std::string &url, ReqHandler req_handler); // 注册事件处理函数
        static std::string rootPath_; // 网页根目录
        static mg_serve_http_opts serverOpt_; // web服务器选项
        static std::unordered_map<std::string, ReqHandler> s_handler_map; // 回调函数映射表

    private:
        // 静态事件响应函数
        static void OnHttpWebsocketEvent(mg_connection *connection, int event_type, void *event_data);

        static void HandleHttpEvent(mg_connection *connection, http_message *http_req);

        static void SendHttpRsp(mg_connection *connection, std::string rsp);

        static int isWebsocket(const mg_connection *connection); // 判断是否是websoket类型连接
        static void HandleWebsocketMessage(mg_connection *connection, int event_type, websocket_message *ws_msg);

        static void SendWebsocketMsg(mg_connection *connection, std::string msg); // 发送消息到指定连接
        static void BroadcastWebsocketMsg(const std::string& msg); // 给所有连接广播消息
        static std::unordered_set<mg_connection *> s_websocket_session_set; // 缓存websocket连接

        std::string port_;    // 端口
        mg_mgr mgr_{};          // 连接管理器

    };
}

