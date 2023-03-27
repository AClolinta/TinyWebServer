/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:27:16
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-27 03:33:32
 * @FilePath: /TinyWebServer/server/Server.hpp
 * @Description: 服务端，处理网络部分
 */
#pragma once

#include <string>
#include <string_view>

namespace aclolita {
namespace server {
class Server {
   private:
    /* data */
    std::string m_ip;
    size_t m_port;
    size_t m_threads;
    size_t m_connects;
    size_t m_wait_time;

   public:

   Server();
   ~Server();

   //
   void Listen(std::string_view ip, size_t port);
   void Start();
   void SetThread(size_t threads);
   void SetConnects(size_t connects);
   void SetWaitTime(size_t wait_time);
};

}  // namespace server
}  // namespace aclolita