/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-29 12:34:49
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:25:22
 * @FilePath: /TinyWebServer/task/Task.cpp
 * @Description: Task,任务类
 */
#include "Task.hpp"

#include "AutoLock.hpp"

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