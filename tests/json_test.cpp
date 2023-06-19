/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-11 03:28:37
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-06-19 09:41:16
 * @FilePath: /TinyWebServer/tests/json_test.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "../json/json.cpp"

#include "../json/parser.cpp"
#include "../logger/log.cpp"

using namespace aclolinta::logger;
using namespace aclolinta::json;

int main() {
    std::ifstream json_file("./test.json");
    // std::ifstream json_file("./test.txt");
    std::stringstream ss;
    ss << json_file.rdbuf();

    std::string str = ss.str();

    std::cout << str << std::endl;

    str =
        "{\"code\":0,\"message\":\"0\",\"ttl\":1,\"data\":{\"cover\":\"\","
        "\"channel_id\":0,\"channel_name\":\"\",\"notify\":false,\"ctype\":0,"
        "\"subscribed_count\":0}}";

    Parser *P = Parser::GetInstance();
    P->init(str);
    Json J = P->ParserStart();

    auto test = aclolinta::logger::Logger::GetInstance();
    test->Open("/home/ac/TinyWebServer/tests/log/main.log");
    info(J.to_string().c_str());
}