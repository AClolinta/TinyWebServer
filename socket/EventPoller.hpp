/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 02:19:12
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 03:11:53
 * @FilePath: /TinyWebServer/socket/EventPoller.hpp
 * @Description: Epoll真难啊
 * */
#pragma once

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

namespace aclolinta {
namespace socket {
/// @brief
class EventPoller {
    friend class SocketHandler;

   public:
    /// @brief 构造函数
    /// @param et 默认是et模式
    EventPoller(bool et = true);
    ~EventPoller();

    /// @brief  epoll句柄
    /// @param max_connet epoll服务需要支持的最大连接数
    void Creat(size_t max_connet);

    /// @brief 添加监听句柄.
    /// @param fd 句柄（文件描述符）
    /// @param ptr 辅助的数据, 可以后续在epoll_event中获取到
    /// @param events 需要监听的事件EPOLLIN|EPOLLOUT
    void Add(int fd, void* ptr, __uint32_t events);

    /// @brief 修改句柄事件.
    /// @param fd 句柄（文件描述符）
    /// @param ptr 辅助的数据, 可以后续在epoll_event中获取到
    /// @param events 需要监听的事件EPOLLIN|EPOLLOUT
    void Mod(int fd, void* ptr, __uint32_t events);

    /// @brief 删除句柄事件.
    /// @param fd 句柄（文件描述符）
    /// @param ptr 辅助的数据, 可以后续在epoll_event中获取到
    /// @param events 需要监听的事件EPOLLIN|EPOLLOUT
    void Del(int fd, void* ptr, __uint32_t events);

    /// @brief 等待时间
    /// @param millsecond 毫秒
    /// @return 有事件触发的句柄数
    int Wait(size_t millsecond);

   protected:
    /**
     * @description: 控制 epoll，将EPOLL设为边缘触发EPOLLET模式(ET)
     * @param {int} fd 句柄，在create函数时被赋值
     * @param {void*} ptr 辅助的数据, 可以后续在epoll_event中获取到
     * @param {__uint32_t} events 需要监听的事件
     *                 EPOLLIN  表示对应的文件描述符可以读
     *                 EPOLLOUT 表示对应的文件描述符可以写
     *                 EPOLLPRI 表示对应的文件描述符有紧急的数据可读
     *                 EPOLLERR 表示对应的文件描述符发生错误
     *                 EPOLLHUP 表示对应的文件描述符被挂断
     *                 EPOLLET  表示对应的文件描述符有事件发生
     * @param {int} operate 控制 epoll 文件描述符上的事件：注册、修改、删除
     *                 EPOLL_CTL_ADD：注册新的fd到epfd中
     *                 EPOLL_CTL_MOD：修改已经注册的fd的监听事件
     *                 EPOLL_CTL_DEL：从 epfd中删除一个fd；
     */
    void Ctrl(int fd, void* ptr, __uint32_t events, int operate);

   protected:
    int m_epfd;                    // epoll句柄
    int m_max_connect;         // 最大连接数
    struct epoll_event* m_events;  // 事件集
    bool m_et;                     // 否是为ET模式
};

}  // namespace socket
}  // namespace aclolinta