/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-31 02:34:47
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 13:58:27
 * @FilePath: /TinyWebServer/thread/WorkerThread.cpp
 * @Description: 具体的工作线程类
 *  */
#include "WorkThread.hpp"

#include "../log/log.hpp"
using namespace aclolinta::logger;
#include "../utility/Singleton.hpp"
using namespace aclolinta::utility;

#include "../task/Task.hpp"
using namespace aclolinta::task;

#include "ThreadPool.hpp"
using namespace aclolinta::thread;

WorkThread::WorkThread() : Thread(){};

WorkThread::~WorkThread(){};

void WorkThread::CleanUP(void* ptr) {
    info("WORKER THREAD CLEANUP HANDLER: %x", ptr);
}

void WorkThread::Run() {
    sigset_t mask;

    if (0 != sigfillset(&mask)) {
        // 添加信号集
        errorr("WORK THREAD SIGFILLSET FAILE!");
    }

    if (0 != pthread_sigmask(SIG_SETMASK, &mask, nullptr)) {
        // 将线程的信号掩码设置为 mask 中的信号集合。
        errorr("WORK THREAD PTHREAD_SIGMASK FAILE!");
    }

    pthread_cleanup_push(CleanUP, this);
    while (true) {
        //等待任务队列中任务的到来
        m_mutex.Lock();
        while( m_task == nullptr){
            // 任务没来,等在信号量m_mutex上的通知
            m_cond.Wait(&m_mutex);
        }
        m_mutex.Unlock();
        //获取到任务，等待结束

        int rc = 0;
        int old_state = 0;
        //线程不允许被取消（中断）
        rc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_state);
        //执行线程的逻辑
        m_task->Run();
        m_task->Destory();
        m_task = nullptr;

        Singleton<ThreadPool>::Getinstance()->Move2IdleList(this);

        rc = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_state);
        pthread_testcancel();

    }
    pthread_cleanup_pop(1);
}