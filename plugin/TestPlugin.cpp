/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-16 04:00:19
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 04:04:51
 * @FilePath: /TinyWebServer/plugin/TestPlugin.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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