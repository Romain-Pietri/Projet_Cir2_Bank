#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <string>
#include <fstream>
#include "RapidXml/rapidxml.hpp"
#include "RapidXml/rapidxml_utils.hpp"
#include "RapidXml/rapidxml_print.hpp"
#include "moteur.hpp"
#include "xml_parser.hpp"
#include "client.hpp"
#include <thread>
#include <boost/asio.hpp>
#include <time.h>   


using std::vector;
using std::cout;
using std::endl;
using std::vector;
using namespace rapidxml;
using std::string;
using std::thread;

using namespace std;
//g++ test.cpp -o ok.exe  -lsfml-graphics -lsfml-window -lsfml-system 
class Input_text{
    private:
        int posxd;
        int posyd;
        int posxf;
        int posyf;
        bool vide;
        string text;
        bool clicked;
        bool ispassword;


    public :
        Input_text(int posxd, int posyd, int posxf, int posyf,bool ispassword=false){
            this->posxd = posxd;
            this->posyd = posyd;
            this->posxf = posxf;
            this->posyf = posyf;
            this->vide = true;
            this->text = "";
            clicked=false;
            this->ispassword = ispassword;
        }
        void ajoute_char(char c){
            if(this->vide){
                if(isdigit(c) || ispassword==true){
                    this->text = c;
                    this->vide = false;
                }
                else{
                    this->text = "Veuillez entrer un nombre";
                    this->vide = false;
                }
            }
            else{
                if(isdigit(c) || ispassword==true){
                    this->text += c;
                }
                else{
                    this->text = "Veuillez entrer un nombre";
                }
            } 
        }


        void supprime_char(){
            if(this->vide){
                return;
            }
            else{
                this->text.pop_back();
                if(this->text.empty()){
                    this->vide = true;
                }
            }
            
            
        }
        void afficherText(sf::RenderWindow &window){
            sf::Font font;
            if (!font.loadFromFile("police.otf"))
            {
                cout << "erreur chargement font" << endl;
            }
            
            sf::Text text;
            text.setFont(font);
            if(this->ispassword){
                string s = "";
                for(int i=0;i<this->text.size();i++){
                    s += "*";
                }
                text.setString(s);
            }
            else if(!this->vide){
                text.setString(this->text);
            }
            else{text.setString("Entrez le texte");}
            text.setCharacterSize(24);
            text.setFillColor(sf::Color(249, 228, 183));
            //centre le texte au milieu du rectangle
            text.setPosition(posxd+((posxf-posxd)/2)-(text.getLocalBounds().width/2), posyd+((posyf-posyd)/2)-(text.getLocalBounds().height/2));
            window.draw(text);
        }
        void afficher(sf::RenderWindow &window){
            sf::RectangleShape rectangle(sf::Vector2f(posxf-posxd, posyf-posyd));
            sf::RectangleShape rectangle2(sf::Vector2f(posxf-posxd+6, posyf-posyd+6));
            rectangle2.setFillColor(sf::Color(50,50,50));
            if(clicked){
                // sf::RenderWindow window2(sf::VideoMode(610, 400), "SFML works!",sf::Style::Close);
                // window2.display();
                // clicked = false;
            }
            else{
                rectangle.setFillColor(sf::Color(120, 120, 120));
            }
            //rectangle.setFillColor(sf::Color(255, 255, 255));
            rectangle.setPosition(posxd, posyd);
            rectangle2.setPosition(posxd-3, posyd-3);
            window.draw(rectangle2);
            window.draw(rectangle);
            afficherText(window);
        }
        
        bool isbind(int x, int y){
            return (x>=posxd && x<=posxf && y>=posyd && y<=posyf);
        }
        string getText(){
            return this->text;
        }
        void setClicked(bool b){
            this->clicked = b;
        }
        bool getClicked(){
            return this->clicked;
        }
 
};
class client{
    public:
        string id,name;
};

class Carre{

