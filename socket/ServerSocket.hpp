/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 01:36:59
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 07:38:39
 * @FilePath: /TinyWebServer/socket/ServerSocket.hpp
 * @Description: 服务器端Socket的实现，利用自己封装好的Socket.hpp
 *  */
#pragma once

#include <string>
#include <string_view>

#include "Socket.hpp"

namespace aclolinta {
namespace socket {
class ServerSocket : public Socket{
   private:
    /* data */
   public:
    ServerSocket(/* args */);
    ServerSocket(std::string_view ip, size_t port);

    virtual ~ServerSocket();
};

}  // namespace socket
}  // namespace aclolinta