/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-16 09:05:11
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:21:49
 * @FilePath: /TinyWebServer/plugin/UserPlugin.cpp
 * @Description:
 */
#include "UserPlugin.hpp"

using namespace aclolinta::engine;
using namespace aclolinta::plugin;

#include "json.hpp"

using namespace aclolinta::json;

UserPlugin::UserPlugin() : Plugin() {}

UserPlugin::~UserPlugin() {}

bool UserPlugin::Run(Context& ctx) {
    std::string_view input = ctx.Ref<std::string>("input");
    ctx.Ref<std::string>("output") += "user plugin run!";
    return true;
}