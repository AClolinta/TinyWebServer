
/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-07 11:58:01
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-08 02:37:53
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
    void Open(std::string_view filename);  // 打开文件

    void Log(LoggerLevel level, std::string_view file, size_t line,
             std::string_view format, ...);
    void Max(int bytes);
    void Level(int level);
};
}  // namespace logger

}  // namespace aclolinta
