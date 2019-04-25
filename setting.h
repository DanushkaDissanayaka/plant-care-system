#ifndef setting_h
    #define setting_h
    
    /************* wifi setting *******************/
    #define SSID        "Dialog 4G 364"
    #define PASSWORD    "7B4Fd0C1"

    /************* Server Setting ****************/
    #define MQTT_API            "192.168.8.174"
    #define MQTT_CLIENT_NAME    "Esp8266"
    #define MQTT_USER_NAME      "1"
    #define MQTT_PASSWORD       "2"
    #define ERROR_MSG           "{\"success\":\"false\",\"massage\":\"error connection fails\"}"
    #define RECONNECT_TRYS      2

    /************* Mqtt topics ****************/
    #define TOPIC  "plantInfoSetting" 

    /************ evaluation Conditions **********/
    uint16_t MIN_SOIL_MOISTURE  = 750;

    /************* Srvice define ****************/
    #define DATA_SEND_DELAY 10000

    /************* Debug  ****************/
    #define DEBUG true
#endif