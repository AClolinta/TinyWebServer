#pragma once

#include <string>
#include <string_view>

#include "Socket.hpp"

namespace aclolinta {
namespace socket {
class ClientSocket : public Socket {
   private:
    /* data */
   public:
    ClientSocket(/* args */);
    ClientSocket(std::string_view ip, size_t port);
    virtual ~ClientSocket();
};

}  // namespace socket
}  // namespace aclolinta