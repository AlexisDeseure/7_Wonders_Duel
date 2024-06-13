#ifndef GAME_H
#define GAME_H


#include "qtmetamacros.h"
#define GAME_PARAMETERS_PATH "../../data/game_parameters.json"
#include <QtCore>
#include <QObject>
#include "instanciator.h"
#include <string>
#include <vector>
#include <exception>
#include "StartMenu.h"

class DeckPile;
class Board;
class Player;
enum class AiLevel;
class Building;

class GameException : public QObject ,public std::exception{
Q_OBJECT
private:
    std::string message;

public:
    GameException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class Game{
    private:
        int age;
        unsigned int turn;
        Board* board;
        Player* players[2];
        bool isReplaying;
        DeckPile* deck;
        Player* winner;
        bool isTerminal;
        StartMenu* startmenu;
    public:
        bool endTurn();
        bool checkMilitaryVictory() const;
        bool checkScientificVictory() const;
        bool updateConflictPawn();
        void processEquality();
        void advanceAge();
        void startGame();
        void replay();
        void selectWondersPhase();
        void endGame();
        void calculateWinner();
        void invertTurnPlayer();
        void randomPlayerStart();
        Player& getTurnPlayer() const { return *players[0]; };
        Player& getOtherPlayer() const { return *players[1]; };
        Board& getBoard() {return *board;}
        DeckPile& getDeck() {return *deck;}
        bool playAge();
        void playTurn();
        void startMenu();
        void displayplayerChoice(int nb_joueur);
        void displayAiLevelChoice();
        AiLevel aiOptions(Player& player);
        int getNumberOfVictoryPointsBlue(Player& player);
        void chooseWhoStartsAge(Player& player);
        Game();
        ~Game();

        // UI SPECIFIC


    public slots:

    signals:


};

int selectRandomInteger(int min = 0, int max = 1);
int getIntInput();
std::string getStrInput();
#endif
