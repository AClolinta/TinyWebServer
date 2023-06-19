/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:57:23
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 11:11:33
 * @FilePath: /TinyWebServer/utility/Singleton.hpp
 * @Description: C++11标准的线程安全的单例模板
 * */
#pragma once
// #include <assert.h>
// #include <pthread.h>
#include <mutex>

namespace aclolinta {
namespace utility {

template <typename T>
class Singleton {
   public:
    static T *Getinstance() {
        std::call_once(m_onceFlag, []() { m_instance = new T(); });
        // static T *m_instance = new T();
        return m_instance;
    }

    // static void Init() { m_instance = new T(); }

   private:
    Singleton() = default;
    Singleton(const Singleton<T> &) = delete;
    Singleton<T> &operator=(const Singleton<T> &);
    ~Singleton() = default;

   private:
    static std::once_flag m_onceFlag;
    static T *m_instance;
    //     static pthread_once_t m_ponce;
    //     static T *m_instance;
};

template <typename T>
std::once_flag Singleton<T>::m_onceFlag;

template <typename T>
T *Singleton<T>::m_instance = nullptr;

// template <typename T>
// pthread_once_t Singleton<T>::m_ponce = PTHREAD_ONCE_INIT;

}  // namespace utility
}  // namespace aclolinta