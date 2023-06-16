/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 13:01:10
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 03:19:29
 * @FilePath: /TinyWebServer/task/EchoTask.hpp
 * @Description: 回显 */
#pragma once

#include "../task/Task.hpp"
using namespace aclolinta::task;

#include "../socket/Socket.hpp"
using namespace aclolinta::socket;

namespace aclolinta {
namespace task {
class EchoTask : public Task {
   private:
    /* data */
   public:
    EchoTask(Socket* socket);
    virtual ~EchoTask();

   public:
    virtual void Run();
    virtual void Destroy();
};

}  // namespace task
}  // namespace aclolinta
