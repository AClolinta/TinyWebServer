/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-30 13:22:02
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-31 04:22:15
 * @FilePath: /TinyWebServer/thread/ThreadPool.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ThreadPool.hpp"

#include "../log/log.hpp"
#include "WorkerThread.hpp"

using namespace aclolinta::logger;
using namespace aclolinta::thread;

ThreadPool::ThreadPool() : m_threads(0) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::Creat(int thread_counts) {
    AutoLock lock(&m_mutex_idle);

    m_threads = thread_counts;
    for (size_t i = 0; i < m_threads; ++i) {
        Thread* thread_ = new WorkThread();
        debug("create thread %x", thread_);
        m_list_idle.emplace(thread_);
        thread_->Start();
    }
}

/// @brief 从线程池的空闲线程列表中获取一个空闲线程
/// @return Thread *
Thread* ThreadPool::GetIdleThread() {
    AutoLock lock(&m_mutex_idle);
    while (0 == m_list_idle.size()) {
        // 等待有空闲线程被加入到列表中
        m_cond_idle.Wait(&m_mutex_busy);
    }
    return *m_list_idle.begin();
}

/// @brief 将一个忙碌线程移动到线程池的空闲线程列表，先插入再移除
void ThreadPool::Move2IdleList(Thread* thread) {
    // 上锁空闲队列
    m_mutex_idle.Lock();
    m_list_idle.emplace(std::move(thread));
    m_cond_idle.Signal();//通知空闲队列
    m_mutex_idle.Unlock();
    // 解锁空闲队列

    //上锁busy队列
    m_mutex_busy.Lock();
    if (0 != m_list_busy.count(thread)) m_list_busy.erase(m_list_busy.find(thread));
    m_cond_busy.Signal();
    m_mutex_busy.Unlock();
    // 解锁busy队列
}