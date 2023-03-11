#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

#define IS_TYPE(typea, typeb) std::is_same<typea, typeb>::value
#define THROW_ERROR(error) throw std::logic_error((#error))

using std::string;

namespace aclolinta {

namespace json {

enum JSON_TYPE {
    TYPE_NULL,
    TYPE_BOOL,
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_LIST,
    TYPE_OBJ
};

class Json;

// 定义具体的数据类型
using null_t = std::string;
using bool_t = bool;
using int_t = int;
using double_t = double;
using string_t = std::string;
using list_t = std::vector<Json>;
using obj_t = std::map<std::string, Json>;

class Json {
   public:
    // 下面是Json允许的七种数据类型

    Json();
    Json(bool_t value);
    Json(int_t value);
    Json(double_t value);
    Json(const char *value);  // C风格的字符串
    Json(const string_t &value);
    //
    Json(JSON_TYPE type);
    Json(const Json &value);
    // 清理
    void clear();

    // 迭代器
    list_t::iterator begin() { return m_value.m_list->begin(); }
    list_t::iterator end() { return m_value.m_list->end(); }

    // 类型转换
    operator bool();
    operator int();
    operator double();
    operator string();
    // 重载索引操作的操作符
    Json &operator[](size_t index);
    Json &operator[](const char *source);
    Json &operator[](const string &source);

    // 重载等于的运算符
    bool operator==(const Json &source);

    // 删除元素的模板
    template <typename T>
    void remove(T const &source) {
        if constexpr (IS_TYPE(T, size_t) || IS_TYPE(T, int)) {  // 数组的索引
            if (m_type != TYPE_LIST) return;
            if (source < 0 || source >= m_value.m_list->size())
                return;  // 越界检查
            (m_value.m_list)->at(source).clear();
            (m_value.m_list)->erase(m_value.m_list->begin() + source);
        } else if constexpr (IS_TYPE(T, string) || (IS_TYPE(T, char *))) {
            if (m_type != TYPE_OBJ) return;
            if (m_value.m_obj->count(source) == 0) {
                return;  // 元素不存在
            } else {
                (*(m_value.m_obj))[source].clear();
                (m_value.m_obj)->erase(source);
            }
        } else {
            THROW_ERROR(NOT A LAWFUL TYPE IN REMOVE);
        }
    }

    // 列表增加元素
    void emplace(const Json &obj);
    // 序列化
    string to_string();

    //

   private:
    union JSON_VALUE {
        /* data */
        bool_t m_bool;
        int_t m_int;
        double_t m_double;
        string_t *m_string;
        list_t *m_list;
        obj_t *m_obj;
    };

    JSON_TYPE m_type;
    JSON_VALUE m_value;
};

}  // namespace json
}  // namespace aclolinta