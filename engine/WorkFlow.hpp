/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 13:29:53
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 04:05:00
 * @FilePath: /TinyWebServer/engine/WorkFlow.hpp
 * @Description: 工作流
 */
#pragma once

#include <map>
#include <string>
#include <string_view>

#include "Work.hpp"
using std::string;
using std::string_view;

#include "../xml/Document.hpp"
#include "../xml/Element.hpp"
using namespace aclolinta::xml;

namespace aclolinta {
namespace engine {
class WorkFlow {
   private:
    /* data */
    map<string, Work*> m_works;

   public:
    WorkFlow(/* args */);
    ~WorkFlow();

   public:
    bool Load(string_view workinfo);
    bool Run(string_view work, string_view input, string& output);

   private:
    bool LoadPlugin(Work* work, Element& element);
};

}  // namespace engine
}  // namespace aclolinta