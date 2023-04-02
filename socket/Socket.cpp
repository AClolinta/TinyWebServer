/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-02 03:19:50
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-02 07:52:29
 * @FilePath: /TinyWebServer/socket/Socket.cpp
 * @Description: Socket的实现 */
#include "Socket.hpp"

#include "../log/log.hpp"

using namespace aclolinta::logger;
using namespace aclolinta::socket;

#include <cerrno>
#include <cstring>

Socket::Socket() : m_sockfd(0){};

Socket::Socket(std::string_view ip, size_t port)
    : m_ip(ip), m_port(port), m_sockfd(0){};

Socket::~Socket() { Close(); }

bool Socket::Bind(std::string_view ip, size_t port) {
    struct sockaddr_in sockaddr;
    std::memset(&sockaddr, 0, sizeof(sockaddr));

    // std::string ip_(ip);

    sockaddr.sin_family = AF_INET;  // 表示 IPv4 地址族
    if ("" != ip) {
        if (inet_pton(AF_INET, ip.data(), &sockaddr.sin_addr) <= 0) {
            errorr(" TRANSFER IP_ADDR IN INET_PTON");
        }
    } else {
        sockaddr.sin_addr.s_addr =
            htons(INADDR_ANY);  // 让该端口接收来自所有本地接口上的请求
    }
    sockaddr.sin_port = htons(port);  // 设定端口

    if (bind(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
        errorr("SOCKET BIND ERROR: ERRNO=%d ERRSTR=%s", errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::Listen(int backlog) {
    // 监听端口
    if (listen(m_sockfd, backlog) < 0) {
        errorr("SOCKET LISTEN ERROR: ERRNO=%d ERRSTR=%s", errno,
               strerror(errno));
        return false;
    }
    return true;
}

bool Socket::Connect(std::string_view ip, size_t port) {
    // std::string ip_(ip);
    struct sockaddr_in sockaddr;
    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;

    if (inet_pton(AF_INET, ip.data(), &sockaddr.sin_addr) <= 0) {
        errorr(" TRANSFER IP_ADDR IN INET_PTON");
    }

    sockaddr.sin_port = htons(port);
    if (connect(m_sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
        errorr("SOCKET CONNECT ERROR: ERRNO=%d ERRSTR=%s", errno,
               strerror(errno));
        return false;
    }
    return true;
}

bool Socket::Close() {
    if (m_sockfd > 0) {
        close(m_sockfd);
        m_sockfd = 0;
    }
    return true;
}
