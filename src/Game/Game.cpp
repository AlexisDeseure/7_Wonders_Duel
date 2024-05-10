#include "../../includes/Game/Game.h"
#include "../../includes/BoardManager/Board.h"
#include "../../includes/Game/Player.h"


Game::Game() : age(0), board(*new Board()){
    players[0] = new Player();
    players[1] = new Player();

    std::cout << "Game created" << std::endl;
    startGame();
}

Game::~Game() {
    delete &board;
    delete players[0];
    delete players[1];
    std::cout << "Game finished" << std::endl;
}

void Game::startMenu(){
    AiLevel level;
    int choice;

    for (int i = 0; i < NB_PLAYERS; i++) {
        choice = 0;
        do{
            displayplayerChoice(i+1);
            switch (choice = getIntInput()) {
                case 1:
                    players[i]->setAI(false);
                    std::cout << "Entrez le nom du joueur : "<< std::endl;
                    players[i]->setName(getStrInput());
                    break;

                case 2:
                    players[i]->setAI(true);
                    level = aiOptions();
                    players[i]->setAiLevel(level);
                    players[i]->setName("BOT " + AiLeveltoString(level));
                    break;

                default:
                    std::cout << "Choix invalide" << std::endl;
                    break;
            }
        }while(choice < 1 || choice > 2);
    }
}

AiLevel Game::aiOptions() {
    AiLevel level;
    int choice = 0;
    do {
        displayAiLevelChoice();
        switch (choice = getIntInput()) {
            case 1:
                level = AiLevel::EASY;
                break;

            case 2:
                level = AiLevel::MEDIUM;
                break;

            case 3:
                level = AiLevel::HARD;
                break;

            default:
                std::cout << "Choix invalide" << std::endl;
                break;
        }
    }while (choice < 1 || choice > 3);

    return level;
}

void Game::displayAiLevelChoice(){
    std::cout << "Choisissez le niveau de l'IA : "<< std::endl;
    std::cout << "\t1. Facile" << std::endl;
    std::cout << "\t2. Moyen" << std::endl;
    std::cout << "\t3. Difficile" << std::endl;
    std::cout << "Selection: ";
}

void Game::displayplayerChoice(int nb_joueur){
    std::cout << "Choisissez le type du joueur " << nb_joueur << std::endl;
    std::cout << "\t1. Humain" << std::endl;
    std::cout << "\t2. IA" << std::endl;
    std::cout << "Selection: ";
}

int getIntInput()
{
    /**
     * @brief Récupère l'entrée de l'utilisateur et empêche les erreurs de saisie
     *
     * @return int
     */

    int choice;
    std::string input;
    std::cin.clear();
    std::getline(std::cin, input);

    if (input.length() > 0 && std::isdigit(input[0])) {
        choice = std::stoi(input);
    } else {
        choice = -1; // Valeur invalide
    }
    std::cout << std::endl;
    return choice;
}

std::string getStrInput()
{
    /**
     * @brief Récupère l'entrée de l'utilisateur et empêche les erreurs de saisie
     *
     * @return std::string
     */

    std::string input;
    std::cin.clear();
    std::getline(std::cin, input);
    std::cout << std::endl;
    return input;
}


void Game::startGame(){
    std::cout << "Game started" << std::endl;
    startMenu();
    std::cout << "nom des joueurs : " << players[0]->getName() << " et " << players[1]->getName() << std::endl;
    randomPlayerStart();
    selectWondersPhase();
    while (age < AGE_MAX){
        playAge();
    }
    endGame();

}

void Game::playAge(){
    advanceAge();
    std::cout << "Age " << age << " en cours" << std::endl;
    // vérifier quel est le joueur mené militairement pour lui laisser qui commence l'age entre
    // les deux joueurs (lui, l'adversaire, ou aléatoirement en utilisant la méthode randomPlayerStart)
    // à faire
//    while (!board.deckIsEmpty()){
//        getTurnPlayer().play();
//    }
}

void Game::selectWondersPhase(){
    std::cout << "Phase de selection des merveilles" << std::endl;
}

void Game::advanceAge(){
    age++;
    std::cout << "Age avance" << std::endl;
}

void Game::endGame(){
    std::cout << "Calcul du gagnant" << std::endl;
    std::cout << "Game ended" << std::endl;
}

void Game::invertTurnPlayer(){
    Player &player = getTurnPlayer();
    players[0] = &getOtherPlayer();
    players[1] = &player;
}

void Game::randomPlayerStart() {
    if(selectRandomInteger() == 1){
        invertTurnPlayer();
        std::cout << "Turn inverted" << std::endl;
    }
    else {
        std::cout << "Turn not inverted" << std::endl;
    }
};

int selectRandomInteger(int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    int number = dis(gen);
    return number;
}

