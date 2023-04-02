/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:53:05
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-02 02:49:18
 * @FilePath: /TinyWebServer/thread/Condiction.hpp
 * @Description: 条件变量,实现的是线程之间的通信
 * */
#pragma once
#include <pthread.h>
#include "Mutex.hpp"

namespace aclolinta {
namespace thread {
class Condition {
   private:
    /* data */
    pthread_cond_t m_cond;

   public:
    Condition(/* args */);
    ~Condition();

    int Wait(Mutex* mutex);  // 用于保护该条件变量的互斥锁
    int Signal();
    int Broadcast();
};

}  // namespace thread
}  // namespace aclolinta