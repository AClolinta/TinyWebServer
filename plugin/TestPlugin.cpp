/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-16 04:00:19
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 08:53:41
 * @FilePath: /TinyWebServer/plugin/TestPlugin.cpp
 * @Description: */
#include "TestPlugin.hpp"

using namespace aclolinta::engine;
using namespace aclolinta::plugin;

TestPlugin::TestPlugin() : Plugin() {}

TestPlugin::~TestPlugin() {}

bool TestPlugin::Run(Context& ctx) {
    std::string_view input_ = ctx.Ref<std::string>("input");
    ctx.Ref<std::string>("output") = string(input_) + " PLUGIN(TEST) RUN! \n";
    return true;
}