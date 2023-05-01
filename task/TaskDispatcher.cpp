/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-30 13:19:03
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-04 14:01:44
 * @FilePath: /TinyWebServer/thread/TaskDispatcher.cpp
 * @Description:  任务分配器具体实现
 * */
#include "TaskDispatcher.hpp"

#include "../log/log.hpp"
#include "../utility/Singleton.hpp"

using namespace aclolinta::utility;
using namespace aclolinta::logger;
using namespace aclolinta::thread;

TaskDispatcher::TaskDispatcher(){};

TaskDispatcher::~TaskDispatcher(){};

/**
 * @description: 启动任务分配器
 * @param {size_t} threads 线程数量
 * @return {*}
 */
void TaskDispatcher::Init(size_t threads) {
    Singleton<ThreadPool>::Getinstance()->Creat(threads);
    this->Start();
}

void TaskDispatcher::Assign(Task* task) {
    debug("TASK DISPATCHER TASK ASSIGNED");
    m_mutex.Lock();
    m_tasks.push_back(task);
    m_mutex.Unlock();
    m_cond.Signal();
}

void TaskDispatcher::Handle(Task* task) {
    debug("HANDLE TASK IN TASK DISPATCHER");

    ThreadPool* threadpool_ = Singleton<ThreadPool>::Getinstance();

    if (threadpool_->GetIdleThreadCount() > 0) {
        threadpool_->Assign(task);
    } else {
        debug("ALL THREADS ARE BUSY!");
        m_mutex.Lock();
        m_tasks.push_front(task);
        m_mutex.Unlock();
    }
}

void TaskDispatcher::Run() {
    sigset_t mask;

    if (0 != sigfillset(&mask)) {
        // 添加信号集
        errorr("TASKDISPATCHER SIGFILLSET FAILE!");
        return;
    }

    if (0 != pthread_sigmask(SIG_SETMASK, &mask, nullptr)) {
        // 将线程的信号掩码设置为 mask 中的信号集合。
        errorr("TASKDISPATCHER PTHREAD_SIGMASK FAILE!");
        return;
    }

    while (true) {
        
        //队列上锁
        m_mutex.Lock();
        while (m_tasks.empty()) {
            //没任务的时候等待cond的通知
            m_cond.Wait(&m_mutex);
        }

        Task* task_ = m_tasks.front();
        m_tasks.pop_front();
        m_mutex.Unlock();
        // 队列释放锁

        this->Handle(task_);//执行任务
    }
}