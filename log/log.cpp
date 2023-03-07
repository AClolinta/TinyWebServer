#include "log.hpp"

#include <error.h>
#include <stdarg.h>
#include <time.h>

#include <stdexcept>

#define THROW_ERROR(error) throw std::logic_error((#error))

namespace aclolinta {

Logger *Logger::m_instance = nullptr;

Logger::Logger() : m_max(0), m_len(0), m_level(1 /*debug*/){};

void Logger::Close() {
    if (m_instance != nullptr) {
        delete m_instance;
        m_instance = nullptr;
    }
}

Logger *Logger::GetInstance() {
    if (m_instance == nullptr) {
        m_instance = new Logger();
        std::atexit(Logger::Close);
    }
    return m_instance;
}

void Logger::Open(std::string_view filename) {
    m_filename = filename;
    m_fout.open(m_filename, std::ios::app);  // 在文件末尾添加的格式
    if (m_fout.fail()) {
        throw std::logic_error("OPEN LOG FILE FAILED: " + m_filename);
    }
    m_fout.seekp(0,
                 std::ios::end);  // 将写入位置设置为从文件末尾开始的第 0 个字节

    m_len = m_fout.tellp();  // 获取 当前 put 流指针的位置
}
}  // namespace aclolinta