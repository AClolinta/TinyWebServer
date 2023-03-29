#include "Task.hpp"

#include "AutoLock.hpp"

using namespace aclolinta::thread;

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