/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:22:08
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-11 03:22:42
 * @FilePath: /TinyWebServer/json/parser.hpp
 * @Description: json语法解析器
 */
#pragma once

#include <string>
#include <string_view>

#include "json.hpp"

namespace aclolinta {

namespace json {
class Parser {
   private:
    /* data */
    std::string m_str;  // 字符串
    size_t m_index;     // 索引
    // 实例
    static Parser* m_instance;
    // 单例
    Parser();
    static void Clear();  // 删除器

   public:
    // 获取实例
    static Parser* GetInstance();

    void init(std::string_view string_src);
    // 主解析器
    Json ParserStart();
    // 具体解析
    char GetNextToken();
    Json ParserNull();
    bool ParserBool();
    Json ParserNum();
    string_t ParserString();
    Json ParserList();
    Json ParserObj();
    // 辅助函数
    bool isMulitEscape(size_t pos);
    bool isBoolType();
};

}  // namespace json
}  // namespace aclolinta
