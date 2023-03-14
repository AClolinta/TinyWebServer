/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-14 12:05:23
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-14 12:12:21
 * @FilePath: /TinyWebServer/xml/Document.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once
#include <iostream>
#include <string>

#include "Element.cpp"
using namespace std;

namespace aclolinta {
namespace xml {

class Document {
   public:
    Document();
    ~Document();

    void load_file(const string& filename);
    void load_string(const string& str);
    void skip_white_spaces();
    Element parse();

   private:
    bool parse_declaration();
    bool parse_comment();
    string parse_element_name();
    string parse_element_text();
    string parse_element_attr_key();
    string parse_element_attr_val();

   private:
    string m_str;
    size_t m_idx;
};

}  // namespace xml
}  // namespace aclolinta
