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
    System * sys = Singleton<System>::Getinstance();
    sys->Init();

    
}