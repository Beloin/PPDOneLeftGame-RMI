#include <rpc/msgpack/adaptor/define_decl.hpp>
#include <rpc/server.h>
#include <string>

typedef struct Result {
  int status;
  int command;
  
  // If command == 1
  int fromX;
  int fromY;
  int toX;
  int toY;

  // If command == 2
  std::string message;

  // If command == 4
  int option;


  MSGPACK_DEFINE_ARRAY(status, command, fromX, fromY, toX, toY, message, option);
} Result;
