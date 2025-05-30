// web_server.h
#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <WiFi.h>

class WebServerModule {
public:
    WebServerModule(const char* ssid, const char* password, uint16_t port=80);
    void iniciar();
    void actualizar();
    void setDatosSensor(float temp, float hum, const String& lat, const String& lon, const String& fechaHora);
    void setEstadoLED(bool estado);
    void toggleLED();

private:
    const char* _ssid;
    const char* _password;
    uint16_t _port;
    WiFiServer _server;
    WiFiClient _client;

    float _temp;
    float _hum;
    String _lat;
    String _lon;
    String _fechaHora;
    bool _ledEstado;

    void manejarCliente();
    String generarPaginaHTML();
};

#endif
