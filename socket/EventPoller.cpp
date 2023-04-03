/*
 * @Author: AClolinta AClolinta@gmail.com
 * @Date: 2023-04-03 02:19:44
 * @LastEditors: AClolinta AClolinta@gmail.com
 * @LastEditTime: 2023-04-03 03:13:43
 * @FilePath: /TinyWebServer/socket/EventPoller.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "EventPoller.hpp"

using namespace aclolinta::socket;

EventPoller::EventPoller(bool et)
    : m_epfd(), m_max_connect(0), m_events(NULL), m_et(et){};

EventPoller::~EventPoller(){
    if(m_epfd > 0){
        close(m_epfd);
        m_epfd = 0;
    }

    if( nullptr != m_events ){
        delete [] m_events;
        m_events = nullptr;
    }
}