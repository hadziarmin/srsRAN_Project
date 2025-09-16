#include <iostream>
#include <string>
#include <mqtt/async_client.h>
#include "mqtt.h"  // Include the header file
#include "mqtt_flag.h"
#include "../../../lib/scheduler/slicing/slice_ue_repository.h"  // Adjust the path as necessary

namespace srsran {
namespace app_services {
// Constructor
MQTTClient::MQTTClient() : client(SERVER_ADDRESS, CLIENT_ID) {
}

// Destructor
MQTTClient::~MQTTClient() {
    // Ensure we disconnect when the object is destroyed
    disconnect();
}

// Connect method
void MQTTClient::connect() {
    mqtt::connect_options connOpts;
    connOpts.set_keep_alive_interval(20);  // seconds
    connOpts.set_clean_session(true);

    try {
        std::cout << "Connecting to MQTT server..." << std::endl;
        client.connect(connOpts)->wait();
        std::cout << "Connected!" << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "Error connecting to MQTT: " << e.what() << std::endl;
        exit(1);
    }
}

// Publish message method
void MQTTClient::publish_message(const std::string& message) {
    try {
        mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(TOPIC, message, QOS, false);
        client.publish(pubmsg);
        std::cout << "Message published: " << message << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "Error publishing message: " << e.what() << std::endl;
    }
}

// Subscribe method
void MQTTClient::subscribe() {
    try {
        client.subscribe(TOPIC, QOS);
        std::cout << "Subscribed to topic: " << TOPIC << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "Error subscribing to topic: " << e.what() << std::endl;
    }
}

// Start listening method
void MQTTClient::start_listening() {
    client.set_message_callback(
        [](mqtt::const_message_ptr msg) {
            std::cout << "Received message: " << msg->to_string() << std::endl;
            std::string payload = msg->to_string();
            std::stringstream ss(payload);
            std::string flag_str, ue_rnti_hex;
            uint16_t ue_rnti = 0;
            if (std::getline(ss, flag_str, ',') && std::getline(ss, ue_rnti_hex)) {
                try {
                    // Parse the second part as hex and store as decimal
                    ue_rnti = std::stoi(ue_rnti_hex, nullptr, 16);
                    std::cout << "Second number (hex): " << ue_rnti_hex
                              << " as decimal: " << ue_rnti << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error converting second value from hex to int: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "Invalid message format! Expected two values separated by a comma." << std::endl;
            }
            bool flag = (flag_str != "0");
            std::cout << "Flag: " << flag << std::endl;
            srsran::g_use_custom_policy.store(flag, std::memory_order_relaxed);  
            srsran::g_use_custom_policy_ue.store(ue_rnti, std::memory_order_relaxed);          
        });

    std::cout << "Listening for messages..." << std::endl;
}

// Disconnect method
void MQTTClient::disconnect() {
    try {
        std::cout << "Disconnecting from MQTT server..." << std::endl;
        client.disconnect()->wait();
        std::cout << "Disconnected!" << std::endl;
    } catch (const mqtt::exception& e) {
        std::cerr << "Error disconnecting: " << e.what() << std::endl;
    }
}

// int main() {
//     MQTTClient mqttClient;

//     mqttClient.connect();
//     mqttClient.subscribe();
//     mqttClient.start_listening();

//     // Publish a message to the topic
//     mqttClient.publish_message("Hello from C++ MQTT client!");

//     // Simulate some time to receive messages
//     std::this_thread::sleep_for(std::chrono::seconds(10));

//     mqttClient.disconnect();
//     return 0;
// }
}
}