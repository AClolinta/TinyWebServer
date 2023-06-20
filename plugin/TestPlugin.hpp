/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-16 03:58:25
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 04:05:20
 * @FilePath: /TinyWebServer/plugin/TestPlugin.hpp
 * @Description: 
 *  */
#pragma once

#include "Plugin.hpp"

using namespace aclolinta::engine;

namespace aclolinta {
namespace plugin {

class TestPlugin : public Plugin {
   public:
    TestPlugin();
    virtual ~TestPlugin();

    virtual bool Run(Context& ctx);
};

DEFINE_PLUGIN(TestPlugin)
}  // namespace plugin
}  // namespace aclolinta