#include "Game.h"
#include "Building.h"
#include "ProgressToken.h"
#include "City.h"
#include "Card.h"

#include "EffectFactory.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTextStream>
#include <QString>

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    // QTextStream qin(stdin);
    // QString line = qin.readLine();
    // std::cout << "Vous avez entré : " << line.toStdString() << std::endl;

    City c;
    std::vector<RessourceType> vect_ress = {RessourceType::Glass,RessourceType::Paper,RessourceType::Wood};
    c.addRessource(vect_ress);
    c.getRessource(RessourceType::Paper)+=2;
    for (auto& r : c.getRessources()){
        cout << "Liste ressource : ";
        for (auto& t : r->getTypes()) cout<< ressourceTypeToString(t)<<" ";
        cout << endl;
        cout << "Tradable : " << r->getTradable()<<endl<<endl;
    }
    //c.addChainSymbol("test");
    RessourceType vere = RessourceType::Glass;
    RessourceType pap = RessourceType::Paper;
    RessourceCost re(3,vere);
    c.getRessource(RessourceType::Glass).updatePrice(-1);
    RessourceCost re2(4,pap);
    std::vector<RessourceCost> vecre = {re, re2};
    Effect* effect = EffectFactory::instance().create("AddMoney");
    cout << "re : " << c.getRessource(RessourceType::Glass).getPrice()<<endl;
    Building b("test", vecre, {effect}, 2, BuildingType::Blue,3);
    cout << "cost : " << b.getCost(&c)<<endl;
    for (auto& t : b.getLackingRessources(&c)){
        cout << ressourceTypeToString(t);
    }
    cout<<endl;
    Game();

    string test;
    cin >> test;

    return 0;
    // // Test QT
    // QMainWindow fenetre;
    // fenetre.setWindowTitle("Ma Fenêtre Qt");
    // fenetre.setGeometry(100, 100, 400, 200);
    // QPushButton *bouton = new QPushButton("Cliquez-moi", &fenetre);
    // bouton->setGeometry(150, 80, 100, 30);
    // QObject::connect(bouton, &QPushButton::clicked, &fenetre, &QMainWindow::close);

    // Affichage de la fenêtre
    // fenetre.show();

    // SevenWonderUI ui;
    // ui.show();

    // // Exécution de la boucle d'événements
    // return app.exec();
}   
    














