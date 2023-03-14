/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-13 02:03:51
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-14 11:45:41
 * @FilePath: /TinyWebServer/utility/iniFile.hpp
 * @Description: 读取ini文件
 */
#pragma once

#include <string.h>

#include <sstream>
#include <string>
#include <string_view>
#include<map>

namespace aclolinta {
namespace utility {

/// @brief 值处理
class Value {
   private:
    /* data */
    std::string m_value;

   public:
    Value();
    Value(bool value);
    Value(int value);
    Value(double value);
    Value(const std::string& value);
    ~Value();

    Value& operator=(bool value);
    Value& operator=(int value);
    Value& operator=(double value);
    Value& operator=(const std::string& value);

    operator bool();
    operator int();
    operator double();
    operator std::string();
    operator std::string() const;
};

/// @brief ini文件类
class IniFile {
   public:
    IniFile();
    IniFile(std::string_view filename);
    ~IniFile();

    bool Load(std::string_view filename);
    void Save(std::string_view filename);
    void Show();
    void Clear();

    // read values in different formats
    Value &Get(const std::string &section, const std::string &key);

    // Set values in different formats
    void Set(const std::string &section, const std::string &key, bool value);
    void Set(const std::string &section, const std::string &key, int value);
    void Set(const std::string &section, const std::string &key, double value);
    void Set(const std::string &section, const std::string &key,
             const std::string &value);

    bool Has(const std::string &section);
    bool Has(const std::string &section, const std::string &key);

    void Remove(const std::string &section);
    void Remove(const std::string &section, const std::string &key);

    using Section = std::map<std::string, Value>;
    Section &operator[](const std::string &key) { return m_inifile[key]; }

   private:
    std::string trim(std::string s);

   private:
    std::string m_filename;

    std::map<std::string, Section> m_inifile;
};

}  // namespace utility
}  // namespace aclolinta