    private:
        int posxd;//position x début
        int posyd;//position y début
        int posxf;//position x fin
        int posyf;//position y fin
        sf::RectangleShape carre;//tkt c'est juste un rectangle
        int id;//id pour les fonction apres tkt
        int r;//couleur rgb du carré
        int g;
        int b;
        int rt;//couleur rgb du texte
        int gt;
        int bt;
        string text;//texte du carré
        bool clicked;
    public:
    Carre(){
        this->posxd = 0;
        this->posyd = 0;
        this->posxf = 0;
        this->posyf = 0;
        this->id = 0;
        this->r = 0;
        this->g = 0;
        this->b = 0;
        this->rt = 0;
        this->gt = 0;
        this->bt = 0;
        this->text = "";
        this->clicked=false;
    }
    Carre(int posxd, int posyd, int posxf, int posyf, int id, int r, int g, int b, string text, int rt, int gt, int bt){//constructeur bien badass
        this->posxd = posxd;
        this->posyd = posyd;
        this->posxf = posxf;
        this->posyf = posyf;
        this->id = id;
        this->r = r;
        this->g = g;
        this->b = b;
        this->rt=rt;
        this->gt=gt;
        this->bt=bt;
        this->text = text;
        carre.setSize(sf::Vector2f(posxf-posxd, posyf-posyd));
        carre.setPosition(posxd, posyd);
        carre.setFillColor(sf::Color(r, g, b));
        clicked=false;
    }
    Carre(int posxd, int posyd, int posxf, int posyf, int id, int r, int g, int b){
        this->posxd = posxd;
        this->posyd = posyd;
        this->posxf = posxf;
        this->posyf = posyf;
        this->id = id;
        this->r = r;
        this->g = g;
        this->b = b;
        carre.setSize(sf::Vector2f(posxf-posxd, posyf-posyd));
        carre.setPosition(posxd, posyd);
        carre.setFillColor(sf::Color(r, g, b));
        this->text="";
        clicked=false;
    }
    void setter_carre(string txt){
        this->text = txt;
    }
    void setter(int posxd,int posyd,int posxf,int posyf,int id,int r,int g,int b,string text,int rt,int gt,int bt){
        this->posxd = posxd;
        this->posyd = posyd;
        this->posxf = posxf;
        this->posyf = posyf;
        this->id = id;
        this->r = r;
        this->g = g;
        this->b = b;
        this->rt=rt;
        this->gt=gt;
        this->bt=bt;
        this->text = text;
        carre.setSize(sf::Vector2f(posxf-posxd, posyf-posyd));
        carre.setPosition(posxd, posyd);
        carre.setFillColor(sf::Color(r, g, b));
    }
    void setTxt(string txt){
        this->text = txt;
    }
    void afficherText(sf::RenderWindow &window){
        sf::Font font;
        if (!font.loadFromFile("police.otf"))
        {
            cout << "erreur chargement font" << endl;
        }
        
        sf::Text text;
        text.setFont(font);
        text.setString(this->text);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color(rt, gt, bt));
        
