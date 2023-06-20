/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-14 12:05:23
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:43:42
 * @FilePath: /TinyWebServer/xml/Element.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#pragma once

#include <string>
using std::string;

#include <map>
#include <vector>

namespace aclolinta {
namespace xml {

class Element {
   public:
    Element();
    Element(const string& name);
    Element(const string& name, const string& text);
    ~Element();

    // get element's name
    const string& Name() const;

    // set element's name
    void Name(const string& name);

    // get element's text
    const string& Text() const;

    // set element's text
    void Text(const string& text);

    // get element's attr
    string& Attr(const string& key);

    // set element's attr
    void Attr(const string& key, const string& value);

    // get child element by index
    const Element& operator[](int index) const;

    // get child element by name
    const Element& operator[](const string& name) const;

    // append child element
    void Append(const Element& child);

    // get numbers of the child
    int size();

    void clear();

    string toString() const;

    typedef std::vector<Element>::iterator iterator;
    typedef std::vector<Element>::const_iterator const_iterator;

    iterator begin() { return m_children.begin(); }

    iterator end() { return m_children.end(); }

    const_iterator begin() const { return m_children.begin(); }

    const_iterator end() const { return m_children.end(); }

    static Element const& null();

   private:
    string m_name;
    string m_text;
    std::vector<Element> m_children;
    std::map<string, string> m_attrs;
};

}  // namespace xml
}  // namespace yazi
