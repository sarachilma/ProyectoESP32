// web_server.cpp
#include "web_server.h"

WebServerModule::WebServerModule(const char* ssid, const char* password, uint16_t port)
    : _ssid(ssid), _password(password), _port(port), _server(port), _temp(0), _hum(0), _lat(""), _lon(""), _fechaHora(""), _ledEstado(false) {}

void WebServerModule::iniciar() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    _server.begin();
}

void WebServerModule::actualizar() {
    if (_server.hasClient()) {
        if (_client && _client.connected()) {
            _client.stop();
        }
        _client = _server.available();
    }
    if (_client && _client.connected() && _client.available()) {
        manejarCliente();
    }
}

void WebServerModule::setDatosSensor(float temp, float hum, const String& lat, const String& lon, const String& fechaHora) {
    _temp = temp;
    _hum = hum;
    _lat = lat;
    _lon = lon;
    _fechaHora = fechaHora;
}

void WebServerModule::setEstadoLED(bool estado) {
    _ledEstado = estado;
}

void WebServerModule::toggleLED() {
    _ledEstado = !_ledEstado;
}

void WebServerModule::manejarCliente() {
    String peticion = _client.readStringUntil('\r');
    _client.flush();

    if (peticion.indexOf("GET /toggleLED") >= 0) {
        toggleLED();
    }

    String pagina = generarPaginaHTML();

    _client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    _client.print(pagina);
    delay(1);
    _client.stop();
}

String WebServerModule::generarPaginaHTML() {
    String html = "<!DOCTYPE html><html><head><title>ESP32 Sensor</title></head><body>";
    html += "<h1>Estado sensores</h1>";
    html += "<p>Temperatura: " + String(_temp, 1) + " °C</p>";
    html += "<p>Humedad: " + String(_hum, 1) + " %</p>";
    html += "<p>Latitud: " + _lat + "</p>";
    html += "<p>Longitud: " + _lon + "</p>";
    html += "<p>Fecha/Hora: " + _fechaHora + "</p>";
    html += "<p>LED: " + String(_ledEstado ? "Encendido" : "Apagado") + "</p>";
    html += "<a href='/toggleLED'>Alternar LED</a>";
    html += "</body></html>";
    return html;
}
