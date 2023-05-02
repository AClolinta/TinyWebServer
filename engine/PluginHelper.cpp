/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-01 12:16:59
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-02 11:59:03
 * @FilePath: /TinyWebServer/engine/PluginHelper.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "PluginHelper.hpp"
using namespace aclolinta::engine;

#include "../log/log.hpp"
using namespace aclolinta::logger;

#include "../utility/Singleton.hpp"
using namespace aclolinta::utility;

#include "../system/system.hpp"
using namespace aclolinta::system;

PluginHelper::PluginHelper(/* args */) {}

PluginHelper::~PluginHelper() {}

void PluginHelper::Load(std::string_view plugin) {
    if (plugin.empty()) {
        errorr("LOAD PLUGIN FAILURE: PLUGIN IS EMPTY");
        return;
        //
    }
    if (m_plugin.find(plugin.data()) != m_plugin.end()) {
        debug("PLUGIN IS ALREADY EXIST");
        return;
    }
    System* sys_ = Singleton<System>::Getinstance();
    std::string filename_ = sys_->GetRootPath() + "/plugin/" + plugin.data();

    void* handle_ = dlopen(filename_.c_str(), RTLD_GLOBAL | RTLD_LAZY);
    if (handle_ == nullptr) {
        errorr("LOAD PLUGIN FAILURE: %s", dlerror());
        return;
    }
    m_plugin[plugin.data()] = handle_;
}

void PluginHelper::Unload(std::string_view plugin) {
    if (plugin.empty()) {
        errorr("LOAD PLUGIN FAILURE: PLUGIN IS EMPTY");
        return;
    }
    auto it == m_plugin.find(plugin.data());
    if (it == m_plugin.end()) {
        errorr("UNLOAD PLUGIN FAILURE: PLUGIN IS NOT EXIST.");
        return;
    }
    dlclose(it->second);
    m_plugin.erase(it);
}

void* PluginHelper::Get(std::string_view plugin, std::string_view symbol);
void PluginHelper::Show();