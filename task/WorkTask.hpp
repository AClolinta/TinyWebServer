/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-07 03:33:31
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-07 03:35:46
 * @FilePath: /TinyWebServer/task/WorkTask.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include "../task/Task.hpp"
using namespace aclolinta::task;

#include "../socket/Socket.hpp"
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