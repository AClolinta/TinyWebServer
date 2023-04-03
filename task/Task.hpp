/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 12:26:56
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 13:53:33
 * @FilePath: /TinyWebServer/thread/Task.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include "../thread/Mutex.hpp"
// #include "Mutex.hpp"
using namespace aclolinta::thread;

namespace aclolinta {
namespace task {
class Task {
   public:
    Task(/* args */);
    Task(void* m_data);
    virtual ~Task();

    void* GetData();
    void SetData(void* data);

    virtual void Run() = 0;
    virtual void Destory() = 0;

   protected:
    void* m_data;
    Mutex m_mutex;
};

}  // namespace thread
}  // namespace aclolinta