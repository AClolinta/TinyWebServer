
/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 12:35:59
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 12:41:18
 * @FilePath: /TinyWebServer/thread/AutoLock.hpp
 * @Description: 构造时上锁，析构时解锁*/
#pragma once

#include "Mutex.hpp"

namespace aclolinta {
namespace thread {
class AutoLock {
   private:
    /* data */
    Mutex* m_mutex;
   public:
    AutoLock(Mutex* mutex);
    ~AutoLock();
};


}  // namespace thread
}  // namespace aclolinta