#ifndef MQTTCLIENT_H
    #define MQTTCLIENT_H
    #include <ESP8266WiFi.h>
    #include <MQTT.h>
    #include "setting.h"

    // function declarations
    void messageReceived(String &topic, String &payload);
    void mqttInit();
    void Wificonnect();
    void clientConnect(const char clientName[], const char username[], const char password[]);
    void publishData(String topic, String payload);
    bool mqttSubscribe(String topic);
    bool mqttUnSubscribe(String topic);

    WiFiClient net;
    MQTTClient client;

    void messageReceived(String &topic, String &payload)
    {
        Serial.println("incoming: " + topic + " - " + payload);
    }

    void mqttInit()
    {

        WiFi.begin(SSID, PASSWORD);
        client.begin(MQTT_API, net);       // in here use setting.h file's MQTT_API
        client.onMessage(messageReceived); // function for print recived massages

        Wificonnect(); // connect to wifi
        clientConnect(MQTT_CLIENT_NAME, MQTT_USER_NAME, MQTT_PASSWORD);
    }

    void Wificonnect()
    {
        Serial.print("checking wifi...");
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            delay(1000);
        }
    }

    void clientConnect(const char clientName[], const char username[], const char password[])
    {
        uint8_t trys = 0;
        Serial.print("\nclient connecting...");
        while (!client.connect(clientName, username, password) && (trys <= RECONNECT_TRYS))
        {
            Serial.print(".");
            delay(500);
            trys++;
        }

        if (!client.connected())
        {
            Serial.println("Connection Time out");
        }
        else
        {
            Serial.println("\nconnected!");
            // subscribes to your topics here
            mqttSubscribe(TOPIC);
        }
    }

    void publishData(String topic, String payload)
    {
        client.loop();
        delay(10); // <- fixes some issues with WiFi stability

        if (!client.connected())
        {
            clientConnect(MQTT_CLIENT_NAME, MQTT_USER_NAME, MQTT_PASSWORD);
        }
        if (client.connected())
        {
            // publish a message
            if (client.publish(topic, payload))
            {
                Serial.println("payload sent");
            }
            else
            {
                Serial.println("payload send fail");
            }
        }
    }

    bool mqttSubscribe(String topic)
    {
        return client.subscribe(topic);
    }

    bool mqttUnSubscribe(String topic)
    {
        return client.unsubscribe(topic);
    }
#endif