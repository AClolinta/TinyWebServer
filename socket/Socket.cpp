/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-02 03:19:50
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-02 09:16:05
 * @FilePath: /TinyWebServer/socket/Socket.cpp
 * @Description: Socket的实现 */
#include "Socket.hpp"

#include "log.hpp"

using namespace aclolinta::logger;
using namespace aclolinta::socket;

#include <cerrno>
#include <cstring>
#include <system_error>

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

    if (bind(m_sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
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
    if (connect(m_sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
        errorr("SOCKET CONNECT ERROR: ERRNO=%d ERRSTR=%s", errno,
               strerror(errno));
        return false;
    }
    return true;
}

bool Socket::Close() {
    // 关闭链接
    if (m_sockfd > 0) {
        close(m_sockfd);
        m_sockfd = 0;
    }
    return true;
}

int Socket::Accept() {
    // 会阻塞进程，直到有客户端连接进来
    int sockfd_ = accept(m_sockfd, nullptr, nullptr);
    if (sockfd_ < 0) {
        errorr("ACCEPT CALL ERROR: ERRNO=%d ERRSTR=%s", errno, strerror(errno));
        sockfd_ = -1;
    }

    return sockfd_;
}

int Socket::Recv(char* buff, size_t len) {
    // flag一般设置为0，此时send为阻塞式发送
    return recv(m_sockfd, buff, len, 0);
}

int Socket::Send(const char* buff, size_t len) {
    return send(m_sockfd, buff, len, 0);
}

bool Socket::SetNonBlocking() {
    int flags = fcntl(m_sockfd, F_GETFL, 0);  // 获取文件描述符的状态标志
    if (flags < 0) {
        errorr(
            "Socket::SetNonBlocking(F_GETFL, O_NONBLOCK): ERRNO=%d ERRSTR=%s",
            errno, strerror(errno));
        return false;
    }
    flags |= O_NONBLOCK;  // 将 O_NONBLOCK 标志位添加到了标志位中(非阻塞标志)

    if (fcntl(m_sockfd, F_SETFL, flags)) {
        // 文件描述符的状态更改为给定的状态，设置非阻塞
        errorr(
            "Socket::SetNonBlocking(F_SETFL, O_NONBLOCK): ERRNO=%d ERRSTR=%s",
            errno, strerror(errno));
        return false;
    }
    return true;
}

bool Socket::SetSendBuffer(size_t size) {
    // size_t buff_size = size;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_SNDBUF, &size, sizeof(size)) < 0){
        errorr("SOCKET SET SEND BUFFER ERROR: ERRNO=%d ERRSTR=%s", errno,
              strerror(errno));
        return false;
    }
    return true;
    
 }
bool Socket::SetRecvBuffer(size_t size){

    if (setsockopt(m_sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)) < 0) {
        errorr("SOCKET SET RECV BUFFER ERROR: ERRNO=%d ERRSTR=%s", errno,
               strerror(errno));
        return false;
    }
    return true;
}


bool Socket::SetLinger(bool active, size_t seconds){
    // 当连接中断时，需要延迟关闭(linger)以保证所有数据都被传输
    struct linger l;
    memset(&l, 0, sizeof(l));

    if (active)
        l.l_onoff = 1;
    else
        l.l_onoff = 0;
    l.l_linger = seconds;

    if (setsockopt(m_sockfd, SOL_SOCKET, SO_LINGER, &l, sizeof(l)) < 0) {
        errorr("SOCKET SET SOCK LINGER ERROR: ERRNO=%d ERRSTR=%s", errno,
              strerror(errno));
        return false;
    }
    return true;
}

bool Socket::SetKeepAlive() {
    // 允许使用心跳包
     size_t flag = 1;
     if (setsockopt(m_sockfd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) <
         0) {
        errorr("SOCKET SET SOCK KEEP ALIVE ERROR: ERRNO=%d ERRSTR=%s", errno,
              strerror(errno));
        return false;
     }
    return true;
}
bool Socket::SetReuseAddr() {
    // 当服务端出现timewait状态的链接时，确保server能够重启成功。
    size_t flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) <
        0) {
        errorr("SOCKET SET SOCK REUSER ADDR ERROR: ERRNO=%s ERRSTR=%s", errno,
              strerror(errno));
        return false;
    }
    return true;
}
bool Socket::SetReusePort() {
    // 多进程或者多线程创建多个绑定同一个ip:port的监听socket
    size_t flag = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) <
        0) {
        errorr("SOCKET SET SOCK REUSER PORT ERROR: ERRNO=%d ERRSTR=%s", errno,
              strerror(errno));
        return false;
    }
    return true;
}