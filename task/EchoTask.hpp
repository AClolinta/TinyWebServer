/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 13:01:10
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-05 13:05:59
 * @FilePath: /TinyWebServer/task/EchoTask.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include "../task/Task.hpp"
using namespace aclolinta::task;

#include "../socket/Socket.hpp"
using namespace aclolinta::socket;

namespace aclolinta {
namespace task {
class EchoTask : public Task{
   private:
    /* data */
   public:
    EchoTask(Socket* socket);
    virtual  ~EchoTask();

    public:
     virtual void Run();
     virtual void Destory();
};

}  // namespace task
}  // namespace aclolinta
