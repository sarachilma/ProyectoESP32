// rtc_module.cpp
#include "rtc_module.h"

RTCModule::RTCModule() {}

bool RTCModule::iniciar() {
    if (!_rtc.begin()) {
        return false;
    }
    if (!_rtc.isrunning()) {
        _rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajusta a fecha/hora compilación
    }
    return true;
}

DateTime RTCModule::obtenerFechaHora() const {
    return _rtc.now();
}

String RTCModule::obtenerFechaHoraString() const {
    DateTime now = _rtc.now();
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d %02d:%02d:%02d",
             now.day(), now.month(), now.year(),
             now.hour(), now.minute(), now.second());
    return String(buffer);
}
