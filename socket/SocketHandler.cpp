/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 13:09:31
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-05 14:04:09
 * @FilePath: /TinyWebServer/socket/SocketHandler.cpp
 * @Description: 基于事件轮询模型的 Socket 服务器
 *  */
#include "SocketHandler.hpp"

#include "../log/log.hpp"
using namespace aclolinta::logger;

#include "../utility/Singleton.hpp"
#include "../utility/iniFile.hpp"

using namespace aclolinta::utility;


#include "../task/Task.hpp"
#include "../thread/AutoLock.hpp"
using namespace aclolinta::task;

#include "../task/TaskDispatcher.hpp"
#include "ServerSocket.hpp"
using namespace aclolinta::socket;

SocketHandler::~SocketHandler() {
    if (nullptr != m_epoll) {
        delete m_epoll;
        m_epoll = nullptr;
    }

    if (nullptr != m_server) {
        delete m_server;
        m_server = nullptr;
    }
}

void SocketHandler::Listen(std::string_view ip, size_t port) {
    m_server = new ServerSocket(ip, port);
}

/**
 * @description: 将Socket添加到事件轮询器中
 * @param {Socket*} socket
 * @return {*}
 */
void SocketHandler::Attach(Socket* socket) {
    AutoLock lock(&m_mutex);
    m_epoll->Add(socket->m_sockfd, static_cast<void*>(socket),
                 (EPOLLONESHOT | EPOLLIN | EPOLLHUP | EPOLLERR));
}

void SocketHandler::Detach(Socket* socket) {
    AutoLock lock(&m_mutex);
    m_epoll->Del(socket->m_sockfd, static_cast<void*>(socket),
                 (EPOLLONESHOT | EPOLLIN | EPOLLHUP | EPOLLERR));
}

void SocketHandler::Remove(Socket* socket) {
    AutoLock lock(&m_mutex);
    socket->Close();
}

void SocketHandler::Handle(size_t max_connect, size_t wait_time) {
    m_epoll = new EventPoller(false);
    m_epoll->Creat(max_connect);
    m_epoll->Add(m_server->m_sockfd, m_server, (EPOLLIN | EPOLLHUP | EPOLLERR));
    m_sockt_pool.Init(max_connect);

    debug("EPOLL WAIT TIME: %dms", wait_time);

    while (true) {
        int event_cnt = m_epoll->Wait(wait_time);

        if (0 == event_cnt) {
            continue;
        }

        for (int i = 0; i < event_cnt; ++i) {
            if (m_server ==
                static_cast<Socket*>(m_epoll->m_events[i].data.ptr)) {
                debug("SOCKET ACCEPT EVENT");

                int sockfd = m_server->Accept();  // 获取一个Socketfd
                Socket* socket_ = m_sockt_pool.Allocate();

                if (nullptr == socket_) {
                    errorr("EMPTY SOCKET POOL");
                    break;
                }

                socket_->m_sockfd = sockfd;
                socket_->SetNonBlocking();
                this->Attach(socket_);
            } else {
                Socket* socket_ =
                    static_cast<Socket*>(m_epoll->m_events[i].data.ptr);
                if (m_epoll->m_events[i].events & EPOLLHUP) {
                    // 检查套接字事件是否是一个 "挂起 "事件
                    // 记录一条错误信息，将套接字从epoll事件中分离出来，
                    // 并将套接字从SocketHandler中删除。
                    errorr("SOCKET %d CLOSED BY PEER.", socket_->m_sockfd);
                    this->Detach(socket_);
                    this->Remove(socket_);
                } else if (m_epoll->m_events[i].events & EPOLLERR){
                    errorr("SOCKET %d ERRORR.", socket_->m_sockfd);
                    this->Detach(socket_);
                    this->Remove(socket_);
                } else if(m_epoll->m_events[i].events & EPOLLIN){
                    debug("SOCKET READ EVENT");
                    this->Detach(socket_);
                    Task* task = TaskFactory::Create(socket_);
                    Singleton<TaskDispatcher>::Getinstance()->Assign(task);
                }
            }
        }
    }
}