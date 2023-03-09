
/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-07 11:58:01
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-09 08:53:23
 * @FilePath: /TinyWebServer/log/log.hpp
 * @Description: 日志器
 */
#pragma once

#include <fstream>
#include <string>
#include <string_view>

namespace aclolinta {
namespace logger {

enum class LoggerLevel : int {
    UNKNOW = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};
//快速输出日志
#define debug(format, ...)                                                     \
    Logger::GetInstance()->Log(LoggerLevel::DEBUG, __FILE__, __LINE__, format, \
                               ##__VA_ARGS__)

#define info(format, ...)                                                     \
    Logger::GetInstance()->Log(LoggerLevel::INFO, __FILE__, __LINE__, format, \
                               ##__VA_ARGS__)

#define warn(format, ...)                                                     \
    Logger::GetInstance()->Log(LoggerLevel::WARN, __FILE__, __LINE__, format, \
                               ##__VA_ARGS__)
#define error(GetInstance, ...)                                             \
    Logger::instance()->Log(LoggerLevel::ERROR, __FILE__, __LINE__, format, \
                            ##__VA_ARGS__)

#define fatal(GetInstance, ...)                                             \
    Logger::instance()->Log(LoggerLevel::FATAL, __FILE__, __LINE__, format, \
                            ##__VA_ARGS__)
//

class Logger {
   private:
    Logger(/* args */);
    ~Logger();
    void Rotate();
    /* data */
   private:
    std::string m_filename;  // 文件名
    std::ofstream m_fout;    // 输出文件流
    int m_max;
    int m_len;  // m_foutput 流中指针的位置
    LoggerLevel m_level;
    static std::string s_level;  // 六个等级
    static Logger* m_instance;

   public:
    static Logger* GetInstance();  // 单例
    static void Close();

    std::string LogLevelToString(LoggerLevel Level);

    void Open(std::string_view filename);  // 打开文件

    void Log(LoggerLevel level, std::string_view file, size_t line,
             const char* format, ...);
    void SetMax(int bytes);
    void SetLevel(int level);
    void rotate();
};
}  // namespace logger

}  // namespace aclolinta
