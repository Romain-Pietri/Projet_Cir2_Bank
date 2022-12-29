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
void connexion(vector<Client> &Bdd_client,bool &shutdown, int id_agence);
void window_1(vector<Client> &Bdd_client, int id_client, bool &shutdown, int id_agence);
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
        int i2;
        bool onlynumber;


    public :
        Input_text(int posxd, int posyd, int posxf, int posyf,bool ispassword=false, bool onlynumber=true){
            this->posxd = posxd;
            this->posyd = posyd;
            this->posxf = posxf;
            this->posyf = posyf;
            this->vide = true;
            this->text = "";
            this->i2 = 0;
            clicked=false;
            this->ispassword = ispassword;
            this->onlynumber = onlynumber;
        }
        void ajoute_char(char c){

            if(this->vide){
                if(isdigit(c) || ispassword==true || onlynumber==false){
                    
                    this->text = c;
                    this->vide = false;
                    this->i2=1;
                }
                else{
                    
            
                     if(this->i2==1){
                        this->text = c;
                    }
                    else this->text += c;
                    this->text = "Veuillez entrer un nombre";
                    this->vide = false;
                    this->i2=2;
                }
            }
            else{
                if(isdigit(c) || ispassword==true ||onlynumber==false){
                    
                    
                    if(this->i2==2){
                        this->text = c;
                    }
                    else this->text += c;
                    this->i2=1;
                }
                else{
                    this->text = "Veuillez entrer un nombre";
                    this->i2=2;
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
        Carre fond(0,0,610,400,4,255,243,216);
        Input_text input(10, 110, 400, 150);
        string txt = "";
        
        if(DoR == 1){
            txt = "Inserez un montant a deposer ";
        }
        else{
            txt = "Inserez un montant a retirer : ";
        }
        Carre explication(10, 10, 400, 100, 1, 255,243,216, txt, 115,0,0);
        Carre confirmation(410, 108, 550, 152, 1, 255,243,216, "Valider", 115,0,0);
        bool bugged=false;
        int resultConf = 0;
        while (window2.isOpen()){
            while (window2.pollEvent(event_)){
                
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
                            if(tmp!=""){
                                if(stoi(tmp)>0)Bdd_client[id_client].set_solde_courant(Bdd_client[id_client].get_solde_courant()+stoi(tmp));
                                else{
                                    explication.setTxt("Veuillez rentrer un nombre positif");
                                    window_1(Bdd_client, id_client, shutdown, id_agence);
                                }
                            }
                            else{
                                explication.setTxt("Rentrez un nombre");
                            }
                        }
                        else{
                            if(tmp!=""){
                                if(stoi(tmp)>0)Bdd_client[id_client].set_solde_courant(Bdd_client[id_client].get_solde_courant()-stoi(tmp));
                                else{
                                    explication.setTxt("Veuillez rentrer un nombre positif");
                                    window_1(Bdd_client, id_client, shutdown, id_agence);
                                }
                            }
                            else{
                                explication.setTxt("Rentrez un nombre");
                            }
                            
                        }
                        
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
                    window_1(Bdd_client, id_client, shutdown, id_agence);
                }
                
            }
            window2.clear();
            fond.afficher(window2);
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
        Carre validation(80, 10, 580, 100, 1, 255,243,216, txt, 115,0,0);
        Carre confirmer(130, 110, 320, 200, 1, 255,243,216, "Confirmer", 115,0,0);
        Carre annuler(330, 110, 520, 200, 1, 255,243,216, "Annuler", 115,0,0);
        int counter = 0;
        bool bugged = false;
        while (window3.isOpen()){
            while (window3.pollEvent(event_)){
                if(confirmer.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    if(counter >= 4 && Bdd_client[id_client].get_solde_courant()>std::stoi(tmp_)){ // Si quelqu'un comprend pourquoi le bouton est cliqué automatiquement aux 4 premières itérations...
                        window3.clear();
                        window3.close();
                        return 1;
                    }
                    if(Bdd_client[id_client].get_solde_courant()<std::stoi(tmp_)){
                       txt = "Vous n'avez pas assez d'argent sur votre compte courant";
                       window3.clear();
                       window3.close();
                       return 0;
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
            window3.clear();
            validation.afficher(window3);
            confirmer.afficher(window3);
            annuler.afficher(window3);
            window3.display();
        }
        return 0;
    }
    int afficherV(sf::RenderWindow &window2, sf::Event event_, vector<Client> &Bdd_client,int id_client,bool &shutdown, int id_agence){     /// AFFICHAGE DE LA FENETRE VIREMENT
        
        
        Carre fond2(0,0,800,700,35,255,243,216,"",0,0,0);
        Carre explication(10, 10, 720, 100, 1, 255, 243, 216, "Inserer le montant du virement et l'id du destinataire : ", 115,0,0);
        //creer un carre choix compte qui est centré et qui demande depuis quel compte on veut faire le virement
        Carre choix_compte(10, 108, 720, 152, 1, 255, 243, 216, "Depuis quel compte voulez-vous faire le virement ?", 115,0,0);
        //creer 3 carres aligné sur l'horizontale qui contiennent les comptes
        Carre compte1(10, 160, 240, 200, 1, 255, 243, 216, "Compte 1", 115,0,0);
        Carre compte2(260, 160, 490, 200, 1, 255, 243, 216, "Compte 2", 115,0,0);
        Carre compte3(510, 160, 740, 200, 1, 255, 243, 216, "Compte 3", 115,0,0);
        
        //creer un carre qui demande le montant du virement
        Carre montant(10, 208, 200, 252, 1, 255, 243, 216, "Montant : ",115,0,0);
        //creer une input text qui prend le montant du virement
        Input_text input(10, 260, 200 , 300);
        //creer un carre qui demande l'id du destinataire aligné au milieu
        Carre id_destinataire(260, 208, 460, 252, 1, 255, 243, 216, "Id du destinataire : ", 115,0,0);
        //creer une input text qui prend l'id du destinataire
        Input_text id_(260, 260, 460, 300);
        //creer un carre qui demande le mot de passe du compte
        Carre mot_de_passe(510, 208, 690, 252, 1, 255, 243, 216, "Mot de passe : ", 115,0,0);
        //creer une input text qui prend le mot de passe
        Input_text mdp_(510, 260, 690, 300, true);
        //creer un carre qui confirme le virement en bas a droite
        Carre confirmation(510, 308, 710, 352, 1, 255, 243, 216, "Confirmer", 115,0,0);
        

        
        
        

        
        
        
        int resultConf = 0;
        bool bugged=false;
        while (window2.isOpen()){
            
            while (window2.pollEvent(event_)){
                if (event_.type == sf::Event::Closed){
                    window2.close();
                    
                    
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
                            explication.setTxt("Veuillez remplir tous les champs");
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
                    else{
                        confirmation.setclicked(false);
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

            fond2.afficher(window2);
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

    
};

void supp(vector<Client> &Bdd_client, int id_client, int id_agence, bool &shutdown){
    //creer une fenetre demandans a l'utilisateur s'il veut vraiment supprimer son compte
    //si oui, supprimer le compte et revenir a la fenetre de connexion
    //si non, revenir a la fenetre de gestion de compte
    sf::RenderWindow windowSuppr(sf::VideoMode(640, 420), "Suppression",sf::Style::Close);
    Carre fond(0, 0, 640, 420, 1, 255, 243, 216, "", 255, 255, 255);
    Carre info(240, 10, 400, 100, 1, 255, 243, 216, "Voulez-vous vraiment supprimer votre compte ?", 115,0,0);
    Carre oui(250, 110, 300, 200, 1, 255, 243, 216, "OUI", 115,0,0);
    Carre non(350, 110, 400, 200, 1, 255, 243, 216, "NON", 115,0,0);
    
    while (windowSuppr.isOpen())
    {
        sf::Event event_;
        while (windowSuppr.pollEvent(event_))
        {
            if(event_.type==sf::Event::MouseButtonPressed){
                if(event_.mouseButton.button==sf::Mouse::Left){
                    if(oui.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        Bdd_client.erase(Bdd_client.begin() + id_client);
                        windowSuppr.close();
                        send_to_serveur("5/"+to_string(Bdd_client[id_client].get_id())+"\n",1235);
                        connexion(Bdd_client, shutdown, id_agence);
                    }
                    if(non.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                        windowSuppr.close();
                        window_1(Bdd_client, id_client, shutdown, id_agence);
                    }
                }
            }
            if (event_.type == sf::Event::Closed){
                windowSuppr.close();
                window_1(Bdd_client, id_client, shutdown, id_agence);
            }
        }
        windowSuppr.clear();
        fond.afficher(windowSuppr);
        info.afficher(windowSuppr);
        oui.afficher(windowSuppr);
        non.afficher(windowSuppr);
        windowSuppr.display();
    }

}
void window_1(vector<Client> &Bdd_client, int id_client, bool &shutdown, int id_agence){ // FENETRE CLIENTS
    debut :

    sf::RenderWindow window(sf::VideoMode(610, 400), "NotStonksBank",sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Carre fond(0, 0, 610, 400, 3, 255, 243, 216);
    Carre txt_bvn(255,100,355,120, 3,255,243,216,"Bonjour " +Bdd_client[id_client].get_name()+" "+Bdd_client[id_client].get_surname()+", que voulez vous faire ?",115,0,0);
    Carre carre(10, 170, 200, 250, 1, 116, 103, 82, "DEPOT", 255, 243, 216);
    Carre carre2(210, 170, 400, 250, 1, 116, 103, 82, "RETRAIT", 255, 243, 216);
    Carre carre3(410, 170, 600, 250, 1, 116, 103, 82, "VIREMENT", 255, 243, 216);
    Carre argent(255,130,355,150,3,255,243,216,"Vous avez " + to_string(Bdd_client[id_client].get_solde_courant()) + "€", 115,0,0);
    Carre suppression(255, 300, 355, 330, 1, 255, 243, 216, "Supprimer votre compte", 115, 0, 0);
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
                    if(suppression.isbind(event.mouseButton.x, event.mouseButton.y)){
                        suppression.setclicked(true);
                        window.close();
                        window.clear();
                        supp(Bdd_client, id_client, id_agence, shutdown);
                        
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
        fond.afficher(window);
        txt_bvn.afficher(window);
        suppression.afficher(window);
        carre.afficher(window);
        carre2.afficher(window);
        carre3.afficher(window);
        window.display();
    }
} 


void nouveau(vector<Client> &Bdd_client, bool &shutdown, int id_agence){
    sf::RenderWindow window(sf::VideoMode(610, 500), "Cree un Compte !",sf::Style::Close);
    Carre fond(0, 0, 610, 500, 3, 255, 243, 216);
    //creer un ensemble de input_text demandans les informations necessaires pour creer un compte
    // <name>John</name> <surname>Smith</surname> <age>25</age> <password>1234</password>
    Input_text name(230, 50, 400, 80,false,false);
    Input_text surname(230, 150, 400, 180,false,false);
    Input_text age(230, 250, 400, 280);
    Input_text password(230, 350, 400, 380,true,false);
    Input_text confirme_password(230, 430, 400, 460,true,false);
    Carre valider(330, 480, 370, 490, 3, 255, 243, 216, "Valider", 115, 0, 0);
    Carre retour(240, 480, 280, 490, 3, 255, 243, 216, "Retour", 115, 0, 0);
    Carre texte_client(295,20,315,40,50,255,243,216,"Veuillez entrer votre Nom",115,0,0);
    Carre texte_client2(295,100,315,130,95,255,243,216,"Veuillez entrer votre Prenom",115,0,0);
    Carre texte_client3(295,200,315,230,95,255,243,216,"Veuillez entrer votre Age",115,0,0);
    Carre texte_client4(295,300,315,330,95,255,243,216,"Veuillez entrer votre Mot de passe",115,0,0);
    Carre texte_client5(295,400,315,430,95,255,243,216,"Veuillez confirmer votre Mot de passe",115,0,0);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(name.isbind(event.mouseButton.x, event.mouseButton.y)){
                        name.setClicked(true);
                    }
                    else{name.setClicked(false);}
                    if(surname.isbind(event.mouseButton.x, event.mouseButton.y)){
                        surname.setClicked(true);
                    }
                    else{surname.setClicked(false);}
                    if(age.isbind(event.mouseButton.x, event.mouseButton.y)){
                        age.setClicked(true);
                    }
                    else{age.setClicked(false);}
                    if(password.isbind(event.mouseButton.x, event.mouseButton.y)){
                        password.setClicked(true);
                    }
                    else{password.setClicked(false);}
                    if(confirme_password.isbind(event.mouseButton.x, event.mouseButton.y)){
                        confirme_password.setClicked(true);
                    }
                    else{confirme_password.setClicked(false);}
                    if(valider.isbind(event.mouseButton.x, event.mouseButton.y)){
                        valider.setclicked(true);
                        //verifier si les informations sont correctes
                        if(name.getText()!="" && surname.getText()!="" && age.getText()!="" && password.getText()!="" && confirme_password.getText()!=""){
                            if(password.getText()==confirme_password.getText()){
                                //creer un nouveau client
                                string id = send_to_serveur("2/"+std::to_string(id_agence)+"\n",1235);
                                if(id[0]=='-') {cout<<"erreur"<<endl; return;}
                                int id_client = stoi(id);
                                Client new_client(id_client,name.getText(),surname.getText(),stoi(age.getText()),password.getText(),id_client+1,0,id_client+2,0,id_client,0);
                                Bdd_client.push_back(new_client);
                            }
                            else{
                                valider.setTxt("Les mots de passe ne correspondent pas");
                                }
                        }

                    }
                    else{
                        valider.setclicked(false);
                    }
                    if(retour.isbind(event.mouseButton.x, event.mouseButton.y)){
                        retour.setclicked(true);
                        window.close();
                        connexion(Bdd_client, shutdown, id_agence);
                    }
                    else{
                        retour.setclicked(false);
                    }
                
                }
            if(event.type==sf::Event::MouseButtonReleased){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(valider.isbind(event.mouseButton.x, event.mouseButton.y)){
                        valider.setclicked(false);
                    }
                    if(retour.isbind(event.mouseButton.x, event.mouseButton.y)){
                        retour.setclicked(false);
                    }
                }
            }
            }
            if(event.type==sf::Event::TextEntered){
                if(name.getClicked()){
                    if(event.text.unicode<128){
                        if(event.text.unicode==8){
                            name.supprime_char();
                        }
                        else if(event.text.unicode==13){
                            name.setClicked(false);
                        }
                        else{
                            name.ajoute_char(event.text.unicode);
                            cout<<name.getText()<<endl;
                        }
                    }
                }
                if(surname.getClicked()){
                    if(event.text.unicode<128){
                        if(event.text.unicode==8){
                            surname.supprime_char();
                        }
                        else if(event.text.unicode==13){
                            surname.setClicked(false);
                        }
                        else{
                            surname.ajoute_char(event.text.unicode);
                            cout<<surname.getText()<<endl;
                        }
                    }
                }
                if(age.getClicked()){
                    if(event.text.unicode<128){
                        if(event.text.unicode==8){
                            age.supprime_char();
                        }
                        else if(event.text.unicode==13){
                            age.setClicked(false);
                        }
                        else{
                            age.ajoute_char(event.text.unicode);
                            cout<<age.getText()<<endl;
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
                        else{
                            password.ajoute_char(event.text.unicode);
                            cout<<password.getText()<<endl;
                        }
                    }
                }
                if(confirme_password.getClicked()){
                    if(event.text.unicode<128){
                        if(event.text.unicode==8){
                            confirme_password.supprime_char();
                        }
                        else if(event.text.unicode==13){
                            confirme_password.setClicked(false);
                        }
                        else{
                            confirme_password.ajoute_char(event.text.unicode);
                            cout<<confirme_password.getText()<<endl;
                        }
                    }
                }
            
            
        }
        if(event.type==sf::Event::Closed){
                window.close();
                shutdown=true;
                send_to_serveur("9/"+std::to_string(id_agence)+"\n",1235);
            }
        }
        window.clear();
        fond.afficher(window);
        texte_client.afficher(window);
        texte_client2.afficher(window);
        texte_client3.afficher(window);
        texte_client4.afficher(window);
        texte_client5.afficher(window);
        name.afficher(window);
        surname.afficher(window);
        age.afficher(window);
        password.afficher(window);
        confirme_password.afficher(window);
        valider.afficher(window);
        retour.afficher(window);
        window.display();



    }
    
}


void connexion(vector<Client> &Bdd_client,bool &shutdown, int id_agence){
    sf::RenderWindow window(sf::VideoMode(610, 400), "Bienvenue  sur l'agence : "+std::to_string(id_agence)+" !",sf::Style::Close);
    
    Carre texte_client(295,60,315,80,95,255,243,216,"Veuillez entrer vos identifiants",115,0,0);
    Input_text id(230, 120, 400, 150);
    
    int id_;
    Input_text password(230, 180, 400, 210,true);
    Carre fond(0, 0, 610, 400, 3, 255, 243, 216);
    Carre valider(230, 230, 400, 300, 3, 255, 243, 216, "Se connecter", 115, 0, 0);
    Carre creer_compte(230, 300, 400, 330, 3, 255, 243, 216, "Creer un compte", 115, 0, 0);
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
                    if(creer_compte.isbind(event.mouseButton.x, event.mouseButton.y)){
                        window.close();
                        nouveau(Bdd_client,shutdown,id_agence);
                    }
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
            creer_compte.afficher(window);
            window.display();
         
    }
}


int main()
{
    int id_agence= stoi(recup_info());//ABSOLUMENT A CHANGER
    vector<Client> Bdd_client=reader();
    bool shutdown=false;
    try{
        send_to_serveur("8/"+std::to_string(id_agence)+"\n",1235);
    }
    catch(...){
        cout<<"Serveur non connecté"<<endl;
        return 0;
    }
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
