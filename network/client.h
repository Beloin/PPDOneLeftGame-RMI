//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_CLIENT_H
#define TWAMP_CLIENT_H

#include <string>
#include <rpc/client.h>

namespace Network {

class Client {

protected:
  bool hasConnected = false;
  int server_fd{};

  std::string server_addr;
  rpc::client *rpcClient;
 
private:
  int ConnectToServer(std::string const &host, std::string const &port);

public:
  int ConnectTo(std::string const &host, std::string const &port);

  [[nodiscard]] bool IsConnected() const;

  virtual ~Client();

  void disconnect();
};

} // namespace Network

#endif // TWAMP_CLIENT_H
