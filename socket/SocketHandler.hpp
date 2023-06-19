/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 12:05:40
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 12:08:05
 * @FilePath: /TinyWebServer/socket/SocketHandler.hpp
 * @Description: 基于事件轮询模型的 Socket 服务器
 *  */
#pragma once

#include <list>
#include <string>
#include <string_view>

#include "ObjectPool.hpp"
#include "EventPoller.hpp"
#include "Socket.hpp"

using namespace aclolinta::utility;

#include "Mutex.hpp"
using namespace aclolinta::thread;

#include "Task.hpp"
using namespace aclolinta::task;

namespace aclolinta {
namespace socket {
class SocketHandler {
   private:
    /* data */
    EventPoller* m_epoll;  // epoll
    Socket* m_server;
    ObjectPool<Socket> m_sockt_pool;  // socket的对象池
    Mutex m_mutex;

   public:
    SocketHandler(/* args */) = default;
    ~SocketHandler();

   public:
    /**
     * @description: 指定的 IP
     * 和端口号上创建监听套接字，开始监听客户端的连接请求
     * @param {string_view} ip
     * @param {size_t} port
     * @return {*}
     */
    void Listen(std::string_view ip, size_t port);
    /**
     * @description:  在指定的
     * IP和端口号上创建监听套接字，开始监听客户端的连接请求
     * @param {Socket*} socket
     * @return {*}
     */
    void Attach(Socket* socket);
    /**
     * @description: 一个 Socket 对象添加到事件轮询器中，开始监听该 Socket
     * 的读写事件
     * @param {Socket*} socket
     * @return {*}
     */
    void Detach(Socket* socket);
    /**
     * @description: 将一个 Socket 对象从事件轮询器中移除，并关闭该 Socket。
     * @param {Socket*} socket
     * @return {*}
     */
    void Remove(Socket* socket);
    /**
     * @description: 处理连接请求和事件轮询
     * @param {size_t} max_connect 最大连接数
     * @param {size_t} wait_time 等待时间
     * @return {*}
     */
    void Handle(size_t max_connect, size_t wait_time);
};

}  // namespace socket
}  // namespace aclolinta
