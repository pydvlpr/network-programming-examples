#include<memory>
#include "Server.h"

int main(int argc, char **argv) {
  
  bool iFlag = argv[1];

  auto s = std::make_unique<Server>();
  s->prepare(8080);
  s->startListening(iFlag);

}