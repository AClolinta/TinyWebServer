/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:58:53
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 12:49:21
 * @FilePath: /TinyWebServer/system/system.hpp
 * @Description: System工具类
 *
 */
#pragma once

#include <string>

#include "system.hpp"

// using namespace aclolinta::system;



namespace aclolinta {
namespace system {
class System {
   private:
    /* data */
    std::string m_root_path;

   private:
    /// @brief 生成CoreDump文件
    void CoreDump();

   public:
    System(/* args */);
    ~System();

    void Init();

    /// @brief 获取系统路径
    /// @return std::string
    std::string GetRootPath();

    static void Close();
};

}  // namespace system
}  // namespace aclolinta