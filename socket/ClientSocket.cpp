/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 02:09:54
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 07:37:21
 * @FilePath: /TinyWebServer/socket/ClientSocket.cpp
 * @Description: 客户端的实现
 * */

#include "ClientSocket.hpp"

#include "../logger/log.hpp"

using namespace aclolinta::logger;
using namespace aclolinta::socket;

#include <cerrno>
#include <cstring>

ClientSocket::ClientSocket():Socket(){

}

ClientSocket::ClientSocket(std::string_view ip, size_t port):Socket(ip,port){
    // SOCK_STREAM表示使用面向连接的流式套接字
    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sockfd < 0) {
        errorr("CREATE CLIENT SOCKET ERROR: ERRNO=%d ERRSTR=%s", errno,
               strerror(errno));
        return;
    }

    Socket::Connect(ip,port);
}

ClientSocket::~ClientSocket(){
    Close();
}