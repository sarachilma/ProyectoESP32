// gps_module.cpp
#include "gps_module.h"

GPSModule::GPSModule(HardwareSerial& serial, uint32_t baudRate)
    : _serial(serial), _baudRate(baudRate), _fix(false) {}

void GPSModule::actualizar() {
    if (!_serial) {
        _serial.begin(_baudRate);
    }
    while (_serial.available()) {
        String linea = _serial.readStringUntil('\n');
        procesarLinea(linea);
    }
}

void GPSModule::procesarLinea(const String& linea) {
    // Simple parsing for GPGGA (fix data)
    if (linea.startsWith("$GPGGA")) {
        auto parts = linea.split(','); // Nota: Arduino String no tiene split, usa otra forma:
        // Aquí hacemos el split manual para no usar librerías extra
        int indices[15];
        int idxCount = 0;
        indices[idxCount++] = 0;
        for (int i=0; i < linea.length(); i++) {
            if (linea.charAt(i) == ',') {
                indices[idxCount++] = i+1;
                if (idxCount >= 15) break;
            }
        }
        if (idxCount >= 15) {
            String fixStatus = linea.substring(indices[6], linea.indexOf(',', indices[6]));
            _fix = (fixStatus.toInt() > 0);
            if (_fix) {
                _horaUTC = linea.substring(indices[1], linea.indexOf(',', indices[1]));
                _latitud = linea.substring(indices[2], linea.indexOf(',', indices[2])) + " " + linea.substring(indices[3], linea.indexOf(',', indices[3]));
                _longitud = linea.substring(indices[4], linea.indexOf(',', indices[4])) + " " + linea.substring(indices[5], linea.indexOf(',', indices[5]));
            }
        }
    }
}

bool GPSModule::tieneFix() const { return _fix; }
String GPSModule::obtenerLatitud() const { return _latitud; }
String GPSModule::obtenerLongitud() const { return _longitud; }
String GPSModule::obtenerHoraUTC() const { return _horaUTC; }
