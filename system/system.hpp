/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:58:53
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-11 04:20:42
 * @FilePath: /TinyWebServer/system/system.hpp
 * @Description: System工具类
 * 
 */
#pragma once

#include <string>

namespace aclolinta {
namespace system {
class System {
   private:
    /* data */
    std::string m_root_path ;

   private:

    void CoreDump();

   public:
    System(/* args */);
    ~System();

    void Init();
    std::string GetRootPath();

    static void Close();
};

}  // namespace system
}  // namespace aclolinta