/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 13:05:10
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-30 08:48:42
 * @FilePath: /TinyWebServer/thread/Thread.cpp
 * @Description: 线程框架的实现
 *  */
#include "Thread.hpp"

#include "AutoLock.hpp"

using namespace aclolinta::thread;

Thread::Thread() : m_tid(0), m_task(nullptr){};

Thread::~Thread(){};

void Thread::Start() {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    // 作用域设置为 PTHREAD_SCOPE_SYSTEM，此线程将与系统中的所有线程进行竞争
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // 线程在结束时可以自动释放所有资源,该线程一退出，便可重用其线程 ID
    // 和其他资源。
    pthread_create(&m_tid, &attr, ThreadFunc, (void*)this);
    pthread_attr_destroy(&attr);
}

void Thread::Stop() {
    pthread_exit(PTHREAD_CANCELED);
    // 当一个线程被强制终止执行时，它会返回 PTHREAD_CANCELED 这个宏
    }