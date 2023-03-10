/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-08 08:42:21
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-10 09:36:12
 * @FilePath: /TinyWebServer/log_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "../log/log.cpp"

using namespace aclolinta::logger;

int main() {
    auto test = aclolinta::logger::Logger::GetInstance();
    test->Open("/log/main.log");
    debug("??????????");
}