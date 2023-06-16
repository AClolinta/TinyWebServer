/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-16 03:27:05
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 03:50:06
 * @FilePath: /TinyWebServer/plugin/EchoPlugin.hpp
 * @Description: EchoPlugin插件 */
#pragma once

#include "../engine/Plugin.hpp"

using namespace aclolinta::engine;

namespace aclolinta {
namespace plugin {
class EchoPlugin : public Plugin {
   private:
    /* data */
   public:
    EchoPlugin(/* args */);
    virtual ~EchoPlugin();

    virtual bool Run(Context& ctx);
};

DEFINE_PLUGIN(EchoPlugin)
}  // namespace plugin
}  // namespace aclolinta