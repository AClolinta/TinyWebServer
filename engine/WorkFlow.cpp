/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-05 12:19:28
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 09:58:27
 * @FilePath: /TinyWebServer/engine/WorkFlow.cpp
 * @Description: 从XML中读取配置并运行插件
 * */
#include "WorkFlow.hpp"

#include "log.hpp"
using namespace aclolinta::logger;

#include "Singleton.hpp"
using namespace aclolinta::utility;

#include "Context.hpp"
#include "Plugin.hpp"
#include "PluginHelper.hpp"

using namespace aclolinta::engine;

// WorkFlow::WorkFlow() = default;

WorkFlow::~WorkFlow() {
    for (auto it = m_works.begin(); it != m_works.end(); ++it) {
        delete it->second;
        it->second = nullptr;
    }
    m_works.clear();
}

bool WorkFlow::Load(string_view workinfo) {
    Document doc_;
    doc_.load_file(workinfo.data());
    Element root_ = doc_.parse();
    info("LOAD WORKFLOW SUCCESS: %s", workinfo);
    for (auto it = root_.begin(); it != root_.end(); ++it) {
        const string& name = it->attr("name");
        const string& flag = it->attr("switch");
        Work* work = new Work();
        work->SetName(name);
        if (flag == "on") {
            work->SetSwitch(true);
        } else if (flag == "off") {
            work->SetSwitch(false);
        } else {
            errorr("plugin switch: %s is not supported: %s", name.c_str(),
                   flag.c_str());
            return false;
        }
        if (!LoadPlugin(work, (*it))) {
            return false;
        }
        m_works[name] = work;
    }
    return true;
}

bool WorkFlow::Run(string_view work, string_view input, string& output) {
    auto it = m_works.find(work.data());
    if (it == m_works.end()) {
        errorr("work: %s is not exist!", work);
        return false;
    }
    if (!it->second->GetSwitch()) {
        errorr("work: %s is switch off!", work);
        return false;
    }

    Context ctx_;
    ctx_.Ref<string>("input") = input;
    if (!it->second->Run(ctx_)) {
        errorr("work: %s run error!", work);
        return false;
    }
    output = ctx_.Ref<string>("output");
    return true;
}

bool WorkFlow::LoadPlugin(Work* work, Element& elem) {
    for (auto it = elem.begin(); it != elem.end(); ++it) {
        if (it->name() != "plugin") {
            errorr("plugin %s elem: %s is not supported",
                   it->attr("name").c_str(), it->name().c_str());
            return false;
        }
        const string& name = it->attr("name");
        create_func func =
            (create_func)Singleton<PluginHelper>::Getinstance()->Get(name,
                                                                     "create");
        Plugin* plugin = func();
        plugin->SetName(name);

        const string& flag = it->attr("switch");
        if (flag == "on")
            plugin->SetSwitch(true);
        else if (flag == "off")
            plugin->SetSwitch(false);
        else {
            errorr("plugin %s switch: %s is not supported", name.c_str(),
                   flag.c_str());
            return false;
        }
        work->Append(plugin);
    }
    return true;
}
