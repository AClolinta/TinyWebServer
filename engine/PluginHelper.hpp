/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-01 12:03:20
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-01 12:24:05
 * @FilePath: /TinyWebServer/engine/PluginHelper.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <dlfcn.h>

#include <map>
#include <string>

#include "Plugin.hpp"

namespace aclolinta {
namespace engine {
// 定义了一个函数指针类型 create_func，指向一个不接受任何参数并返回 Plugin*
// 类型指针的函数
using create_func = Plugin* (*)();
// 定义了一个名为 destroy_func 的函数指针类型，该函数指针指向一个接受一个
// Plugin* 类型指针参数并返回 void 的函数。
using destroy_func = void (*)(Plugin*);
class PluginHelper {
   private:
    std::map<std::string, void*> m_plugin;
    /* data */
   public:
    PluginHelper(/* args */);
    ~PluginHelper();

   public:
    void Load(std::string_view plugin);
    void Unload(std::string_view plugin);
    void* Get(std::string_view plugin, std::string_view symbol);
    void Show();
};

PluginHelper::PluginHelper(/* args */) {}

PluginHelper::~PluginHelper() {}

}  // namespace engine
}  // namespace aclolinta