#include <rpc/msgpack/adaptor/define_decl.hpp>
#include <rpc/server.h>

typedef struct Result {
  int status;
  MSGPACK_DEFINE_ARRAY(status);
} Result;
