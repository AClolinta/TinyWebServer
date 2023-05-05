/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 13:10:57
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-05 13:23:07
 * @FilePath: /TinyWebServer/task/EchoTask.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "EchoTask.hpp"
using namespace aclolinta::task;

#include "../log/log.hpp"
using namespace aclolinta::logger;

#include "../utility/Singleton.hpp"

using namespace aclolinta::utility;

#include "../socket/SocketHandler.hpp"
using namespace aclolinta::socket;

#include <vector>


EchoTask::EchoTask(Socket* socket) : Task(socket) {}

EchoTask::~EchoTask() {}

void EchoTask::Run(){
    debug("ECHO TASK RUN!");
    SocketHandler* handle_ = Singleton<SocketHandler>::Getinstance();

    Socket * socket_ = static_cast<Socket*>(m_data);
    char buf[1024];
    memset(buf, 0, 1024);
    int len_ = socket_->Recv(buf,1024);//获取Socket文件描述符
    if (len_ > 0) {
        debug("RECV MSG LEN: %d MSG DATA: %s", len_, buf);
        socket_->Send(buf, len_);//发送
        handle_->Attach(socket_);//将发送送入epoll队列
    } else {
        debug("echo task socket closed by peer");
        handle_->Remove(socket_);
    }
}

void EchoTask::Destory() {
    debug("ECHO TASK DESTROY");
    delete this;
}
