#include "TaskDispatcher.hpp"
#include "../log/log.hpp"
#include "../utility/Singleton.hpp"

using namespace aclolinta::utility;
using namespace aclolinta::logger;
using namespace aclolinta::thread;

TaskDispatcher::TaskDispatcher() {};

TaskDispatcher::~TaskDispatcher() {};

void TaskDispatcher::Init(size_t threads){
    Singleton<ThreadPool>::Getinstance()->Creat(threads);
    this->Start();
}

void TaskDispatcher::Assign(Task* task){
    debug("TASK DISPATCHER TASK ASSIGNED");
    m_mutex.Lock();
    m_tasks.push_back(task);
    m_mutex.Unlock();
    m_cond.Signal();
}