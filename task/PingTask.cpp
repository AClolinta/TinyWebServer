/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 13:40:41
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 07:39:32
 * @FilePath: /TinyWebServer/task/PingTask.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "PingTask.hpp"

#include "../logger/log.hpp"
using namespace aclolinta::logger;

#include "../utility/Singleton.hpp"

using namespace aclolinta::utility;

#include "../socket/SocketHandler.hpp"
using namespace aclolinta::socket;

#include "cstdio"
#include "unistd.h"

PingTask::PingTask(Socket* socket) : Task(socket) {}

PingTask::~PingTask() {}

void PingTask::Run(){
    debug("TASK PING IS RUNNING");
    SocketHandler* handle_ = Singleton<SocketHandler>::Getinstance();

    Socket* socket_ = static_cast<Socket*>(m_data);
    char buf[8192];
    memset(buf, 0, 8192);
    int len_ = socket_->Recv(buf,8192);
    if(len_ > 0){
        debug("RECV MSG LEN: %d", len_);
        socket_->Send("+OK\r\n", 5);
        handle_->Attach(socket_);
    } else {
        debug("TASK PING SOCKET CLOSED BY PEER");
        handle_->Remove(socket_);
    }
}

void PingTask::Destroy() {
    debug("TASK PING DESTROY");
    delete this;
}