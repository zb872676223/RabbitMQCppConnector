#include <iostream>
#include "../src/ideup/amqp/ConnectionFactory.hpp"
#include "../src/ideup/amqp/Connection.hpp"
#include "../src/ideup/amqp/Channel.hpp"
#include "../src/ideup/amqp/Queue.hpp"
#include "../src/ideup/amqp/Message.hpp"
#include "../src/ideup/amqp/Exception.hpp"

using namespace ideup::amqp;


class MyConsumer : public Observer
{
  public:
    void update(Message& message) {
      cout << message.getBody() << endl;
    }
};


int main(int argc, char* argv[])
{
  try {
    shared_ptr<Connection> conn = ConnectionFactory::newConnection();
    shared_ptr<Channel> channel = conn->createChannel();

    Queue::ptr_t queue = channel->declareQueue("my-first-queue");
    queue->attach(new MyConsumer());

    channel->basicConsume(queue);

    conn->close();
  }
  catch (Exception& e) {
    cerr << "AMQP Exception: " << e.what() << endl;
  }
  catch (exception& e) {
    cerr << "Standard Exception: " << e.what() << endl;
  }
}
