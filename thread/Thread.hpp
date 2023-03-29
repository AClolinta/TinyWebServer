/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:40:47
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 13:10:02
 * @FilePath: /TinyWebServer/thread/Thread.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <pthread.h>

#include "Condition.hpp"
#include "Mutex.hpp"
#include "Task.hpp"

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
    Mutex m_mutes;     // 互斥信号量
    Condition m_cond;  // 线程通讯工具
};
}  // namespace thread
}  // namespace aclolinta
