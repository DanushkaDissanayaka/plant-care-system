/***
 * 
 * SOIL MOISTURE SENSOR SETTINGS BEGIN
 * 
 */

#define SOIL_MOISTURE_PIN A0

void soilMoistureInit(void)
{
    pinMode(SOIL_MOISTURE_PIN, INPUT);
}

uint16_t getSoilMoisture(void)
{
    return analogRead(SOIL_MOISTURE_PIN);
}

/**
 * 
 * END SOIL MOISTURE SETTINGS
 * 
 */

