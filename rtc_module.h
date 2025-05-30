// rtc_module.h
#ifndef RTC_MODULE_H
#define RTC_MODULE_H

#include <Arduino.h>
#include <RTClib.h>

class RTCModule {
public:
    RTCModule();
    bool iniciar();
    DateTime obtenerFechaHora() const;
    String obtenerFechaHoraString() const;

private:
    RTC_DS1307 _rtc;
};

#endif
