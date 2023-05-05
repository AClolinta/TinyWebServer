/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 02:40:20
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-05 12:17:38
 * @FilePath: /TinyWebServer/engine/Work.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: 插件的管理和运行
 */
#pragma once

#include <string_view>
using std::string_view;

#include <vector>
using std::vector;
#include "Context.hpp"
#include "Plugin.hpp"

namespace aclolinta {
namespace engine {
class Work {
   private:
    /* data */
    string m_name;
    bool m_switch;
    vector<Plugin *> m_plugins;

   public:
    Work(/* args */);
    Work(string_view name, bool flag);
    ~Work();

   public:
    /// @brief 添加插件
    /// @param plugin 
    void Append(Plugin *plugin);

    /// @brief 设置名称
    /// @param name
    void SetName(string_view name);

    string_view GetName() const;

    void SetSwitch(bool flag);
    bool GetSwitch() const;

    bool Run(Context &ctx);
};
}  // namespace engine
}  // namespace aclolinta
