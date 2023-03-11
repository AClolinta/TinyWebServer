#include "./json.hpp"

#define THROW_ERROR(error) throw std::logic_error((#error))

using namespace aclolinta::json;

Json::Json() : m_type(TYPE_NULL) {}

Json::Json(bool_t value) {
    m_type = TYPE_BOOL;
    m_value.m_bool = value;
}
Json::Json(int_t value) {
    m_type = TYPE_INT;
    m_value.m_int = value;
}
Json::Json(double_t value) {
    m_type = TYPE_DOUBLE;
    m_value.m_double = value;
}
Json::Json(const char *value) : m_type(TYPE_STRING) {  // C风格的字符串
    m_value.m_string = new std::string(value);
};
Json::Json(const string_t &value) : m_type(TYPE_STRING) {
    m_value.m_string = new std::string(value);
}
Json::Json(JSON_TYPE type) : m_type(type) {
    switch (m_type) {
        case TYPE_NULL:
            /* code */
            break;
        case TYPE_BOOL:
            m_value.m_bool = false;
            break;
        case TYPE_INT:
            m_value.m_int = 0;
            break;
        case TYPE_DOUBLE:
            m_value.m_double = 0.0;
            break;
        case TYPE_STRING:
            m_value.m_string = new string_t("");
            break;
        case TYPE_LIST:
            m_value.m_list = new list_t();
            break;
        case TYPE_OBJ:
            m_value.m_obj = new obj_t();
            break;

        default:
            break;
    }
}
Json::Json(const Json &value) {  // copy
    m_type = value.m_type;
    switch (m_type) {
        case TYPE_NULL:
            /* code */
            break;
        case TYPE_BOOL:
            m_value.m_bool = value.m_value.m_bool;
            break;
        case TYPE_INT:
            m_value.m_int = value.m_value.m_int;
            break;
        case TYPE_DOUBLE:
            m_value.m_double = value.m_value.m_double;
            break;
        case TYPE_STRING:
            // m_value.m_string = value.m_value.m_string;
            m_value.m_string =
                new string_t(value.m_value.m_string->begin(),
                             value.m_value.m_string->end());  // 深拷贝
            break;
        case TYPE_LIST:
            // m_value.m_list = value.m_value.m_list;
            m_value.m_list = new list_t(*value.m_value.m_list);
            break;
        case TYPE_OBJ:
            // m_value.m_obj = value.m_value.m_obj;
            m_value.m_obj = new obj_t(*value.m_value.m_obj);
            break;

        default:
            break;
    }
}
// 类型转换
Json::operator bool() {
    if (m_type != TYPE_BOOL)
        throw std::logic_error("TYPE ERROR, NOT A BOOL TYPE");
    return m_value.m_bool;
};
Json::operator int() {
    if (m_type != TYPE_INT)
        throw std::logic_error("TYPE ERROR, NOT A INT TYPE");
    return m_value.m_int;
};
Json::operator double() {
    if (m_type != TYPE_DOUBLE)
        throw std::logic_error("TYPE ERROR, NOT A DOUBLE TYPE");
    return m_value.m_double;
};
Json::operator string() {
    if (m_type != TYPE_STRING)
        throw std::logic_error("TYPE ERROR, NOT A STRING TYPE");
    return *m_value.m_string;
};
// 清理
void Json::clear() {
    // 基本类型不用管
    switch (m_type) {
        case TYPE_NULL:
            /* code */
            break;
        case TYPE_BOOL:
            m_value.m_bool = false;
            break;
        case TYPE_INT:
            m_value.m_int = 0;
            break;
        case TYPE_DOUBLE:
            m_value.m_double = 0.0;
            break;
        case TYPE_STRING:
            m_value.m_string->clear();
            break;
        case TYPE_LIST:
            m_value.m_list->clear();
            break;
        case TYPE_OBJ:
            m_value.m_obj->clear();
            break;
        default:
            break;
    }
    m_type = TYPE_NULL;
}

