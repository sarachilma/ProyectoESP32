// led_control.h
#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>

class LEDControl {
public:
    LEDControl(uint8_t pin);
    void encender();
    void apagar();
    void alternar();
    bool estado() const;

private:
    uint8_t _pin;
    bool _estado;
};

#endif
