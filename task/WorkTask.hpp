/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-07 03:33:31
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:26:15
 * @FilePath: /TinyWebServer/task/WorkTask.hpp
 * @Description: 工作任务的定义
 *  */
#pragma once

#include "Task.hpp"
using namespace aclolinta::task;

#include "Socket.hpp"
using namespace aclolinta::socket;

namespace aclolinta {
namespace task {

struct MsgHead {
    char flag[8];
    uint32_t cmd;
    uint32_t len;
};

const uint32_t recv_buff_size = 1024;

class WorkTask : public Task {
   private:
    /* data */
   public:
    WorkTask(Socket* socket);
    virtual ~WorkTask();

   public:
    virtual void Run();
    virtual void Destroy();
};

}  // namespace task
}  // namespace aclolinta