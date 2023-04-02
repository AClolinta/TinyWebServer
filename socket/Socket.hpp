/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-02 02:53:21
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-02 04:04:14
 * @FilePath: /TinyWebServer/socket/Socket.hpp
 * @Description: Socket的实现
 * */
#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <string_view>

namespace aclolinta {
namespace socket {
class Socket {
   public:
    Socket(/* args */);
    Socket(std::string_view ip, size_t port);
    virtual ~Socket();

   public:
    bool Bind(std::string_view ip, size_t port);     // 绑定端口
    bool Listen(int backlog);                     // 监听
    bool Connect(std::string_view ip, size_t port);  // 链接
    bool Close();

    int Accept();
    int Recv(char* buff, size_t len);
    int Send(const char* buff, size_t len);

    bool SetNonBlocking();
    bool SetSendBuffer(size_t size);
    bool SetRecvBuffer(size_t size);
    bool SetLinger(bool active, size_t seconds);
    bool SetKeep_alive();
    bool SetReuse_addr();
    bool SetReuse_port();

   protected:
    std::string m_ip;
    size_t m_port;
    int m_sockfd;  // Socket 的文件描述符。
};

}  // namespace socket
}  // namespace aclolinta