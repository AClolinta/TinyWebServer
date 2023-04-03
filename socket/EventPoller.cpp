/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 02:19:44
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 09:13:03
 * @FilePath: /TinyWebServer/socket/EventPoller.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "EventPoller.hpp"

using namespace aclolinta::socket;

EventPoller::EventPoller(bool et)
    : m_epfd(), m_max_connect(0), m_events(NULL), m_et(et){};

EventPoller::~EventPoller() {
    if (m_epfd > 0) {
        close(m_epfd);
        m_epfd = 0;
    }

    if (nullptr != m_events) {
        delete[] m_events;
        m_events = nullptr;
    }
}

void EventPoller::Ctrl(int fd, void* ptr, __uint32_t events, int operate) {
    struct epoll_event event_;

    event_.data.ptr = ptr;
    if (m_et) {
        // ET模式
        event_.events = events | EPOLLET;
    } else {
        event_.events = events;
    }
    epoll_ctl(m_epfd, operate, fd, &event_);  // epoll的事件注册函数
}

void EventPoller::Creat(size_t max_connet) {
    m_max_connect = max_connet;
    m_epfd = epoll_create(m_max_connect + 1);  // 自己也算一个epoll实例
    if (m_epfd < 0) {
        return;
    }
    if (nullptr == m_events) {
        delete[] m_events;
        m_events = nullptr;
    }

    m_events = new epoll_event[m_max_connect + 1];
}

void EventPoller::Add(int fd, void* ptr, __uint32_t events) {
    Ctrl(fd, ptr, events, EPOLL_CTL_ADD);
}

void EventPoller::Mod(int fd, void* ptr, __uint32_t events) {
    Ctrl(fd, ptr, events, EPOLL_CTL_MOD);
}

void EventPoller::Del(int fd, void* ptr, __uint32_t events) {
    Ctrl(fd, ptr, events, EPOLL_CTL_DEL);
}

int EventPoller::Wait(size_t millsecond) {
    return epoll_wait(m_epfd, m_events, m_max_connect + 1, millsecond);
}
