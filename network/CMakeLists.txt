add_library(
        network_lib STATIC
        server.cpp server.h
        client.cpp client.h
        socket_utils.cpp socket_utils.h
        internal_rpc/types.h
)

target_link_libraries(network_lib rpc)