        text.setPosition(posxd+(posxf-posxd)/2-text.getLocalBounds().width/2, posyd+(posyf-posyd)/2-text.getLocalBounds().height/2-5);
        window.draw(text);
    }
    void afficher(sf::RenderWindow &window){//appelle cette fonction pour afficher le carrer #obligatoire
        if(clicked){
            carre.setFillColor(sf::Color::Green);
        }
        else{
            carre.setFillColor(sf::Color(r, g, b));
        }
        window.draw(carre);
        afficherText(window);
    }

    int afficherDR(sf::RenderWindow &window2, sf::Event event_, int DoR, vector<Client> &Bdd_client,int id_client,bool &shutdown, int id_agence){   // AFFICHAGE DES FENETRES DEPOT ET RETRAIT     
        Input_text input(10, 110, 400, 150);
        string txt = "";
        
        if(DoR == 1){
            txt = "Inserez un montant a deposer ";
        }
        else{
            txt = "Inserez un montant a retirer : ";
        }
        Carre explication(10, 10, 400, 100, 1, 255, 0, 0, txt, 255, 255, 255);
        Carre confirmation(410, 108, 550, 152, 1, 255, 0, 0, "Valider", 255, 255, 255);
        bool bugged=false;
        int resultConf = 0;
        while (window2.isOpen()){
            while (window2.pollEvent(event_)){
                if (event_.type == sf::Event::Closed){
                window2.close();
                shutdown=true;
                send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
            }
                if(confirmation.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    confirmation.setclicked(true);
                    string tmp = input.getText();
                    window2.clear();
                    window2.close();

                    sf::RenderWindow window3(sf::VideoMode(650, 400), "Confirmation",sf::Style::Close);
                    
                    if(DoR == 0){
                        
                        resultConf = afficherC(window3, event_, tmp,1, Bdd_client, id_client,shutdown, id_agence);

                    }
                    else if(DoR == 1){

                        resultConf = afficherC(window3, event_, tmp,2, Bdd_client, id_client,shutdown, id_agence);
                    }

                    if(resultConf == 0){//Si opération annulée on revient à la page D ou R
                        if(DoR == 1){
                            sf::RenderWindow window2(sf::VideoMode(610, 400), "DEPOT",sf::Style::Close);
                            afficherDR(window2, event_, 1, Bdd_client, id_client, shutdown, id_agence);
                        }
                        else{
                            sf::RenderWindow window2(sf::VideoMode(610, 400), "RETRAIT",sf::Style::Close);
                            afficherDR(window2, event_, 0, Bdd_client, id_client, shutdown, id_agence);
                        }
                        
                    }
                    else{
                        if(DoR==1){
                            Bdd_client[id_client].set_solde_courant(Bdd_client[id_client].get_solde_courant()+stoi(tmp));
                        }
                        else{
                            Bdd_client[id_client].set_solde_courant(Bdd_client[id_client].get_solde_courant()-stoi(tmp));
                        }
                        goto end;
                    }
                    
                }
                if(input.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        input.setClicked(true);
                }
                if(event_.type==sf::Event::TextEntered){
                    if(input.getClicked()){

                        if(event_.text.unicode<128){
                            if(event_.text.unicode==8){
                                input.supprime_char();
                            }
                            else if(event_.text.unicode==13){
                                input.setClicked(false);
                            }
                            else{
                                input.ajoute_char(event_.text.unicode);
                            }
                        }
                    }
                }
                if (event_.type == sf::Event::Closed){
                    end:
                    window2.clear();
                    window2.close();
                }
                
            }
            window2.clear();

            input.afficher(window2);
            explication.afficher(window2);
            confirmation.afficher(window2);
            window2.display();
        }

        return 1;

    }
    int getId(){
        return id;
    }
    bool isbind(int x, int y){//si le carré est bind avec la souris
        if(x >= posxd && x <= posxf && y >= posyd && y <= posyf){
            return true;
        }
        return false;
    }
    void setclicked(bool a){
        this->clicked=a;
    }
    bool getclicked(){
        return this->clicked;
    }
    int afficherC(sf::RenderWindow &window3, sf::Event event_, string tmp_, int type_, vector<Client> &Bdd_client,int id_client, bool &shutdown, int id_agence){ 
        string type_txt = "erreur";
        if(type_ == 1){//Retrait
            type_txt = "retrait ";
        }
        else if(type_ == 2){//Depot
            type_txt = "depot ";
        }
        else if(type_ == 3){//Virement
            type_txt = "virement ";
        }
        string txt = "Confirmer le " + type_txt + "de " + tmp_ + " euros ?";
        Carre validation(80, 10, 580, 100, 1, 255, 0, 0, txt, 255, 255, 255);
        Carre confirmer(130, 110, 320, 200, 1, 255, 0, 0, "Confirmer", 255, 255, 255);
        Carre annuler(330, 110, 520, 200, 1, 255, 0, 0, "Annuler", 255, 255, 255);
        int counter = 0;
        bool bugged = false;
        while (window3.isOpen()){
            while (window3.pollEvent(event_)){
                if(confirmer.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    if(counter >= 4){ // Si quelqu'un comprend pourquoi le bouton est cliqué automatiquement aux 4 premières itérations...
                        window3.clear();
                        window3.close();
                        return 1;
                    }
                }
                if(annuler.isbind(event_.mouseButton.x, event_.mouseButton.y)){

                    if(counter >= 4){//Pareil
                        window3.clear();
                        window3.close();
                        return 0;
                    }
                }
                if (event_.type == sf::Event::Closed){
                    window3.clear();
                    window3.close();
                }
                counter+=1;
            }
            validation.afficher(window3);
            confirmer.afficher(window3);
            annuler.afficher(window3);
            window3.display();
        }
        return 0;
    }

    int afficherV(sf::RenderWindow &window2, sf::Event event_, vector<Client> &Bdd_client,int id_client,bool &shutdown, int id_agence){     /// AFFICHAGE DE LA FENETRE VIREMENT
        
        Carre explication(10, 10, 720, 100, 1, 255, 0, 0, "Inserer le montant du virement et l'id du destinataire : ", 255, 255, 255);
        //creer un carre choix compte qui est centré et qui demande depuis quel compte on veut faire le virement
        Carre choix_compte(10, 108, 720, 152, 1, 255, 0, 0, "Depuis quel compte voulez-vous faire le virement ?", 255, 255, 255);
        //creer 3 carres aligné sur l'horizontale qui contiennent les comptes
        Carre compte1(10, 160, 240, 200, 1, 255, 0, 0, "Compte 1", 255, 255, 255);
        Carre compte2(260, 160, 490, 200, 1, 255, 0, 0, "Compte 2", 255, 255, 255);
        Carre compte3(510, 160, 740, 200, 1, 255, 0, 0, "Compte 3", 255, 255, 255);
        
        //creer un carre qui demande le montant du virement
        Carre montant(10, 208, 200, 252, 1, 255, 0, 0, "Montant du virement : ", 255, 255, 255);
        //creer une input text qui prend le montant du virement
        Input_text input(10, 260, 200 , 300);
        //creer un carre qui demande l'id du destinataire aligné au milieu
        Carre id_destinataire(260, 208, 460, 252, 1, 255, 0, 0, "Id du destinataire : ", 255, 255, 255);
        //creer une input text qui prend l'id du destinataire
        Input_text id_(260, 260, 460, 300);
        //creer un carre qui demande le mot de passe du compte
        Carre mot_de_passe(510, 208, 710, 252, 1, 255, 0, 0, "Mot de passe : ", 255, 255, 255);
        //creer une input text qui prend le mot de passe
        Input_text mdp_(510, 260, 710, 300, true);
        //creer un carre qui confirme le virement en bas a droite
        Carre confirmation(510, 308, 710, 352, 1, 255, 0, 0, "Confirmer", 255, 255, 255);
        

        
        
        

        
        
        
        int resultConf = 0;
        bool bugged=false;
        while (window2.isOpen()){
            
            while (window2.pollEvent(event_)){
                if (event_.type == sf::Event::Closed){
                    window2.close();
                    shutdown=true;
                    send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
                }
                if(event_.type==sf::Event::MouseButtonPressed){
                    if(compte1.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        compte1.setclicked(true);
                        compte2.setclicked(false);
                        compte3.setclicked(false);
                    }
                    if(compte2.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        compte2.setclicked(true);
                        compte1.setclicked(false);
                        compte3.setclicked(false);
                    }
                    if(compte3.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        compte3.setclicked(true);
                        compte1.setclicked(false);
                        compte2.setclicked(false);
                    }

                    if(input.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        input.setClicked(true);
                        id_.setClicked(false);
                        mdp_.setClicked(false);
                    }
                    
                    if(id_.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        id_.setClicked(true);
                        input.setClicked(false);
                        mdp_.setClicked(false);
                    }
                    if(mdp_.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        mdp_.setClicked(true);
                        input.setClicked(false);
                        id_.setClicked(false);
                    }
                    
                    if(confirmation.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        confirmation.setclicked(true);
                        string tmp = input.getText();
                        string tmp2 = id_.getText();
                        if(tmp==""||tmp2=="" ||(compte1.getclicked()==false && compte2.getclicked()==false && compte3.getclicked()==false)){
                            explication.setTxt("Veuillez remplir tous les champs et/ou cliquer sur le compte depuis lequel vous voulez faire le virement");
                        }
                    
                        else{
                            window2.clear();
                            window2.close();

                            sf::RenderWindow window3(sf::VideoMode(650, 400), "Confirmation",sf::Style::Close);
                            resultConf = afficherC(window3, event_, tmp,3, Bdd_client, id_client, shutdown, id_agence);

                            if(resultConf == 0){//Si virement annulé on revient à la page virement
                                sf::RenderWindow window2(sf::VideoMode(710, 400), "VIREMENT",sf::Style::Close);
                                afficherV(window2, event_, Bdd_client, id_client, shutdown, id_agence);
                            }
                            else{
                                window2.close();
                                
                                if(send_to_serveur("6/"+tmp2+"/"+tmp+"\n",1235)[0]=='1'){
                                    explication.setTxt("Virement effectué avec succès");
                                    if(compte1.getclicked()){
                                        Bdd_client[id_client].set_solde_courant(Bdd_client[id_client].get_solde_courant()-std::stoi(tmp));
                                    }
                                    else if(compte2.getclicked()){
                                        Bdd_client[id_client].set_solde_epargne1(Bdd_client[id_client].get_solde_epargne1()-std::stoi(tmp));
                                    }
                                    else if(compte3.getclicked()){
                                        Bdd_client[id_client].set_solde_epargne2(Bdd_client[id_client].get_solde_epargne2()-std::stoi(tmp));
                                    }
                                    

                                }
                                else{
                                    explication.setTxt("Virement échoué");
                                }
                            }
                            
                        }
                    }
                }
                if(event_.type==sf::Event::TextEntered){
                    if(input.getClicked()){

                        if(event_.text.unicode<128){
                            if(event_.text.unicode==8){
                                input.supprime_char();
                            }
                            else if(event_.text.unicode==13){
                                input.setClicked(false);
                            }
                            else
                            {
                                input.ajoute_char(event_.text.unicode);
                            }
                        }
                    }
                    if(id_.getClicked()){
                        if(event_.text.unicode<128){
                            if(event_.text.unicode==8){
                                id_.supprime_char();
                            }
                            else if(event_.text.unicode==13){
                                id_.setClicked(false);
                            }
                            else
                            {
                                id_.ajoute_char(event_.text.unicode);
                            }
                        }
                    }
                    if(mdp_.getClicked()){
                        if(event_.text.unicode<128){
                            if(event_.text.unicode==8){
                                mdp_.supprime_char();
                            }
                            else if(event_.text.unicode==13){
                                mdp_.setClicked(false);
                            }
                            else
                            {
                                mdp_.ajoute_char(event_.text.unicode);
                            }
                        }
                    }
                }
                if (event_.type == sf::Event::Closed){
                    window2.close();
                }
            }
            window2.clear();

            explication.afficher(window2);
            confirmation.afficher(window2);
            choix_compte.afficher(window2);
            compte1.afficher(window2);
            compte2.afficher(window2);
            compte3.afficher(window2);
            input.afficher(window2);
            id_.afficher(window2);
            montant.afficher(window2);
            mdp_.afficher(window2);
            mot_de_passe.afficher(window2);
            id_destinataire.afficher(window2);
            window2.display();
        }
        return 1;
    }

    void suppression(int id, vector<Client> &Bdd_client, sf::RenderWindow &window3, sf::Event event_,bool &shutdown, int id_agence){ //SUPPRESSION CLIENTS
        Carre validation(10, 10, 630, 100, 1, 255, 0, 0, "Voulez-vous vraiment supprimer le client " + Bdd_client[id].get_name() + " ?", 255, 255, 255);
        Carre confirmer(130, 110, 320, 200, 1, 255, 0, 0, "Confirmer", 255, 255, 255);
        Carre annuler(330, 110, 520, 200, 1, 255, 0, 0, "Annuler", 255, 255, 255);
        int counter = 0;
        bool bugged = false;
        while (window3.isOpen()){
            while (window3.pollEvent(event_)){
                if(confirmer.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    //if(counter >= 4){ // Si quelqu'un comprend pourquoi le bouton est cliqué automatiquement aux 4 premières itérations...
                        Bdd_client.erase(Bdd_client.begin()+id);
                        send_to_serveur("5/"+to_string(id)+"\n",1235);
                        window3.clear();
                        window3.close();
                        
                        //return Bdd_client;
                    //}
                }
                if(annuler.isbind(event_.mouseButton.x, event_.mouseButton.y)){

                    if(counter >= 4){//Pareil
                        window3.clear();
                        window3.close();
                        //return Bdd_client;
                    }
                }
                if (event_.type == sf::Event::Closed){
                    window3.clear();
                    window3.close();
                }
                counter+=1;
            }
            validation.afficher(window3);
            confirmer.afficher(window3);
            annuler.afficher(window3);
            window3.display();
        }
    }
    void suppressionB(int id, vector<Client> &Bdd_banque, sf::RenderWindow &window3, sf::Event event_,bool &shutdown, int id_agence){ //SUPPRESSION BANQUES
        Carre validation(10, 10, 630, 100, 1, 255, 0, 0, "Voulez-vous vraiment supprimer l'agence " + Bdd_banque[id].get_name() + " ?", 255, 255, 255);
        Carre confirmer(130, 110, 320, 200, 1, 255, 0, 0, "Confirmer", 255, 255, 255);
        Carre annuler(330, 110, 520, 200, 1, 255, 0, 0, "Annuler", 255, 255, 255);
        int counter = 0;
        bool bugged = false;
        while (window3.isOpen()){
            while (window3.pollEvent(event_)){
                if(confirmer.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    //if(counter >= 4){ // Si quelqu'un comprend pourquoi le bouton est cliqué automatiquement aux 4 premières itérations...
                        Bdd_banque.erase(Bdd_banque.begin()+id);
                        window3.clear();
                        window3.close();
                        
                        //return Bdd_client;
                    //}
                }
                if(annuler.isbind(event_.mouseButton.x, event_.mouseButton.y)){

                    if(counter >= 4){//Pareil
                        window3.clear();
                        window3.close();
                        //return Bdd_client;
                    }
                }
                if (event_.type == sf::Event::Closed){
                    window3.clear();
                    window3.close();
                }
                counter+=1;
            }
            validation.afficher(window3);
            confirmer.afficher(window3);
            annuler.afficher(window3);
            window3.display();
        }
    }
    void afficherGC(sf::RenderWindow &window2, sf::Event event_, vector<Client> &Bdd_client, int id_client,bool &shutdown, int id_agence){//GERER CLIENTS
        debut:
        Carre info(10, 10, 250, 100, 1, 255, 0, 0, "Liste des clients : ", 255, 255, 255);
        vector<Carre> MonMoiVector;
        vector<Carre> MonMoiVectorSuppr;
        int hauteur1 = 0;
        int hauteur2 = 0;
        int nbr_clients = Bdd_client.size() - 1;
        for(int i = 0; i < Bdd_client.size(); ++i){
            hauteur1 += 110;
            hauteur2 = hauteur1 + 90;
            MonMoiVector.push_back(Carre(10, hauteur1, 200, hauteur2, -1, 255, 0, 0, Bdd_client[i].get_name(), 255, 255, 255));
            MonMoiVectorSuppr.push_back(Carre(210, hauteur1, 400, hauteur2, i, 255, 0, 0, "Supprimer", 255, 255, 255));
        }
        int counter = 0;
        while (window2.isOpen())
        {
            while (window2.pollEvent(event_))
            {
                if (event_.type == sf::Event::Closed){
                    window2.close();
                    shutdown=true;
                    send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
                }
                if(event_.type==sf::Event::MouseButtonPressed){
                    if(event_.mouseButton.button==sf::Mouse::Left){
                        for(int i = 0; i < Bdd_client.size(); ++i){
                            if(MonMoiVectorSuppr[i].isbind(event_.mouseButton.x, event_.mouseButton.y)){
                                window2.close();
                                sf::RenderWindow windowSuppr(sf::VideoMode(640, 420), "Suppression",sf::Style::Close);
                                suppression(i, Bdd_client, windowSuppr, event_, shutdown, id_agence);
                                goto debut;


                            }
                        }
                    }
                }
                //counter +=1;
                if (event_.type == sf::Event::Closed)
                    window2.close();
            }
            window2.clear();
            info.afficher(window2);
            for(int i = 0; i <= nbr_clients; ++i){
                MonMoiVector[i].afficher(window2);
                MonMoiVectorSuppr[i].afficher(window2);
            }
            window2.display();
        }
    }
    /*
    void afficherGB(sf::RenderWindow &window2, sf::Event event_, vector<Client> &Bdd_client, int id_client,bool &shutdown){//GERER BANQUES
        debut:
        Carre info(10, 10, 250, 100, 1, 255, 0, 0, "Liste des banques : ", 255, 255, 255);
        vector<Carre> MonMoiVector;
        vector<Carre> MonMoiVectorSuppr;
        int hauteur1 = 0;
        int hauteur2 = 0;
        //int nbr_banques = Bdd_banque.size() - 1;
        for(int i = 0; i < Bdd_banque.size(); ++i){
            hauteur1 += 110;
            hauteur2 = hauteur1 + 90;
            MonMoiVector.push_back(Carre(10, hauteur1, 200, hauteur2, -1, 255, 0, 0, Bdd_banque[i].get_name(), 255, 255, 255));
            MonMoiVectorSuppr.push_back(Carre(210, hauteur1, 400, hauteur2, i, 255, 0, 0, "Supprimer", 255, 255, 255));
        }
        int counter = 0;
        while (window2.isOpen())
        {
            while (window2.pollEvent(event_))
            {
                if(event_.type==sf::Event::MouseButtonPressed){
                    if(event_.mouseButton.button==sf::Mouse::Left){
                        for(int i = 0; i < Bdd_banque.size(); ++i){
                            if(MonMoiVectorSuppr[i].isbind(event_.mouseButton.x, event_.mouseButton.y)){
                                window2.close();
                                sf::RenderWindow windowSuppr(sf::VideoMode(640, 420), "Suppression",sf::Style::Close);
                                suppressionB(i, Bdd_banque, windowSuppr, event_, shutdown);
                                goto debut;


                            }
                        }
                    }
                }
                //counter +=1;
                if (event_.type == sf::Event::Closed)
                    window2.close();
            }
            window2.clear();
            info.afficher(window2);
            for(int i = 0; i <= nbr_banques; ++i){
                MonMoiVector[i].afficher(window2);
                MonMoiVectorSuppr[i].afficher(window2);
            }
            window2.display();
        }
    }*/
};
void window_1(vector<Client> &Bdd_client, int id_client, bool &shutdown, int id_agence){ // FENETRE CLIENTS
    debut :

    sf::RenderWindow window(sf::VideoMode(610, 400), "Bienvenue !",sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Carre carre(10, 10, 200, 100, 1, 255, 0, 0, "DEPOT", 255, 255, 255);
    Carre carre2(210, 10, 400, 100, 1, 255, 0, 0, "RETRAIT", 255, 255, 255);
    Carre carre3(410, 10, 600, 100, 1, 255, 0, 0, "VIREMENT", 255, 255, 255);
    
    bool bugged=false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                shutdown=true;
                send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
            }
            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(carre.isbind(event.mouseButton.x, event.mouseButton.y)){
                        window.close();
                        sf::RenderWindow window2(sf::VideoMode(610, 400), "DEPOT",sf::Style::Close);
                        carre.afficherDR(window2, event, 1, Bdd_client, id_client, shutdown, id_agence);
                        goto debut;

                    }
                    if(carre2.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre2.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(610, 400), "RETRAIT",sf::Style::Close);
                        carre.afficherDR(window2, event, 0, Bdd_client, id_client, shutdown, id_agence);
                        goto debut;
                    }
                    if(carre3.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre3.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(710, 400), "VIREMENT",sf::Style::Close);
                        carre.afficherV(window2, event, Bdd_client, id_client, shutdown, id_agence);
                        goto debut;
                    }
                }
            }
            if(event.type==sf::Event::MouseButtonReleased){
                if(event.mouseButton.button==sf::Mouse::Left){
                    
                }
                if(event.mouseButton.button==sf::Mouse::Left){
                    
                }
                if(event.mouseButton.button==sf::Mouse::Left){
                    
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        carre.afficher(window);
        carre2.afficher(window);
        carre3.afficher(window);
        window.display();
    }
} 
void window_BC(vector<Client> &Bdd_client, vector<Client> &Bdd_banque,int id_client,bool &shutdown, int id_agence){ //FENETRE ADMIN
    debut :

    sf::RenderWindow window(sf::VideoMode(610, 400), "Bienvenue !",sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Carre carre(10, 10, 200, 100, 1, 255, 0, 0, "Gerer clients", 255, 255, 255);
    Carre carre2(210, 10, 400, 100, 1, 255, 0, 0, "Gerer banques", 255, 255, 255);
    Carre carre3(410, 10, 600, 100, 1, 255, 0, 0, "Logs", 255, 255, 255);
    
    bool bugged=false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                shutdown=true;
                send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
            }
            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(carre.isbind(event.mouseButton.x, event.mouseButton.y)){
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(610, 900), "Gerer clients",sf::Style::Close);
                        carre.afficherGC(window2, event, Bdd_client, id_client, shutdown, id_agence);//Afficher : gerer clients
                        goto debut;

                    }
                    if(carre2.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre2.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(610, 900), "Gerer banques",sf::Style::Close);
                        //carre.afficherGB(window2, event, Bdd_banque, id_client, shutdown);//Afficher gerer banques
                        goto debut;
                    }
                    if(carre3.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre3.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(710, 400), "Logs",sf::Style::Close);
                        carre.afficherV(window2, event, Bdd_client, id_client, shutdown, id_agence);
                        goto debut;
                    }
                }
            }
            if(event.type==sf::Event::MouseButtonReleased){
                if(event.mouseButton.button==sf::Mouse::Left){
                    
                }
                if(event.mouseButton.button==sf::Mouse::Left){
                    
                }
                if(event.mouseButton.button==sf::Mouse::Left){
                    
                }
            }
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        
        carre.afficher(window);
        carre2.afficher(window);
        carre3.afficher(window);
        window.display();
    }
} 
/*
void window_2(){
    sf::RenderWindow window(sf::VideoMode(900, 800), "SFML works!",sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Carre texte_bienvenu(420, 50, 480, 150, 3, 255, 243, 216, "Bienvenue ! Que voulez vous faire ?", 115, 0, 0);
    Carre fond(0,0,900,800,2, 255,243,216);
    Carre texte_banque(450, 10, 450, 50, 1, 255, 243, 216, "NotStonksBank", 115, 0, 0);
    Carre texte_recherche(10,150,390,200, 4, 255, 243, 216, "Rechercher une banque", 115, 0, 0);
    Input_text input(10, 240, 390, 280);

    vector <Carre> Boutons;

    bool bugged=false;
    if(!doc.LoadFile()){
        cout<< "erreur lors du chargement" << endl;
        cout << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
        //return 1;
    }
    TiXmlHandle hdl(&doc);
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
    client cl;
    if(!elem){
        cerr << "le nœud à atteindre n'existe pas" << endl;
        //return 2;
    }
    list<client> user_list;
    vector<string> liste;
    vector<Carre> Affichage;
    //list<client>::iterator i;
    while (elem){
       cl.name = elem->Attribute("name");
      //  cout<<cl.name;
        cl.id = elem->Attribute("id");
        user_list.push_back(cl);
        // string txt = elem->Attribute("name");
        // liste.push_back(txt);
        //cout<<"coucou?"<<endl;
        //Carre txt(420, 500, 480, 550, 3, 255, 243, 216, "test", 115, 0, 0);
        elem = elem->NextSiblingElement(); // iteration 

    }


    Carre txt(40, 250, 480, 300, 5, 255, 243, 216, "", 115, 0, 0);
    while (window.isOpen()){
        sf::Event event;
        //cout<<"fenetre"<<endl;
        while (window.pollEvent(event))
        {
           // cout<<"heloo?"<<endl;
            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(input.isbind(event.mouseButton.x, event.mouseButton.y)){
                        input.setClicked(true);
                    }
                    else{input.setClicked(false);}
                    for(int i=0;i<Boutons.size();i++){
                        if(Boutons[i].isbind(event.mouseButton.x, event.mouseButton.y)){
                            Boutons[i].setclicked(true);
                        }
                        else{
                            Boutons[i].setclicked(false);
                        }
                    }
                }
            }
            if(event.type==sf::Event::MouseButtonReleased){
                if(event.mouseButton.button==sf::Mouse::Left){
                    for(int i=0;i<Boutons.size();i++){
                        if(Boutons[i].isbind(event.mouseButton.x, event.mouseButton.y)){
                            Boutons[i].setclicked(false);
                        }
                    }
                }

            }

            if(event.type==sf::Event::TextEntered){
                if(input.getClicked()){
                    if(event.text.unicode<128){
                        if(event.text.unicode==8){
                            input.supprime_char();
                        }
                        else if(event.text.unicode==13){
                            input.setClicked(false);
                        }
                        else{

                            input.ajoute_char(event.text.unicode);
                            cout<<input.getText()<<endl;
                        }
                    }
                }
            }
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        list<client>::iterator i;
        string txt_inte = "";
        for(i=user_list.begin(); i!=user_list.end(); i++){
          // cout << i->name << " "<< i->id << endl;
           txt_inte += i->name + " " + i->id;

           txt_inte += "\n";
            }
        txt.setter_carre(txt_inte);
        window.clear();

        fond.afficher(window);


        // for(int i=0;i<Boutons.size();i++){
        //     Boutons[i].afficher(window);
        // }
        // for(int i = 0; i<Affichage.size();i++){
        //     Affichage[i].afficher(window);

        // }
        txt.afficher(window);
        texte_banque.afficher(window);
        texte_bienvenu.afficher(window);
        texte_recherche.afficher(window);
        //carre.afficherText(window);
        //window.draw(shape);
        //input.afficher(window);
        window.display();



    } 
}
*/

