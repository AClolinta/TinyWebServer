/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 08:05:28
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 09:58:15
 * @FilePath: /TinyWebServer/engine/Work.cpp
 * @Description: 插件的管理和运行的实现
 */
#include "Work.hpp"

#include "PluginHelper.hpp"
using namespace aclolinta::engine;

#include "Singleton.hpp"
using namespace aclolinta::utility;

#include "log.hpp"
using namespace aclolinta::logger;

Work::Work() : m_name(""), m_switch(false) {}

Work::Work(string_view name, bool flag) : m_name(name), m_switch(flag) {}

Work::~Work() {
    for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it) {
        destroy_func func =
            (destroy_func)Singleton<PluginHelper>::Getinstance()->Get(
                (*it)->GetName(), "Destroy");
        func(dynamic_cast<Plugin*>(*it));
    }
}
void Work::Append(Plugin* plugin) { m_plugins.push_back(plugin); }

void Work::SetName(string_view name) { m_name = name; }

string_view Work::GetName() const { return m_name; }

void Work::SetSwitch(bool flag) { m_switch = flag; }

bool Work::GetSwitch() const { return m_switch; }

bool Work::Run(Context& ctx) {
    for (auto it = m_plugins.begin(); it != m_plugins.end(); ++it) {
        // 获取运行状态
        if ((*it)->GetSwitch() == true) {
            if ((*it)->Run(ctx) == false) {
                errorr("UNEXPECT PLUGIN: %s RUNNING ERROR", (*it)->GetName().data());
                break;
            }
        }
    }
    return true;
}