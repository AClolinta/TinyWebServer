/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 01:37:09
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 07:38:15
 * @FilePath: /TinyWebServer/socket/ServerSocket.cpp
 * @Description: 服务端
 */
#include "ServerSocket.hpp"

#include "log.hpp"

using namespace aclolinta::logger;
using namespace aclolinta::socket;

#include <cerrno>
#include <cstring>

ServerSocket::ServerSocket() : Socket(){};

ServerSocket::ServerSocket(std::string_view ip, size_t port)
    : Socket(ip, port) {
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  // 打开socket描述符
    if (m_sockfd < 0) {
        errorr("CREATE SERVER SOCKET ERROR: ERRNO=%d ERRSTR=%s", errno,
               strerror(errno));
        return;
    }

    SetNonBlocking();
    SetRecvBuffer(10 * 1024);
    SetSendBuffer(10 * 1024);
    SetLinger(true, 0);  // 关闭套接字时立即关闭连接。
    SetKeepAlive();  // 开启心跳包检测机制，检测长时间未活跃的连接
    SetReuseAddr();  // 允许在同一端口上重用Socket

    Bind(ip, port);  // 绑定端口
    Listen(1024);
}

ServerSocket::~ServerSocket() { Close(); }