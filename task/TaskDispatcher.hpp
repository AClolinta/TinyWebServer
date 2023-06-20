
/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-30 13:18:57
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:25:39
 * @FilePath: /TinyWebServer/thread/TaskDispatcher.hpp
 * @Description: 任务分发类
 * */
#pragma once

#include <pthread.h>
#include <signal.h>

#include <list>

#include "Task.hpp"
#include "Thread.hpp"
#include "ThreadPool.hpp"

using namespace aclolinta::task;

namespace aclolinta {
namespace thread {
class TaskDispatcher : public Thread {
   private:
    /* data */
    std::list<Task*> m_tasks;

   public:
    TaskDispatcher(/* args */);
    ~TaskDispatcher();

   public:
    void Init(size_t threads);
    void Assign(Task* task);  // 将任务添加到任务列表中。
    void Handle(Task* task);  // 处理指定的任务。

    virtual void Run();
};

}  // namespace thread
}  // namespace aclolinta