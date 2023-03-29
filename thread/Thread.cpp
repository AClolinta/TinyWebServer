/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 13:05:10
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 13:06:45
 * @FilePath: /TinyWebServer/thread/Thread.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 线程框架的实现
 *  */
#include "Thread.hpp"

#include "AutoLock.hpp"

using namespace aclolinta::thread;

Thread::Thread() : m_tid(0), m_task(nullptr){};