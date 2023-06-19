/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-04 13:47:51
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 09:43:09
 * @FilePath: /TinyWebServer/server/Server.cpp
 * @Description: 服务器配置
 */
#include "Server.hpp"
using namespace aclolinta::server;

#include "../utility/Singleton.hpp"
using namespace aclolinta::utility;

#include "../task/TaskDispatcher.hpp"
using namespace aclolinta::task;

#include "../socket/SocketHandler.hpp"
using namespace aclolinta::socket;

Server::Server()
    : m_ip(""), m_port(0), m_threads(1024), m_connects(1024), m_wait_time(10) {}

Server::~Server() {}

void Server::Listen(std::string_view ip, size_t port) {
    m_ip = ip;
    m_port = port;
}
void Server::SetThreads(size_t threads) { m_threads = threads; }

void Server::SetConnects(size_t connects) { m_connects = connects; }

void Server::SetWaitTimes(size_t wait_time) { m_wait_time = wait_time; }

void Server::Start() {
    // 初始化线程池和任务队列
    TaskDispatcher* dispatcher = Singleton<TaskDispatcher>::Getinstance();
    dispatcher->Init(m_threads);

    // 初始化Socket handler
    SocketHandler* socket_handler = Singleton<SocketHandler>::Getinstance();
    socket_handler->Listen(m_ip, m_port);
    socket_handler->Handle(m_connects, m_wait_time);
}