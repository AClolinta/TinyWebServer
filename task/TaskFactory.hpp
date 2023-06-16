/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 13:19:08
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-05 04:13:26
 * @FilePath: /TinyWebServer/task/TaskFactory.hpp
 * @Description: 任务工厂的设计模式，用于创建特定类型的任务对象*/
#pragma once

#include "../socket/Socket.hpp"

using namespace aclolinta::socket;

#include "../task/Task.hpp"
using namespace aclolinta::thread;

#include "EchoTask.hpp"
#include "PingTask.hpp"
#include "WorkTask.hpp"

namespace aclolinta {
namespace task {
class TaskFactory {
   public:
     static Task * Create(Socket * socket){
        return new WorkTask(socket);
     }

};

}  // namespace task
}  // namespace aclolinta