// 重载索引操作的操作符
Json &Json::operator[](size_t index) {
    if (m_type != TYPE_LIST) {
        // 创建一个List
        m_type = TYPE_LIST;
        m_value.m_list = new list_t();
    }
    size_t size = m_value.m_list->size();

    if (index < 0 && index >= size) THROW_ERROR(OUT OF INDEX);

    return m_value.m_list->at(index);
}
Json &Json::operator[](const char *source) {
    string _name(source);
    return (*(this))[_name];
}
Json &Json::operator[](const string &source) {
    if (m_type != TYPE_OBJ) {
        // clear();
        m_type = TYPE_OBJ;
        m_value.m_obj = new obj_t();
    }
    return (*m_value.m_obj)[source];
}
// 重载逻辑运算符
bool Json::operator==(const Json &source) {
    if (m_type != source.m_type) return false;
    // 下面是值判断
    switch (m_type) {
        case TYPE_NULL:
            return true;
        case TYPE_BOOL:
            return m_value.m_bool == source.m_value.m_bool;
        case TYPE_INT:
            return m_value.m_int == source.m_value.m_int;
        case TYPE_DOUBLE:
            return m_value.m_double == source.m_value.m_double;
        case TYPE_STRING:
            return *m_value.m_string == *source.m_value.m_string;
        case TYPE_LIST: {
            if (m_value.m_list->size() != source.m_value.m_list->size())
                return false;
            for (auto m_it = m_value.m_list->begin(),
                      src_it = source.m_value.m_list->begin();
                 m_it != m_value.m_list->end() &&
                 src_it != source.m_value.m_list->end();
                 ++m_it, ++src_it) {
                if ((*m_it) == (*src_it))
                    // 每一个值都相等
                    continue;
                else
                    return false;
            }
            return true;
        }

        case TYPE_OBJ: {
            // 只能递归判断了
            return m_value.m_obj == source.m_value.m_obj;
        }
        default:
            break;
    }
    THROW_ERROR(CMP ERROR);
}
// bool Json::operator!=(const Json &source) {}

// 列表增加元素
void Json::emplace(const Json &obj) {
    // 类型检查

    if (m_type != TYPE_LIST) {
        // clear();
        m_type = TYPE_LIST;
        m_value.m_list = new list_t();
    }
    m_value.m_list->push_back(obj);
}
string Json::to_string() {
    std::ostringstream os;
    // 下面是业务逻辑
    switch (m_type) {
        case TYPE_NULL:
            os << "null";
            break;
        case TYPE_BOOL:
            if (m_value.m_bool) {
                os << "true";
            } else {
                os << "false";
            }
            break;
        case TYPE_INT:
            os << m_value.m_int;
            break;
        case TYPE_DOUBLE:
            os << m_value.m_double;
            break;
        case TYPE_STRING:
            os << '\"' << *(m_value.m_string) << '\"';
            break;
        case TYPE_LIST: {
            list_t &list = *m_value.m_list;
            // 先输出格式化部分的“[”
            os << '[';
            // 开始遍历处理
            for (auto it = list.begin(); it != list.end(); ++it) {
                // 每一个元素中间要用[,]隔开。最后一个不用
                if (it == list.end() - 1) {  // 最后一个元素
                    os << (it->to_string());
                } else {
                    os << (it->to_string()) << ',';
                }
            }
            // 结束的右括号"]"
            os << ']';
            break;
        }
        case TYPE_OBJ: {
            obj_t &obj = *m_value.m_obj;
            // 先输出格式化部分的“{”
            os << '{';
            // 开始遍历处理
            for (auto it = obj.begin(); it != obj.end(); ++it) {
                // 每一个元素中间要用[,]隔开。最后一个不用
                if (it != obj.begin()) os << ',';
                os << '\"' << it->first << '\"' << ':'
                   << it->second.to_string();
            }
            // 结束处理
            os << '}';
            break;
        }
        default:
            return "";
    }
    return os.str();
}
