/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-06-20 09:16:41
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:21:48
 * @FilePath: /TinyWebServer/plugin/UserPlugin.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include "Plugin.hpp"

using namespace aclolinta::engine;

namespace aclolinta {
namespace plugin {
class UserPlugin : public Plugin {
   public:
    UserPlugin(/* args */);
    virtual ~UserPlugin();

    virtual bool Run(Context& ctx);
};
DEFINE_PLUGIN(UserPlugin)
}  // namespace plugin

}  // namespace aclolinta