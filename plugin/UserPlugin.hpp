#pragma once

#include "../engine/Plugin.hpp"

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