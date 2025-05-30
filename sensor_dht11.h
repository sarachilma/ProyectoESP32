// sensor_dht11.h
#ifndef SENSOR_DHT11_H
#define SENSOR_DHT11_H

#include <Arduino.h>

class SensorDHT11 {
public:
    SensorDHT11(uint8_t pin);
    bool actualizar();
    float obtenerTemperatura() const;
    float obtenerHumedad() const;

private:
    uint8_t _pin;
    float _temperatura;
    float _humedad;
    bool _estado;
};

#endif
