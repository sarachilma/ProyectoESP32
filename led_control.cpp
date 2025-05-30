// led_control.cpp
#include "led_control.h"

LEDControl::LEDControl(uint8_t pin) : _pin(pin), _estado(false) {
    pinMode(_pin, OUTPUT);
    apagar();
}

void LEDControl::encender() {
    digitalWrite(_pin, HIGH);
    _estado = true;
}

void LEDControl::apagar() {
    digitalWrite(_pin, LOW);
    _estado = false;
}

void LEDControl::alternar() {
    if (_estado) apagar();
    else encender();
}

bool LEDControl::estado() const {
    return _estado;
}
