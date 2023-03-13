/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-13 02:02:56
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-13 02:58:54
 * @FilePath: /TinyWebServer/utility/iniFile.cpp
 * @Description: 读取ini文件
 */
#include "iniFile.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace aclolinta::utility;
using std::ostringstream;

Value::Value() {}

Value::Value(bool value) { *this = value; }

Value::Value(int value) { *this = value; }

Value::Value(double value) { *this = value; }

Value::Value(const std::string& value) : m_value(value) {}

Value::~Value() {}

Value& Value::operator=(bool value) {
    if (value)
        m_value = "true";
    else
        m_value = "false";
    return *this;
}

Value& Value::operator=(int value) {
    ostringstream os;
    os << value;
    m_value = os.str();
    return *this;
}

Value& Value::operator=(double value) {
    ostringstream os;
    os << value;
    m_value = os.str();
    return *this;
}

Value& Value::operator=(const std::string& value) {
    m_value = value;
    return *this;
}

Value::operator bool() {
    if (m_value == "true")
        return true;
    else if (m_value == "false")
        return false;
    return false;
}

Value::operator int() { return std::atoi(m_value.c_str()); }

Value::operator double() { return std::atof(m_value.c_str()); }

Value::operator std::string() { return m_value; }

Value::operator std::string() const { return m_value; }

/// 下面是iniFilel类的具体实现
IniFile::IniFile() {}

IniFile::IniFile(std::string_view filename) { Load(filename); }

IniFile::~IniFile() {}

/// @brief 读取、打开ini文件
/// @param filename
/// @return bool
bool IniFile::Load(std::string_view filename) {
    m_filename = filename;
    m_inifile.clear();

    std::string name_;
    std::string line_;
    // open the INI file for reading
    std::ifstream fin(m_filename.c_str());
    if (fin.fail()) {
        printf("LOADING FILE FAILED: %s IS NOT FOUND.\n", m_filename.c_str());
        return false;
    }
    while (std::getline(fin, line_)) {
        line_ = trim(line_);
        if ('[' == line_[0])  // it is a section
        {
            int pos = line_.find_first_of(']');
            if (-1 != pos) {
                name_ = trim(line_.substr(1, pos - 1));
                m_inifile[name_];
            }
        } else if ('#' == line_[0])  // it is a comment
        {
            continue;
        } else  // it is the "key=value" line_
        {
            int pos = line_.find_first_of('=');
            if (pos > 0) {
                // add new key to the last section in the storage
                std::string key = trim(line_.substr(0, pos));
                std::string value =
                    trim(line_.substr(pos + 1, line_.size() - pos - 1));
                auto it = m_inifile.find(name_);
                if (it == m_inifile.end()) {
                    printf("parsing error: section=%s key=%s\n", name_.c_str(),
                           key.c_str());
                    return false;
                }
                m_inifile[name_][key] = value;
            }
        }
    }
    return true;
}
