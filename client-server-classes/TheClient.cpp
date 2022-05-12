#include<memory>
#include "Client.h"

int main() {
 
  auto c = std::make_unique<Client>();
  c->setDstIP("127.0.0.1");
  c->setDstPort(8080);
  c->connectServer();
  c->sendMessage("Hello, world from client object");
  
}