void connexion(vector<Client> &Bdd_client,bool &shutdown, int id_agence){
    sf::RenderWindow window(sf::VideoMode(610, 400), "Bienvenue !",sf::Style::Close);
    
    Carre texte_client(295,60,315,80,95,255,243,216,"Veuillez entrer vos identifiants",115,0,0);
    Input_text id(230, 120, 400, 150);
    
    int id_;
    Input_text password(230, 180, 400, 210,true);
    Carre fond(0, 0, 610, 400, 3, 255, 243, 216);
    Carre valider(230, 230, 400, 300, 3, 255, 243, 216, "Se connecter", 115, 0, 0);
    bool trouve=false;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                shutdown=true;
                //send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
            }
         

            if(event.type==sf::Event::TextEntered){
                    if(id.getClicked()){

                        if(event.text.unicode<128){
                            if(event.text.unicode==8){
                                id.supprime_char();
                            }
                            else if(event.text.unicode==13){
                                id.setClicked(false);
                            }
                            else
                            {
                                id.ajoute_char(event.text.unicode);
                            }
                        }
                    }
                    if(password.getClicked()){
                        if(event.text.unicode<128){
                            if(event.text.unicode==8){
                                password.supprime_char();
                            }
                            else if(event.text.unicode==13){
                                password.setClicked(false);
                            }
                            else
                            {
                                password.ajoute_char(event.text.unicode);
                            }
                        }
                    }
            }

            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(id.isbind(event.mouseButton.x, event.mouseButton.y)){
                        id.setClicked(true);
                    }
                    else{id.setClicked(false);}
                    if(password.isbind(event.mouseButton.x, event.mouseButton.y)){
                        password.setClicked(true);
                    }
                    else{password.setClicked(false);}

                    if(valider.isbind(event.mouseButton.x, event.mouseButton.y)){
                        if(id.getText()!="" && password.getText()!=""){
                        id_=std::stoi(id.getText());
                        for(int i=0; i<size(Bdd_client);++i){
                            if(Bdd_client[i].get_id()==id_){
                                trouve=true;
                                if(Bdd_client[i].get_password()==password.getText()){
                                    window.close();
                                    window_1(Bdd_client,i,shutdown,id_agence);
                                    
                                }
                                else{
                                    
                                    texte_client.setTxt("Mot de passe incorrect, veuillez reessayer");
                                }
                            }
                        }
                        if(!trouve){
                            string res=send_to_serveur("4/"+std::to_string(id_)+"\n",1235); 
                            
                            if(res[0]=='-'){
                                
                                texte_client.setTxt("Identifiant incorrect, veuillez réessayer");
                            }
                            else{ 
                                window.close();
                                shutdown=true;
                                send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
                            }

                        }   
                        }
                        
                    }
                }
            }
        }
            window.clear();
            fond.afficher(window);
            texte_client.afficher(window);
            id.afficher(window);
            password.afficher(window);
            valider.afficher(window);
            window.display();
         
    }
}


int main()
{
    int id_agence= stoi(recup_info());//ABSOLUMENT A CHANGER
    vector<Client> Bdd_client=reader();
    bool shutdown=false;
    thread t1(write_every30sec,std::ref(Bdd_client),std::ref(shutdown));
    thread t2(connexion,std::ref(Bdd_client),std::ref(shutdown),id_agence);
    thread t3(interet_epargne1,std::ref(Bdd_client),std::ref(shutdown));
    thread t4(interet_epargne2,std::ref(Bdd_client),std::ref(shutdown));
    thread t5(client_thread,std::ref(Bdd_client),std::ref(shutdown));


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}
