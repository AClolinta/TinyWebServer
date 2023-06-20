/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-13 01:59:50
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 12:53:55
 * @FilePath: /TinyWebServer/system/system.cpp
 * @Description: 核心部分
 * */
#include "system.hpp"

using namespace aclolinta;
using namespace aclolinta::sys;

#include <dirent.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Singleton.hpp"
#include "iniFile.hpp"
using namespace aclolinta::utility;

#include "log.hpp"
using namespace aclolinta::logger;

#include "WorkFlow.hpp"
using namespace aclolinta::engine;

System::System() {}

System::~System() {}

/// @brief 初始化系统，读入系统路径
void System::Init() {
    CoreDump();

    m_root_path = GetRootPath();
    std::string logdir = m_root_path + "/log";

    DIR* dp = opendir(logdir.c_str());
    if (dp == NULL) {
        mkdir(logdir.c_str(), 0755);
    } else {
        closedir(dp);
    }

    //Logger
    Logger::GetInstance()->Open(m_root_path + "/log/main.log");

    //Inifile
    IniFile * ini = Singleton<IniFile>::Getinstance();
    ini->Load(GetRootPath() + "/config/main.ini");

    //Init WorkFolw
    WorkFlow* workflow = Singleton<WorkFlow>::Getinstance();
    workflow->Load(GetRootPath() + "/config/workflow.xml");

}

/// @brief 获取系统运行的路径
/// @return String
std::string System::GetRootPath() {
    if (m_root_path != "") {
        return m_root_path;
    }
    /// proc/self/exe 它代表当前程序
    char path[1024];
    memset(path, 0, 1024);
    ssize_t cnt = readlink("/proc/self/exe", path, sizeof(path));

    if (cnt < 0 || cnt >= (ssize_t)sizeof(path)) {
        return "";  // 异常
    }

    for (ssize_t i = cnt; i >= 0; --i) {
        if (path[i] == '/') {
            path[i] = '\0';
            break;
        }
    }
    return std::string(path);
}

void System::CoreDump(){
    // core dump
    struct rlimit x;
    int ret = getrlimit(RLIMIT_CORE, &x);
    x.rlim_cur = x.rlim_max;
    ret = setrlimit(RLIMIT_CORE, &x);

    ret = getrlimit(RLIMIT_DATA, &x);
    x.rlim_cur = 768000000;
    ret = setrlimit(RLIMIT_DATA, &x);
}