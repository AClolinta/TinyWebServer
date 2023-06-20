/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-30 13:21:56
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:27:09
 * @FilePath: /TinyWebServer/thread/ThreadPool.hpp
 * @Description: 线程池
 * */
#pragma once

#include <set>

#include "AutoLock.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "Task.hpp"
#include "Thread.hpp"

using namespace aclolinta::task;

namespace aclolinta {
namespace thread {
class ThreadPool {
   private:
    /* data */
    size_t m_threads;//Thread count

    std::set<Thread *> m_list_idle;//Idle thread
    std::set<Thread *> m_list_busy;//busy thread

    Mutex m_mutex_idle;
    Mutex m_mutex_busy;

    Condition m_cond_idle;
    Condition m_cond_busy;

   public:
    ThreadPool(/* args */);
    ~ThreadPool();

   public:
    void Creat(int thread_count);
    Thread* GetIdleThread();

    void Move2IdleList(Thread *thread);
    void Move2BusyList(Thread *thread);

    size_t GetIdleThreadCount();
    size_t GetBusyThreadCount();

    void Assign(Task* task); //分配任务
};

}  // namespace thread
}  // namespace aclolinta