// #include <iostream>

// int main(int, char**) {
    
//     std::cout << "Hello, world!\n";
// }
#include "log/log.cpp"

using namespace aclolinta::logger;

int main() {
    auto test = aclolinta::logger::Logger::GetInstance();
    test->Open("/home/ac/TinyWebServer/log/main.log");
    errorr("NO BUG TEST");
}