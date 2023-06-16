#include <iostream>

#include "log/log.hpp"

using namespace aclolinta::logger;

#include "system/system.hpp"
using namespace aclolinta::system;

#include "utility/Singleton.hpp"
#include "utility/iniFile.hpp"
using namespace aclolinta::utility;

#include "server/Server.hpp"
using namespace aclolinta::server;

int main() {
    System* sys = Singleton<System>::Getinstance();
    sys->Init();

    // IniFile* ini = Singleton<IniFile>::Getinstance();
    // const std::string& ip = (*ini)["server"]["ip"];
    // int port = (*ini)["server"]["port"];
    // int threads_number = (*ini)["server"]["threads"];
    // int max_conn = (*ini)["server"]["max_conn"];
    // int wait_time = (*ini)["server"]["wait_time"];

    // //
    // Server * server = Singleton<Server>::Getinstance();
    // server->SetThreads(threads_number);
    // server->SetConnects(max_conn);
    // server->SetWaitTimes(wait_time);
    // server->Listen(ip,port);

    // server->Start();

    return 0 ;
}