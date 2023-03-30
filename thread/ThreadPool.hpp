/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-30 13:21:56
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-30 13:28:34
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

namespace aclolinta {
namespace thread {
class ThreadPool {
   private:
    /* data */
    int m_threads;//Thread count

    std::set<Thread *> m_list_idle;//Idle thread
    std::set<Thread *> m_list_busy;//busy thread

    Mutex m_mutex_idle;
    Mutex m_mutex_busy;

    Condition m_cond_idle;
    Condition m_busy_idle;

   public:
    ThreadPool(/* args */);
    ~ThreadPool();
};

}  // namespace thread
}  // namespace aclolinta