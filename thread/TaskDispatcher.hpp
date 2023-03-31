
/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-30 13:18:57
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-31 12:56:11
 * @FilePath: /TinyWebServer/thread/TaskDispatcher.hpp
 * @Description: 任务分发类
 * */
#pragma once

#include <pthread.h>
#include <signal.h>

#include <vector>

#include "Task.hpp"
#include "Thread.hpp"
#include "ThreadPool.hpp"

namespace aclolinta {
namespace thread {
class TaskDispatcher : public Thread {
   private:
    /* data */
    std::vector<Task*> m_tasks;

   public:
    TaskDispatcher(/* args */);
    ~TaskDispatcher();

   public:
    void Init(size_t threads);
    void Assign(Task* task);
    void Handle(Task* task);

    virtual void Run();
};

}  // namespace thread
}  // namespace aclolinta