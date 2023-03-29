/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:42:41
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 11:59:01
 * @FilePath: /TinyWebServer/thread/Mutex.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置:利用pthread实现Mutex
 * */
#include "Mutex.hpp"

using namespace aclolinta::thread;

Mutex::Mutex() {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    // PTHREAD_MUTEX_ERRORCHECK，则会提供死锁检查。
    // 如果某个线程尝试重新锁定的互斥锁已经由该线程锁定，则将返回错误。
    // 如果某个线程尝试解除锁定的互斥锁不是由该线程锁定或者未锁定，则将返回错误。
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_init(&m_mutex, &attr);  // 初始化m_mutex
    pthread_mutexattr_destroy(&attr);  // 销毁 attr 变量，释放资源。
}

Mutex::~Mutex() { pthread_mutex_destroy(&m_mutex); }

int Mutex::TryLock() { return pthread_mutex_trylock(&m_mutex); }

int Mutex::Unlock() { return pthread_mutex_unlock(&m_mutex); }

int Mutex::Lock() { return pthread_mutex_lock(&m_mutex); }