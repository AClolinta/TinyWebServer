/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 13:09:31
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 13:16:41
 * @FilePath: /TinyWebServer/socket/SocketHandler.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "SocketHandler.hpp"

#include "../log/log.hpp"
#include "../utility/Singleton.hpp"
#include "../utility/iniFile.hpp"

using namespace aclolinta::utility;
using namespace aclolinta::logger;

#include "../thread/AutoLock.hpp"
#include "../thread/Task.hpp"
#include "../thread/TaskDispatcher.hpp"
#include "ServerSocket.hpp"
using namespace aclolinta::socket;