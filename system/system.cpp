/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-03-13 01:59:50
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-03-13 02:02:39
 * @FilePath: /TinyWebServer/system/system.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "system.hpp"

using namespace aclolinta;

#include <dirent.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../log/log.hpp"