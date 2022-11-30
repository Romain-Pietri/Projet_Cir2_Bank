#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include <vector>
#include <thread>
#include <unistd.h>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinyxml.cpp"
#include "tinyxml/tinyxmlerror.cpp"
#include "tinyxml/tinyxmlparser.cpp"
#include "tinyxml/tinystr.h"
#include "tinyxml/tinystr.cpp"
#include <list>
TiXmlDocument doc("testxml.xml");


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
                if(isdigit(c)){
                    this->text = c;
                    this->vide = false;
                }
                else{
                    this->text = "Veuillez entrer un nombre";
                    this->vide = false;
                }
            }
            else{
                if(isdigit(c)){
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
            text.setFillColor(sf::Color(0, 0, 0));
            
            text.setPosition(18, posyd+(posyf-posyd)/2-text.getLocalBounds().height/2-5);
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
        int posyf;
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

    int afficherDR(sf::RenderWindow &window2, sf::Event event_, int DoR){   // AFFICHAGE DES FENETRES DEPOT ET RETRAIT     
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
                if(confirmation.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    confirmation.setclicked(true);
                    string tmp = input.getText();
                    window2.clear();
                    window2.close();

                    sf::RenderWindow window3(sf::VideoMode(650, 400), "Confirmation",sf::Style::Close);
                    
                    if(DoR == 0){
                        
                        resultConf = afficherC(window3, event_, tmp,1);
                    }
                    else if(DoR == 1){

                        resultConf = afficherC(window3, event_, tmp,2);
                    }

                    if(resultConf == 0){//Si opération annulée on revient à la page D ou R
                        if(DoR == 1){
                            sf::RenderWindow window2(sf::VideoMode(610, 400), "DEPOT",sf::Style::Close);
                            afficherDR(window2, event_, 1);
                        }
                        else{
                            sf::RenderWindow window2(sf::VideoMode(610, 400), "RETRAIT",sf::Style::Close);
                            afficherDR(window2, event_, 0);
                        }
                        
                    }
                    else{
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
    int afficherC(sf::RenderWindow &window3, sf::Event event_, string tmp_, int type_){ 
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

    int afficherV(sf::RenderWindow &window2, sf::Event event_){     /// AFFICHAGE DE LA FENETRE VIREMENT

        Input_text input(10, 110, 300, 150);
        Carre explication(10, 10, 720, 100, 1, 255, 0, 0, "Inserer le montant du virement et l'id du destinataire : ", 255, 255, 255);
        Carre confirmation(420, 108, 720, 152, 1, 255, 0, 0, "Valider", 255, 255, 255);
        Input_text id_(310, 108, 410, 152);
        int resultConf = 0;
        bool bugged=false;
        while (window2.isOpen()){
            while (window2.pollEvent(event_)){

                if(input.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    input.setClicked(true);
                }
                if(id_.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    id_.setClicked(true);
                }
                if(confirmation.isbind(event_.mouseButton.x, event_.mouseButton.y)){
                    confirmation.setclicked(true);
                    string tmp = input.getText();
                    window2.clear();
                    window2.close();

                    sf::RenderWindow window3(sf::VideoMode(650, 400), "Confirmation",sf::Style::Close);
                    resultConf = afficherC(window3, event_, tmp,3);

                    if(resultConf == 0){//Si virement annulé on revient à la page virement
                        sf::RenderWindow window2(sf::VideoMode(710, 400), "VIREMENT",sf::Style::Close);
                        afficherV(window2, event_);
                    }
                    else{
                        window2.close();
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
                }
                if (event_.type == sf::Event::Closed){
                    window2.close();
                }
            }
            window2.clear();

            explication.afficher(window2);
            confirmation.afficher(window2);
            input.afficher(window2);
            window2.display();
        }
        return 1;
    }
};
/*
void window_2(){
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

            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(carre.isbind(event.mouseButton.x, event.mouseButton.y)){
                        window.close();
                        sf::RenderWindow window2(sf::VideoMode(610, 400), "DEPOT",sf::Style::Close);
                        carre.afficherDR(window2, event, 1);
                        goto debut;

                    }
                    if(carre2.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre2.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(610, 400), "RETRAIT",sf::Style::Close);
                        carre.afficherDR(window2, event, 0);
                        goto debut;
                    }
                    if(carre3.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre3.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(730, 400), "VIREMENT",sf::Style::Close);
                        carre.afficherV(window2, event);
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
*/
void window_1(){
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

            if(event.type==sf::Event::MouseButtonPressed){
                if(event.mouseButton.button==sf::Mouse::Left){
                    if(carre.isbind(event.mouseButton.x, event.mouseButton.y)){
                        window.close();
                        sf::RenderWindow window2(sf::VideoMode(610, 400), "DEPOT",sf::Style::Close);
                        carre.afficherDR(window2, event, 1);
                        goto debut;

                    }
                    if(carre2.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre2.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(610, 400), "RETRAIT",sf::Style::Close);
                        carre.afficherDR(window2, event, 0);
                        goto debut;
                    }
                    if(carre3.isbind(event.mouseButton.x, event.mouseButton.y)){
                        carre3.setclicked(true);
                        window.close();
                        window.clear();
                        sf::RenderWindow window2(sf::VideoMode(710, 400), "VIREMENT",sf::Style::Close);
                        carre.afficherV(window2, event);
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

int main()
{
    window_2();

    
    return 0;
}