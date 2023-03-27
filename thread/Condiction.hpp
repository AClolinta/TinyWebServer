/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-27 03:53:05
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-27 03:55:53
 * @FilePath: /TinyWebServer/thread/Condiction.hpp
 * @Description: 条件变量
 * */
#pragma once
#include <pthread.h>

namespace aclolinta {
namespace thread {
class Condiction {
   private:
    /* data */
    pthread_cond_t m_cond;

   public:
    Condiction(/* args */);
    ~Condiction();

    int Wait();
    int Signal();
    int Broadcast();
};

}  // namespace thread
}  // namespace aclolinta