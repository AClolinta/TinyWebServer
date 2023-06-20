/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 13:39:05
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:25:22
 * @FilePath: /TinyWebServer/task/PingTask.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include "Task.hpp"
using namespace aclolinta::task;

#include "Socket.hpp"
using namespace aclolinta::socket;

namespace aclolinta {
namespace task {
class PingTask : public Task {
   private:
    /* data */
   public:
    PingTask(Socket* socket);
    ~PingTask();

   public:
    virtual void Run();
    virtual void Destroy();
};

}  // namespace task
}  // namespace aclolinta
