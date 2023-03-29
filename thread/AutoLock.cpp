/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 12:36:06
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 12:44:01
 * @FilePath: /TinyWebServer/thread/AutoLock.cpp
 * @Description: AutoLock的实现
 * */
#include "AutoLock.hpp"

using namespace aclolinta::thread;

AutoLock::AutoLock(Mutex* mutex){
    m_mutex = mutex;
    m_mutex->Lock();
}

AutoLock::~AutoLock(){
    m_mutex->Unlock();
}