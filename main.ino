/**
 * 
 * Author Danushka Dissanayaka
 * 
 **/

#include "mqtt.h"
#include "sensor.h"
#include <ArduinoJson.h>

/**
 * 
 *  jason declarations
 * 
 **/
StaticJsonDocument<512> doc;
String jsonOutput = "";
JsonObject data = doc.to<JsonObject>(); // create json object
/**
 * 
 * END 
 * 
 **/

/**
 * 
 * Veriable for time calculation
 * 
 **/
unsigned long beginTime;
unsigned long endTime;
/**
 * 
 * END
 * 
 **/
void setup()
{
    soilMoistureInit();         // init soilMoisture sensor
    buzInit(5);                 //init buzer
    Serial.begin(115200);       //init Serial communication for debug purpuses
    mqttInit();                 //init Mqtt protocol for send data view MQTT.h file
    beginTime = millis();       // Begin time calculation
}

void loop()
{
    // publish data to server every 30 seconds or defined time
    if (endTime - beginTime >= DATA_SEND_DELAY)
    {
        publishData("plantInfo", getAvarage()); // send data to server
        beginTime = millis(); // reset time for next data sent
    }
    else
    {
        avarageData(); // caculate avarage to send next time
        localEvaluation(); // Evaluate localy
    }
    endTime = millis();
    delay(1000); // wait 1 second befor bigin next cycle
}

/**
 * 
 *  Evaluate data localy and respond for conditions
 * 
 **/
void localEvaluation(void)
{
    // red soilMoisture from plant
    uint16_t soilMoisture = getSoilMoisture();
    if (soilMoisture > MIN_SOIL_MOISTURE)
    {
        beep(250, 1); // indicate that plant need water
    }
}

/**
 * 
 * avarage dada before send
 * 
 **/
uint8_t avaragecounter = 0; // veriable for hold avarage frequency
float totalSoilMoisture = 0; // hold soil moistuet reding befor calculate avarage

void avarageData()
{
    totalSoilMoisture = totalSoilMoisture + getSoilMoisture();
    avaragecounter++;
}

String getAvarage(void)
{
    // Set sensor data
    data["soilMoisture"] = totalSoilMoisture / avaragecounter;

    // now reset the avarage veriables for next calculation
    avaragecounter = 0;
    totalSoilMoisture = 0;

    // convert json data to string
    jsonOutput = "";
    serializeJson(data, jsonOutput);
    Serial.println(jsonOutput);
    return jsonOutput;
}