/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 12:06:55
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-29 12:25:29
 * @FilePath: /TinyWebServer/thread/Condition.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Condition.hpp"

using namespace aclolinta::thread;

Condition::Condition() {
    // 缺省值为 PTHREAD_PROCESS_PRIVATE,即用于仅同步该进程中的线程
    pthread_cond_init(&m_cond, NULL);
}

Condition::~Condition() { pthread_cond_destroy(&m_cond); }

int Condition::Wait(Mutex* mutex) {
    return pthread_cond_wait(&m_cond, &(mutex->m_mutex));
}

int Condition::Signal() { return pthread_cond_signal(&m_cond); }

int Condition::Broadcast() { return pthread_cond_broadcast(&m_cond); }