/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-07 12:18:55
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-08 03:02:57
 * @FilePath: /TinyWebServer/log/log.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "log.hpp"

#include <error.h>
#include <stdarg.h>

#include <chrono>
#include <ctime>
#include <locale>
#include <stdexcept>
#include <vector>

#define THROW_ERROR(error) throw std::logic_error((#error))

namespace aclolinta {
namespace logger {

Logger *Logger::m_instance = nullptr;

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
                 std::string_view format, ...) {
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
    std::fill(timestamp[0],timestamp[31],'0');
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&ticks));
}

}  // namespace logger
}  // namespace aclolinta