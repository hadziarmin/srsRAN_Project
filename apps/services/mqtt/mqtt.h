#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <mqtt/async_client.h>
#include <string>

namespace srsran {
namespace app_services {

// Define constants for the MQTT server and topic
const std::string SERVER_ADDRESS = "mqtt://10.0.0.3:1883";
const std::string CLIENT_ID      = "srsRANClient";
const std::string TOPIC          = "OT/omron/event";
const int         QOS            = 0;

class MQTTClient
{
    public:
      // Constructor and Destructor
      MQTTClient();
      ~MQTTClient();

      // Method to connect to the MQTT broker
      void connect();

      // Method to publish a message to the topic
      void publish_message(const std::string& message);

      // Method to subscribe to the topic
      void subscribe();

      // Method to start listening for messages
      void start_listening();

      // Method to disconnect from the MQTT broker
      void disconnect();

    private:
      mqtt::async_client client; // The MQTT client instance
};
} // namespace app_services
} // namespace srsran

#endif // MQTT_CLIENT_H
