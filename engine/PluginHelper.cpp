/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-01 12:16:59
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 12:54:36
 * @FilePath: /TinyWebServer/engine/PluginHelper.cpp
 * @Description: 插件辅助工具
 
 */ 
#include "PluginHelper.hpp"
using namespace aclolinta::engine;

#include "log.hpp"
using namespace aclolinta::logger;

#include "Singleton.hpp"
using namespace aclolinta::utility;

#include "system.hpp"
using namespace aclolinta::sys;

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
    auto it = m_plugin.find(plugin.data());
    if (it == m_plugin.end()) {
        errorr("UNLOAD PLUGIN FAILURE: PLUGIN IS NOT EXIST.");
        return;
    }
    dlclose(it->second);
    m_plugin.erase(it);
}

/// @brief 获取每个插件对象的 symbol 函数指针
/// @param plugin 插件名称
/// @param symbol 插件内的函数名称
/// @return symbol 的函数指针
void* PluginHelper::Get(std::string_view plugin, std::string_view symbol) {
    auto it = m_plugin.find(plugin.data());
    if (it == m_plugin.end()) {
        Load(plugin.data());
        it = m_plugin.find(plugin.data());

        if (it == m_plugin.end()) {
            errorr("LOAD PLUGIN FAILURE IN PluginHelper::Get: %s",
                   plugin.data());
            return nullptr;
        }
    }

    void* func = dlsym(it->second, symbol.data());
    if (it == m_plugin.end()) {
        errorr("PLUGIN: %s, UNDEFINED SYMBOL: %s", plugin.data(),
               symbol.data());
    }
    return func;
};
void PluginHelper::Show() {
    for (auto it = m_plugin.begin(); it != m_plugin.end(); ++it) {
        debug("PLUGIN: NAME=%s HANDLE=%x", it->first.c_str(), it->second);
    }
}