/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:40:47
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 13:55:04
 * @FilePath: /TinyWebServer/thread/Thread.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: Thread的基类 */
#pragma once
#include <pthread.h>

#include "Condition.hpp"
#include "Mutex.hpp"
#include "../task/Task.hpp"

using namespace aclolinta::task;

namespace aclolinta {
namespace thread {
class Thread {
   public:
    Thread(/* args */);
    ~Thread();

    virtual void Run() = 0;

    void Start();
    void Stop();

    void SetTask(Task* task);
    Task* GetTask();

   protected:
    static void* ThreadFunc(void* ptr);

   protected:
    pthread_t m_tid;   // 线程ID
    Task* m_task;      // 具体任务
    Mutex m_mutex;     // 互斥信号量
    Condition m_cond;  // 线程通讯工具
};
}  // namespace thread
}  // namespace aclolinta
