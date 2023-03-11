/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-08 08:42:21
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-11 03:24:38
 * @FilePath: /TinyWebServer/tests/log_test.cpp
 * @Description: 日志测试器
 */

#include "../log/log.cpp"

using namespace aclolinta::logger;

int main() {
    auto test = aclolinta::logger::Logger::GetInstance();
    test->Open("/home/ac/TinyWebServer/log/main.log");
    errorr("NO BUG TEST");
}