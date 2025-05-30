// gps_module.h
#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <Arduino.h>

class GPSModule {
public:
    GPSModule(HardwareSerial& serial, uint32_t baudRate);
    void actualizar();
    bool tieneFix() const;
    String obtenerLatitud() const;
    String obtenerLongitud() const;
    String obtenerHoraUTC() const;

private:
    HardwareSerial& _serial;
    uint32_t _baudRate;
    String _latitud;
    String _longitud;
    String _horaUTC;
    bool _fix;
    void procesarLinea(const String& linea);
};

#endif
