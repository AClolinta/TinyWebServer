/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-14 12:05:23
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-20 10:43:58
 * @FilePath: /TinyWebServer/xml/Element.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "Element.hpp"

#include <sstream>
using namespace aclolinta::xml;

Element::Element()= default;

Element::Element(const string& name) : m_name(name) {}

Element::Element(const string& name, const string& text)
    : m_name(name), m_text(text) {}

Element::~Element() = default;

const string& Element::Name() const { return m_name; }

const string& Element::Text() const { return m_text; }

void Element::Name(const string& name) { m_name = name; }

void Element::Text(const string& text) { m_text = text; }

string& Element::Attr(const string& key) { return m_attrs[key]; }

void Element::Attr(const string& key, const string& value) {
    if (value != "") {
        m_attrs[key] = value;
        return;
    }

    std::map<string, string>::iterator it = m_attrs.find(key);
    if (it != m_attrs.end()) {
        m_attrs.erase(it);
    }
}

const Element& Element::operator[](int index) const {
    int size = m_children.size();
    if (index >= 0 && index < size) {
        return m_children.at(index);
    }
    return null();
}

const Element& Element::operator[](const string& name) const {
    for (Element::const_iterator it = m_children.begin();
         it != m_children.end(); it++) {
        if ((*it).Name() == name) {
            return (*it);
        }
    }
    return null();
}

void Element::Append(const Element& child) { m_children.push_back(child); }

int Element::size() { return m_children.size(); }

void Element::clear() {
    m_name.clear();
    m_text.clear();
    m_attrs.clear();
    m_children.clear();
}

string Element::toString() const {
    if (m_name == "") {
        return "";
    }
    std::ostringstream os;
    os << "<" << m_name;
    for (std::map<string, string>::const_iterator it = m_attrs.begin();
         it != m_attrs.end(); it++) {
        os << " " << it->first << "=\"" << it->second << "\"";
    }
    os << ">";
    if (m_children.size() > 0) {
        for (std::vector<Element>::const_iterator it = m_children.begin();
             it != m_children.end(); it++) {
            os << (*it).toString();
        }
    } else {
        os << m_text;
    }
    os << "</" << m_name << ">";
    return os.str();
}

Element const& Element::null() {
    static const Element null;
    return null;
}
