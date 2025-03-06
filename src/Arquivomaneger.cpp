#include "SPIFFS.h"
using namespace std;


class Arquivomaneger {
private:
        String path;
public:
    
    Arquivomaneger(String p){
        this->path = p;

        if (!SPIFFS.begin(true)) {
            Serial.println("Erro ao montar o SPIFFS");
            return;
        }
    
        Serial.println("SPIFFS montado com sucesso!");
    }

    String readFile() {
        String v = "";
        File file = SPIFFS.open(this->path, FILE_READ);
        if (!file) {
            Serial.println("Erro ao abrir o arquivo para leitura");
            return "";
        }
        Serial.println("Conteúdo do arquivo:");
        v = file.readString();
        // while (file.available()) {
        //     v = v + file.readStringUntil('\n') + '\n';
        // }
        file.close();
        return v;
    }
    
    void writeFile(const String message) {
        File file = SPIFFS.open(this->path, FILE_WRITE);
        if (!file) {
            Serial.println("Erro ao abrir o arquivo para escrita");
            return;
        }
        file.print(message);
        file.close();
        Serial.println("Escrita concluída!");
    }
    
    void clearFile() {
        File file = SPIFFS.open(this->path, FILE_WRITE);
        if (!file) {
            Serial.println("Erro ao abrir o arquivo para escrita");
            return;
        }
        file.print("");
        file.close();
        Serial.println("Limpeza concluída!");
    }
};
