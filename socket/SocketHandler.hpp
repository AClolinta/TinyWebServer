/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 12:05:40
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-04 09:17:25
 * @FilePath: /TinyWebServer/socket/SocketHandler.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <list>
#include <string>
#include <string_view>

#include "../utility/ObjectPool.hpp"
#include "EventPoller.hpp"
#include "Socket.hpp"

using namespace aclolinta::utility;

#include "../thread/Mutex.hpp"
using namespace aclolinta::thread;

#include "../task/Task.hpp"
using namespace aclolinta::task;

namespace aclolinta {
namespace socket {
class SocketHandler {
   private:
    /* data */
    EventPoller* m_epoll;
    Socket* m_server;
    ObjectPool<Socket> m_sockt_pool;
    Mutex m_mutex;

   public:
    SocketHandler(/* args */) = default;
    ~SocketHandler();

   public:
    void Listen(std::string_view ip, size_t port);
    void Attach(Socket* socket);
    void Detach(Socket* socket);
    void Remove(Socket* socket);
    void Handle(size_t max_connect, size_t wait_time);
};

}  // namespace socket
}  // namespace aclolinta
