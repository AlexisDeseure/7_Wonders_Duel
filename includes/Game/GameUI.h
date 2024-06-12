#ifndef GAMEUI_H
#define GAMEUI_H


#include "qtmetamacros.h"
#define GAME_PARAMETERS_PATH "../../data/game_parameters.json"

#include "instanciator.h"
#include <string>
#include <vector>
#include <exception>


class DeckPile;
class Board;
class Player;
enum class AiLevel;
class Building;

class GameUIException : public std::exception {
private:
    std::string message;

public:
    GameUIException(const std::string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class GameUI{
    private:
        int age;
        unsigned int turn;
        Board* board;
        Player* players[2];
        bool isReplaying;
        DeckPile* deck;
        Player* winner;

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
        GameUI();
        ~GameUI();
};

int selectRandomInteger(int min = 0, int max = 1);
int getIntInput();
std::string getStrInput();
#endif