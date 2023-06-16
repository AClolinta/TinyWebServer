/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-07 03:35:51
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 11:44:33
 * @FilePath: /TinyWebServer/task/WorkTask.cpp
 * @Description: 每个任务的安全性检查，随后送入
 */
#include "WorkTask.hpp"

#include "../log/log.hpp"
using namespace aclolinta::logger;

#include "../utility/Singleton.hpp"
using namespace aclolinta::utility;

#include "../socket/SocketHandler.hpp"
using namespace aclolinta::socket;

#include "../engine/WorkFlow.hpp"
using namespace aclolinta::engine;

#include <sstream>

using namespace aclolinta::task;

WorkTask::WorkTask(Socket* socket) : Task(socket) {}

WorkTask::~WorkTask() {}

void WorkTask::Run() {
    debug("WORK TASK IS RUNING");
    SocketHandler* handle_ = Singleton<SocketHandler>::Getinstance();

    Socket* socket_ = static_cast<Socket*>(m_data);
    MsgHead msg_head_;
    memset(&msg_head_, 0, sizeof(msg_head_));

    int len_ = socket_->Recv((char*)(&msg_head_), sizeof(msg_head_));
    // 接受消息头部并且检查
    //  如果 len 为 0，表示套接字已被对方关闭，输出错误日志，并从 handler
    //  中移除该套接字。
    if (0 == len_) {
        errorr("SOCKET CLOSED BY PEER");
        handle_->Remove(socket_);
        return;
    }

    // 如果 len 为 -1，且 errno 为 EAGAIN、EWOULDBLOCK 或
    // EINTR，表示接收操作暂时不可用，输出错误日志，并将套接字重新添加到 handler
    // 中

    if (len_ == -1 && errno == EAGAIN) {
        // 表示"Resource temporarily
        // unavailable"，当前操作无法立即完成，因为所需的资源当前不可用。
        errorr("SOCKET RECV LEN: %d, ERROR MSG: EAGAIN ERRNO: %d", len_, errno);
        handle_->Attach(socket_);
        return;
    }
    if (len_ == -1 && errno == EWOULDBLOCK) {
        // EWOULDBLOCK是一个表示"操作将阻塞"的错误代码，通常用于非阻塞操作
        errorr("SOCKET RECV LEN: %d, ERROR MSG: EWOULDBLOCK ERRNO: %d", len_,
               errno);
        handle_->Attach(socket_);
        return;
    }
    if (len_ == -1 && errno == EINTR) {
        // EINTR是一个表示"系统调用被中断"的错误代码
        errorr("SOCKET RECV LEN: %d, ERROR MSG: EINTR ERRNO: %d", len_, errno);
        handle_->Attach(socket_);
        return;
    }
    // 接收到的消息头长度有误,移除该Socket
    if (len_ != sizeof(msg_head_)) {
        errorr("recv msg head error length: %d, errno: %d", len_, errno);
        handle_->Remove(socket_);
        return;
    }
    info("REVC MSG HEAD LEN : %d, FLAF : %s, cmd: %d, body len: %d", len_,
         msg_head_.flag, msg_head_.cmd, msg_head_.len);

    // 检查消息头的标志是否为 "work"，如果不是，则输出错误日志，并从 handler
    // 中移除该套接字。
    if (strncmp(msg_head_.flag, "work", 4) != 0) {
        errorr("MSG HEAD FLAG ERROR: NO WORK SING");
        handle_->Remove(socket_);
        return;
    }
    // 检查消息体长度是否大于等于 recv_buff_size，如果是，则输出错误日志，并从
    // handler 中移除该套接字。
    if (msg_head_.len >= static_cast<uint32_t>(recv_buff_size)) {
        errorr("UNEXPECT RECV MSG BODY LEN: %d, RECV_BUFF_SIZE IS : %d",
               msg_head_.len, recv_buff_size);
        handle_->Remove(socket_);
        return;
    }
    // 安全性检查完成

    char buf[recv_buff_size];
    memset(buf, 0, recv_buff_size);
    len_ = socket_->Recv(buf, msg_head_.len);

    if (len_ == -1 && errno == EAGAIN) {
        errorr("SOCKET RECV LEN: %d, ERROR MSG: EAGAIN ERRNO: %d", len_, errno);
        handle_->Remove(socket_);
        return;
    }
    if (len_ == -1 && errno == EWOULDBLOCK) {
        errorr("SOCKET RECV LEN: %d, ERROR MSG: EWOULDBLOCK ERRNO: %d", len_,
               errno);
        handle_->Remove(socket_);
        return;
    }
    if (len_ == -1 && errno == EINTR) {
        errorr("SOCKET RECV LEN: %d, ERROR MSG: EINTR ERRNO: %d", len_, errno);
        handle_->Remove(socket_);
        return;
    }
    if (len_ != (int)(msg_head_.len)) {
        errorr("RECV MSG BODY ERROR LENGTH: %d, BODY: %s, ERRNO: %d", len_, buf,
               errno);
        handle_->Remove(socket_);
        return;
    }
    info("RECV MSG BODY LEN: %d, MSG DATA: %s", len_, buf);

    WorkFlow* workflow_ = Singleton<WorkFlow>::Getinstance();
    ostringstream oss;
    oss << static_cast<int>(msg_head_.cmd);
    string_view work_ = oss.str();
    string_view input_ = buf;
    string output_;

    workflow_->Run(work_, input_, output_);
    socket_->Send(output_.c_str(), output_.size());
    handle_->Attach(socket_);
}

void WorkTask::Destroy() {
    debug("WORK JOB DESTORY");
    delete this;
}