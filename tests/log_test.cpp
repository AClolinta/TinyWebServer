/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-08 08:42:21
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 10:58:05
 * @FilePath: /TinyWebServer/tests/log_test.cpp
 * @Description: 日志测试器
 */

#include "log.cpp"

using namespace aclolinta::logger;

int main() {
    auto test = aclolinta::logger::Logger::GetInstance();
    test->Open("/home/ac/TinyWebServer/tests/log/main.log");
    errorr("NO BUG TEST");
}