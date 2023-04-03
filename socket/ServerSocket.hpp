/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 01:36:59
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 01:43:18
 * @FilePath: /TinyWebServer/socket/ServerSocket.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: 服务器端Socket的实现，利用自己封装好的Socket.hpp
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