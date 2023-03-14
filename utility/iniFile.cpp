/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-13 02:02:56
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-14 12:01:12
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
        line_ = trim(line_);         // 去除前后多余的空格
        if ('[' == line_.front()) {  // 第一个符号是不是['[']

            size_t end_pos_ = line_.find_first_of(']');
            if (end_pos_ != std::string::npos) {
                // 有匹配的右括号
                name_ = trim(line_.substr(1, end_pos_ - 1));
                m_inifile[name_];
            }
        } else if ('#' == line_[0]) {
            // 注释标记
            continue;
        } else {
            // 处理K-V对
            size_t end_pos_ = line_.find_first_of('=');
            if (end_pos_ > 0) {
                // 增加新的Key
                std::string key_ = trim(line_.substr(0, end_pos_));
                std::string value_ = trim(
                    line_.substr(end_pos_ + 1, line_.size() - end_pos_ - 1));
                auto it = m_inifile.find(name_);
                if (it == m_inifile.end()) {
                    printf("parsing error: section=%s key=%s\n", name_.c_str(),
                           key_.c_str());
                    return false;
                }
                m_inifile[name_][key_] = value_;
            }
        }
    }
    return true;
}

/// @brief 去除前后多余的空格
/// @param s
/// @return string
std::string IniFile::trim(std::string str) {
    if (str.empty()) {
        return str;
    }
    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    return str;
}

/// @brief 保存INI文件
/// @param filename
void IniFile::Save(std::string_view filename) {
    // 打开文件以便保存
    std::string filename_ = filename_;
    std::ofstream fout(filename_.c_str());

    for (auto it = m_inifile.begin(); it != m_inifile.end(); ++it) {
        // 写入一行
        fout << "[" << it->first << "]" << std::endl;
        for (auto iter = it->second.begin();
             iter != it->second.end(); ++iter) {
            // 写入K-V对
            fout << iter->first << " = " << (std::string)iter->second << std::endl;
        }
        fout << std::endl;
    }
}

void IniFile::Show() {

    for (auto it = m_inifile.begin(); it != m_inifile.end(); ++it) {
        //
        std::cout << "[" << it->first << "]" << std::endl;
        for ( auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
            // 
            std::cout << iter->first << " = " << (std::string)iter->second
                      << std::endl;
        }
        std::cout << std::endl;
    }
}

void IniFile::Clear() { m_inifile.clear(); }

bool IniFile::Has(const std::string &section) {
    return (m_inifile.find(section) != m_inifile.end());
}

bool IniFile::Has(const std::string &section, const std::string &key) {
    auto it = m_inifile.find(section);
    if (it != m_inifile.end()) {
        return (it->second.find(key) != it->second.end());
    }
    return false;
}

Value &IniFile::Get(const std::string &section, const std::string &key) {
    return m_inifile[section][key];
}

void IniFile::Set(const std::string &section, const std::string &key, bool value) {
    m_inifile[section][key] = value;
}

void IniFile::Set(const std::string &section, const std::string &key,
                  int value) {
    m_inifile[section][key] = value;
}

void IniFile::Set(const std::string &section, const std::string &key,
                  double value) {
    m_inifile[section][key] = value;
}

void IniFile::Set(const std::string &section, const std::string &key,
                  const std::string &value) {
    m_inifile[section][key] = value;
}

void IniFile::Remove(const std::string &section) {
    auto it = m_inifile.find(section);
    if (it != m_inifile.end()) m_inifile.erase(it);
}

void IniFile::Remove(const std::string &section, const std::string &key) {
    auto it = m_inifile.find(section);
    if (it != m_inifile.end()) {
        Section::iterator iter = it->second.find(key);
        if (iter != it->second.end()) it->second.erase(iter);
    }
}
