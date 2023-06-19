/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 12:06:35
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 09:59:10
 * @FilePath: /TinyWebServer/utility/ObjectPool.hpp
 * @Description:  对象池
 *  */
#pragma once

#include <list>

#include "../thread/AutoLock.hpp"
#include "../thread/Mutex.hpp"

using namespace aclolinta::thread;

namespace aclolinta {
namespace utility {
template <class T>
class ObjectPool {
   private:
    /* data */
    std::list<T*> m_pool;
    Mutex m_mutex;

   public:
    ObjectPool(/* args */);
    ~ObjectPool();

   public:
    void Init(size_t max);
    T* Allocate();
    void Release(T* ptr);
};

template <class T>
ObjectPool<T>::ObjectPool(){};

template <class T>
ObjectPool<T>::~ObjectPool() {
    AutoLock lock(&m_mutex);
    for (auto it = m_pool.begin(); it != m_pool.end(); ++it) {
        if (nullptr != (*it)) {
            delete (*it);
        }
    }
    m_pool.clear();
};

template <class T>
void ObjectPool<T>::Init(size_t max) {
    AutoLock lock(&m_mutex);
    for (size_t i = 0; i < max; ++i) {
        T* ptr = new T();
        m_pool.push_back(ptr);
    }
}

template <class T>
T* ObjectPool<T>::Allocate() {
    AutoLock lock(&m_mutex);
    if (0 == m_pool.size()) {
        return nullptr;
    }
    T* ptr = m_pool.front();
    m_pool.pop_front();
    return ptr;
}
template <class T>
void ObjectPool<T>::Release(T* ptr) {
    AutoLock lock(&m_mutex);
    m_pool.push_back(ptr);
}

}  // namespace utility
}  // namespace aclolinta