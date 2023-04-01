/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:57:23
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-01 03:11:29
 * @FilePath: /TinyWebServer/utility/Singleton.hpp
 * @Description: 单例模板
 * */
#pragma once

namespace aclolinta {
namespace utility {

template <typename T>
class Singleton {
   public:
    static T *Getinstance() {
        if (m_instance == nullptr) {
            m_instance = new T();
            // std::atexit(T::Close);
        };
        return m_instance;
    }

   private:
    Singleton() {}
    Singleton(const Singleton<T> &);
    Singleton<T> &operator=(const Singleton<T> &);
    ~Singleton() {}

   private:
    static T *m_instance;
};

template <typename T>
T *Singleton<T>::m_instance = nullptr;

}  // namespace utility
}  // namespace aclolinta