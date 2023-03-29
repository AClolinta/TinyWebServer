/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:53:05
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 12:19:28
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

    int Wait(Mutex* mutex);
    int Signal();
    int Broadcast();
};

}  // namespace thread
}  // namespace aclolinta