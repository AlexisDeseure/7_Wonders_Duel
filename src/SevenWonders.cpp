#include "Game.h"
#include "SevenWonderUI.h"
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>

#include "Ressource.h"

using namespace std;

int main(int argc, char* argv[]) {


    QApplication app(argc, argv);

    //Game();

    // // Test QT
    // QMainWindow fenetre;
    // fenetre.setWindowTitle("Ma Fenêtre Qt");
    // fenetre.setGeometry(100, 100, 400, 200);
    // QPushButton *bouton = new QPushButton("Cliquez-moi", &fenetre);
    // bouton->setGeometry(150, 80, 100, 30);
    // QObject::connect(bouton, &QPushButton::clicked, &fenetre, &QMainWindow::close);

    // // Affichage de la fenêtre
    // fenetre.show();

    SevenWonderUI ui;
    ui.show();

    // Exécution de la boucle d'événements
    return app.exec();
}   
    














