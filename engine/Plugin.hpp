/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-01 11:47:08
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-16 09:10:42
 * @FilePath: /TinyWebServer/engine/Plugin.hpp
 * @Description: Plugin类的基本定义
 */
#pragma once

#include <string>

#include "Context.hpp"

namespace aclolinta {
namespace engine {
class Plugin {
   private:
    /* data */
   public:
    Plugin(/* args */);
    // 初始化插件的名称和开关属性。
    Plugin(std::string_view name, bool flag) : m_name(name), is_switch(flag) {}

    virtual ~Plugin();

    void SetName(std::string_view name) { m_name = name; };
    std::string_view GetName() { return m_name; };

    void SetSwitch(bool flag) { is_switch = flag; };
    bool GetSwitch() { return is_switch; };

    virtual bool Run(Context& ctx) = 0;

   protected:
    std::string m_name;
    bool is_switch;
};

#define DEFINE_PLUGIN(classType)                                           \
    extern "C" Plugin* Create() { return new (std::nothrow) classType(); } \
    extern "C" void Destroy(Plugin* p) {                                   \
        delete p;                                                          \
        p = NULL;                                                          \
    }
}  // namespace engine
}  // namespace aclolinta