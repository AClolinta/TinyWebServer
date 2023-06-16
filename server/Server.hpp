/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:27:16
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 11:53:02
 * @FilePath: /TinyWebServer/server/Server.hpp
 * @Description: 服务端，处理网络部分
 */
#pragma once

#include <string>
#include <string_view>

namespace aclolinta {
namespace server {

    
class Server {
   private:
    /* data */
    std::string m_ip;    // IP
    size_t m_port;       // 端口
    size_t m_threads;    // 线程数
    size_t m_connects;   // 连接数
    size_t m_wait_time;  // 超时等待时间

   public:
    Server();
    ~Server(); 

    //
    void Listen(std::string_view ip, size_t port);
    void Start();
    void SetThreads(size_t threads);
    void SetConnects(size_t connects);
    void SetWaitTimes(size_t wait_time);
};

}  // namespace server
}  // namespace aclolinta