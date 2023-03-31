/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-31 02:34:41
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-31 02:46:41
 * @FilePath: /TinyWebServer/thread/WorkerThread.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: 具体的工作线程类*/
#pragma once

#include <pthread.h>
#include <signal.h>

#include "Thread.hpp"

namespace aclolinta {
namespace thread {
class WorkThread : public Thread{
   private:
    /* data */
   public:
    WorkThread(/* args */);
    virtual ~WorkThread();

    virtual void Run();

    static void CleanUP(void* ptr);
};

}  // namespace thread
}  // namespace aclolinta