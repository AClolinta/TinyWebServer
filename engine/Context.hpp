/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-05-01 11:33:09
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-05-01 11:40:52
 * @FilePath: /TinyWebServer/engine/Context.hpp
 * @Description: 一个类型安全的键值对存储容器，用于存储键值对。
 */
#pragma once
#include <string>
using std::string;

#include <map>
using std::map;

namespace aclolinta {
namespace engine {

class Object {
   public:
    Object() {}
    virtual ~Object() {}
};

class Context {
   public:
    Context() {}
    ~Context() { Clear(); }

    template <typename T>
    void Set(const string &key, T value);

    template <typename T>
    T Get(const string &key);

    template <typename T>
    T &Ref(const string &key);

    void Clear();

   private:
    map<string, bool> m_bool;
    map<string, char> m_char;
    map<string, short> m_short;
    map<string, int> m_int;
    map<string, long> m_long;
    map<string, double> m_double;
    map<string, string> m_str;
    map<string, Object *> m_obj;
};

template <>
inline void Context::Set<bool>(const string &key, bool value) {
    m_bool[key] = value;
}

template <>
inline bool Context::Get<bool>(const string &key) {
    auto it = m_bool.find(key);
    if (it != m_bool.end()) return it->second;

    return false;
}

template <>
inline void Context::Set<char>(const string &key, char value) {
    m_char[key] = value;
}

template <>
inline char Context::Get<char>(const string &key) {
    auto it = m_char.find(key);
    if (it != m_char.end()) return it->second;
    return 0;
}

template <>
inline void Context::Set<unsigned char>(const string &key,
                                        unsigned char value) {
    m_char[key] = value;
}

template <>
inline unsigned char Context::Get<unsigned char>(const string &key) {
    auto it = m_char.find(key);
    if (it != m_char.end()) return static_cast<unsigned char>(it->second);
    return 0;
}

template <>
inline void Context::Set<short>(const string &key, short value) {
    m_short[key] = value;
}

template <>
inline short Context::Get<short>(const string &key) {
    auto it = m_short.find(key);
    if (it != m_short.end()) return it->second;
    return 0;
}

template <>
inline void Context::Set<unsigned short>(const string &key,
                                         unsigned short value) {
    m_short[key] = value;
}

template <>
inline unsigned short Context::Get<unsigned short>(const string &key) {
    auto it = m_short.find(key);
    if (it != m_short.end()) return static_cast<unsigned short>(it->second);
    return 0;
}

template <>
inline void Context::Set<int>(const string &key, int value) {
    m_int[key] = value;
}

template <>
inline int Context::Get<int>(const string &key) {
    auto it = m_int.find(key);
    if (it != m_int.end()) return it->second;
    return 0;
}

template <>
inline void Context::Set<unsigned int>(const string &key, unsigned int value) {
    m_int[key] = value;
}

template <>
inline unsigned int Context::Get<unsigned int>(const string &key) {
    auto it = m_int.find(key);
    if (it != m_int.end()) return static_cast<unsigned int>(it->second);
    return 0;
}

template <>
inline void Context::Set<long>(const string &key, long value) {
    m_long[key] = value;
}

template <>
inline long Context::Get<long>(const string &key) {
    auto it = m_long.find(key);
    if (it != m_long.end()) return it->second;
    return 0;
}

template <>
inline void Context::Set<unsigned long>(const string &key,
                                        unsigned long value) {
    m_long[key] = value;
}

template <>
inline unsigned long Context::Get<unsigned long>(const string &key) {
    auto it = m_long.find(key);
    if (it != m_long.end()) return static_cast<unsigned long>(it->second);
    return 0;
}

template <>
inline void Context::Set<double>(const string &key, double value) {
    m_double[key] = value;
}

template <>
inline double Context::Get<double>(const string &key) {
    auto it = m_double.find(key);
    if (it != m_double.end()) return it->second;
    return 0;
}

template <>
inline void Context::Set<const string &>(const string &key,
                                         const string &value) {
    m_str[key] = value;
}

template <>
inline string &Context::Get<string &>(const string &key) {
    return m_str[key];
}

template <>
inline void Context::Set<Object *>(const string &key, Object *value) {
    m_obj[key] = value;
}

template <>
inline Object *Context::Get<Object *>(const string &key) {
    auto it = m_obj.find(key);
    if (it != m_obj.end()) return it->second;
    return NULL;
}

template <>
inline string &Context::Ref<string>(const string &key) {
    return m_str[key];
}

template <typename T>
inline T &Context::Ref(const string &key) {
    auto it = m_obj.find(key);
    if (it != m_obj.end()) {
        return *reinterpret_cast<T *>(it->second);
    } else {
        m_obj[key] = new T();
        return *reinterpret_cast<T *>(m_obj[key]);
    }
}

inline void Context::Clear() {
    m_bool.clear();
    m_char.clear();
    m_short.clear();
    m_int.clear();
    m_long.clear();
    m_double.clear();
    m_str.clear();
    for (auto it = m_obj.begin(); it != m_obj.end(); ++it) {
        delete it->second;
        it->second = NULL;
    }
    m_obj.clear();
}

}  // namespace engine
}  // namespace aclolinta
