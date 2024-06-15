#include "cardwidget.h"
#include "Card.h"
#include <QVBoxLayout>

CardWidget::CardWidget(QWidget *parent) : QWidget(parent),  clickable(false) //for testing without cards, will be removed
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // nameLabel = new QLabel("Card", this); //QString::fromStdString(getCard()->getName())
    // effectLabel = new QLabel("Effect", this);
    selectButton = new QPushButton(this);
    selectButton->setIcon(QIcon("../../../data/image/cards/academy.jpg"));
    selectButton->setIconSize(QSize(100, 159));

    selectLabel = new QLabel("Sélectionner", this);
    selectLabel->setAlignment(Qt::AlignCenter);
    opacityEffect = new QGraphicsOpacityEffect(this);
    selectLabel->setGraphicsEffect(opacityEffect);
    selectLabel->setVisible(false);

    this->setStyleSheet("background-color: blue; color: white;");

    layout->addWidget(selectButton);
    layout->addWidget(selectLabel);

    connect(selectButton, SIGNAL(clicked()), this, SLOT(cardClicked()));
}


CardWidget::CardWidget(DeckElement* carte,QWidget *parent) : card(carte), QWidget(parent),  clickable(true) //final initialiser
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    nameLabel = new QLabel("Card", this); //QString::fromStdString(getCard()->getName())
    effectLabel = new QLabel("Effect", this);
    selectButton = new QPushButton(this);
    selectButton->setIcon(QIcon("../../../data/image/cards/academy.jpg"));
    selectButton->setIconSize(QSize(100, 159));

    selectLabel = new QLabel("Sélectionner", this);
    selectLabel->setAlignment(Qt::AlignCenter);
    opacityEffect = new QGraphicsOpacityEffect(this);
    selectLabel->setGraphicsEffect(opacityEffect);
    selectLabel->setVisible(false);

    this->setStyleSheet("background-color: blue; color: white;");

    layout->addWidget(selectButton);
    layout->addWidget(selectLabel);

    connect(selectButton, SIGNAL(clicked()), this, SLOT(cardClicked()));
}

void CardWidget::enterEvent(QEnterEvent *event)
{
    // Afficher le label avec une animation de transparence lorsque le curseur entre
    selectLabel->setVisible(true);
    opacityEffect->setOpacity(0.7); // Définir l'opacité souhaitée
}

void CardWidget::leaveEvent(QEvent *event)
{
    // Cacher le label lorsqu'on quitte le survol
    selectLabel->setVisible(false);
}

void CardWidget::acheter(){
    this->close(); //retire le widget de la fenêtre
    emit sendAchat(card); //envoie signal
    delete this; //efface le widget
}

void CardWidget::defausser(){
    this->close();
    emit sendDefausse(card);
    delete this;
}

void CardWidget::cardClicked()
{
    if (clickable){
        //afficher un menu
        selectWidget* selectMenu = new selectWidget();
        selectMenu->show();
        connect(selectMenu,SIGNAL(acheterPressed()),this,SLOT(acheter()));
        connect(selectMenu,SIGNAL(defausserPressed()),this,SLOT(defausser()));
    }
}


// void CardWidget::cardClicked(){
//     if (getClickable()){
//         QMessageBox::information(this, "Card Clicked", "You clicked the Card!");
//     }
// }



