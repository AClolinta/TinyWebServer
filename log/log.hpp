/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-07 11:58:01
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-07 12:24:57
 * @FilePath: /TinyWebServer/log/log.hpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-07 11:58:01
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-07 12:18:36
 * @FilePath: /TinyWebServer/log/log.hpp
 * @Description: 日志器
 */
#pragma once

#include <fstream>
#include <string>
#include <string_view>

namespace aclolinta {

enum class LoggerLevel :int {
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
    std::string m_filename;
    std::ofstream m_fout;
    int m_max;
    int m_len;
    int m_level;
    static std::string s_level;  // 六个等级
    static Logger* m_instance;

   public:
   static Logger* Instance();//单例
   void open(std::string_view filename);//打开文件
   void close();
   void Log( LoggerLevel level, std::string_view file, size_t line , std::string_view format, ...);
   void Max(int bytes);
   void Level(int level);
};

}  // namespace aclolinta
