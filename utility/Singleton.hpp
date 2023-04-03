/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:57:23
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 11:49:01
 * @FilePath: /TinyWebServer/utility/Singleton.hpp
 * @Description: 线程安全的单例模板
 * */
#pragma once
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>  // atexit

namespace aclolinta {
namespace utility {

template <typename T>
class Singleton {
   public:
    static T *Getinstance() {
        pthread_once(&m_ponce, &Singleton::Init);
        return m_instance;
    }

    static void Init() { m_instance = new T(); }

   private:
    Singleton() {}
    Singleton(const Singleton<T> &);
    Singleton<T> &operator=(const Singleton<T> &);
    ~Singleton() {}

   private:
    static pthread_once_t m_ponce;
    static T *m_instance;
};

template <typename T>
T *Singleton<T>::m_instance = nullptr;

template <typename T>
pthread_once_t Singleton<T>::m_ponce = PTHREAD_ONCE_INIT;

}  // namespace utility
}  // namespace aclolinta