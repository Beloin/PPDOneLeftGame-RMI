//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_CLIENT_H
#define TWAMP_CLIENT_H

#include <string>

namespace Network {
    class Client {

    protected:
        bool hasConnected = false;
        int server_fd{};

        std::string server_addr;

    private:
        int ConnectToServer(std::string const &host, std::string const &port);

    public:
        int ConnectTo(std::string const &host, std::string const &port);

        [[nodiscard]] bool IsConnected() const;

        virtual ~Client();
    };

}

#endif //TWAMP_CLIENT_H
