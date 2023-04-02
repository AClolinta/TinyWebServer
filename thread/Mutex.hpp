/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:42:28
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-02 02:40:48
 * @FilePath: /TinyWebServer/thread/Mutex.hpp
 * @Description: Mutex互斥锁的实现
 * */
#pragma once
#include <pthread.h>

namespace aclolinta {
namespace thread {

class Mutex {
    friend class Condition;

   private:
    /* data */
    pthread_mutex_t m_mutex;

   public:
    Mutex(/* args */);
    ~Mutex();
    //
    int Lock();

    int TryLock();

    int Unlock();
};

}  // namespace thread
}  // namespace aclolinta
