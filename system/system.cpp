/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-13 01:59:50
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-27 03:37:21
 * @FilePath: /TinyWebServer/system/system.cpp
 * @Description: 
 * */
#include "system.hpp"

using namespace aclolinta;
using namespace aclolinta::system;

#include <dirent.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../log/log.hpp"
#include "../utility/Singleton.hpp"
#include "../utility/iniFile.hpp"

System::System() {}

System::~System() {}

/// @brief 初始化系统，读入系统路径
void System::Init() {
    CoreDump();

    m_root_path = GetRootPath();
    std::string logdir = m_root_path + "/log";
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

    if (cnt < 0 || cnt >= sizeof(path)) {
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