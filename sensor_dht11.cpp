// sensor_dht11.cpp
#include "sensor_dht11.h"
#include <DHT.h>

#define DHT_TYPE DHT11

static DHT dht_sensor(0, DHT_TYPE);  // pin será cambiado en constructor

SensorDHT11::SensorDHT11(uint8_t pin) : _pin(pin), _temperatura(0), _humedad(0), _estado(false) {
    dht_sensor.~DHT(); // Destruye objeto anterior
    new (&dht_sensor) DHT(_pin, DHT_TYPE);
    dht_sensor.begin();
}

bool SensorDHT11::actualizar() {
    float temp = dht_sensor.readTemperature();
    float hum = dht_sensor.readHumidity();

    if (isnan(temp) || isnan(hum)) {
        _estado = false;
        return false;
    }
    _temperatura = temp;
    _humedad = hum;
    _estado = true;
    return true;
}

float SensorDHT11::obtenerTemperatura() const {
    return _temperatura;
}

float SensorDHT11::obtenerHumedad() const {
    return _humedad;
}
