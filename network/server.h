//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_SERVER_H
#define TWAMP_SERVER_H

#include <rpc/server.h>
#include <string>


namespace Network {

    class Server {

    public:
        
        explicit Server();

        int serve(const std::string &port);

        ~Server();

        [[nodiscard]] bool IsRunning() const;

        virtual void handle_socket(int client_fd, std::string client_addr) = 0;

        void dispose();

    protected:
        bool should_run;
        bool server_on;
        int serverfd{};
        bool isClosed;

        rpc::server srv;

    };


}


#endif //TWAMP_SERVER_H
