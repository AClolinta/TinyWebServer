/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-16 03:35:32
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 12:09:51
 * @FilePath: /TinyWebServer/plugin/EchoPlugin.cpp
 * @Description:  EchoPlugin 的实现
 *  */
#include "EchoPlugin.hpp"

using namespace aclolinta::engine;
using namespace aclolinta::plugin;

#include "log.hpp"
using namespace aclolinta::logger;

#include "Singleton.hpp"
using namespace aclolinta::utility;

#include "system.hpp"
using namespace aclolinta::system;

EchoPlugin::EchoPlugin() {
    System* sys_ = Singleton<System>::Getinstance();  // 获取系统路径
    std::string_view root_path = sys_->GetRootPath();

    Logger::GetInstance()->Open(string(root_path) + "/log/echo.log");
}
EchoPlugin::~EchoPlugin() {}

bool EchoPlugin::Run(Context& ctx) {
    std::string& input_ = ctx.Ref<std::string>("input");
    info(input_.c_str());

    ctx.Ref<std::string>("output") = input_ + " PLUGIN ECHO RUN!";
    return true;
}