/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 12:34:49
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 13:54:07
 * @FilePath: /TinyWebServer/task/Task.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Task.hpp"

#include "../thread/AutoLock.hpp"

using namespace aclolinta::task;

Task::Task() : m_data(nullptr){};

Task::Task(void* data) : m_data(data){};

Task::~Task(){};

void* Task::GetData() {
    AutoLock lock(&m_mutex);
    return m_data;
}

void Task::SetData(void* data) {
    AutoLock lock(&m_mutex);
    m_data = data;
}