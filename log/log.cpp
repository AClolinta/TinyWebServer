/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-07 12:18:55
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-08 07:53:16
 * @FilePath: /TinyWebServer/log/log.cpp
 * @Description: 日志器的实现
 */
#include "log.hpp"

#include <error.h>
#include <stdarg.h>
#include <string.h>

#include <chrono>
#include <ctime>
#include <locale>
#include <stdexcept>
#include <vector>

#define THROW_ERROR(error) throw std::logic_error((#error))

namespace aclolinta {
namespace logger {

Logger *Logger::m_instance = nullptr;

// std::string Logger::s_level[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};

//

Logger::Logger()
    : m_max(0), m_len(0), m_level(LoggerLevel::DEBUG /*debug级别*/){};
Logger::~Logger() { m_fout.close(); }

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

std::string Logger::LogLevelToString(LoggerLevel Level) {
    switch (Level) {
        case LoggerLevel::UNKNOW:
            return "UNKNOW";
            break;
        case LoggerLevel::DEBUG:
            return "DEBUG";
            break;
        case LoggerLevel::INFO:
            return "INFO";
            break;
        case LoggerLevel::WARN:
            return "WARN";
            break;
        case LoggerLevel::ERROR:
            return "ERROR";
            break;
        case LoggerLevel::FATAL:
            return "FATAL";
            break;
        default:
            break;
    }
    THROW_ERROR(UNEXPECT ERROR IN LogLevelToString);
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

void Logger::Log(LoggerLevel level, std::string_view file, size_t line,
                 const char *format, ...) {
    if (m_level > level) {
        return;  // 等级太低滚蛋
    }
    if (m_fout.fail()) {
        throw std::logic_error("OPEN LOG FILE IN LOGGER FAILED: " + m_filename);
    }
    // 时间输出
    std::locale::global(std::locale("zh_CN.utf8"));
    time_t ticks = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());  // 先获取时间再转化成time_t格式
    char timestamp[32];
    std::fill(timestamp[0], timestamp[31], '0');
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S",
             std::localtime(&ticks));
    //

    size_t len_ = 0;
    std::string format_ = "%s %s %s:%u";  // 格式对应下面的timestap,
    len_ = std::snprintf(
        nullptr, 0, format_.c_str(), LogLevelToString(level), file,
        line);  // 返回写入字符数组的字符数，不包括字符串的结束符,由于size=故实际并不会写入

    if (len_ > 0) {
        char *buffer_ = new char[len_ + 1];  // 缓冲区
        std::snprintf(buffer_, len_ + 1, format_.c_str(),
                      LogLevelToString(level), file, line);
        buffer_[len_] = 0;
        m_fout << buffer_;
        m_len += len_;
    }
    // 处理可变参数,输出日志内容
    va_list arg_ptr;
    va_start(arg_ptr, format);
    len_ = vsnprintf(NULL, 0, format, arg_ptr);
    va_end(arg_ptr);
    if (len_ > 0) {
        char *content = new char[len_ + 1];
        va_start(arg_ptr, format);
        vsnprintf(content, len_ + 1, format, arg_ptr);
        va_end(arg_ptr);
        content[len_] = 0;
        m_fout << content;
        delete content;
        m_len += len_;
    }

    m_fout << "\n";
    m_fout.flush();

    if (m_max > 0 && m_len >= m_max) rotate();
}

void Logger::SetMax(int bytes) { m_max = bytes; }

void Logger::SetLevel(int level) {
    switch (level) {
        case 0:
            m_level = LoggerLevel::UNKNOW;
            break;
        case 1:
            m_level = LoggerLevel::DEBUG;
            break;
        case 2:
            m_level = LoggerLevel::INFO;
            break;
        case 3:
            m_level = LoggerLevel::WARN;
            break;
        case 54:
            m_level = LoggerLevel::ERROR;
            break;
        case 5:
            m_level = LoggerLevel::FATAL;
            break;

        default:
            break;
    }
}

void Logger::rotate() {
    m_fout.close();
    std::locale::global(std::locale("zh_CN.utf8"));
    time_t ticks = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());  // 先获取时间再转化成time_t格式
    char timestamp[32];
    std::fill(timestamp[0], timestamp[31], '0');
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S",
             std::localtime(&ticks));
    std::string filename_ = m_filename + timestamp;
    if (std::rename(m_filename.c_str(), filename_.c_str()) != 0) {
        throw std::logic_error("RENAME LOG FILE FAILED: " +
                               std::string(strerror(errno)));
    }
    Open(m_filename);
}

}  // namespace logger
}  // namespace aclolinta