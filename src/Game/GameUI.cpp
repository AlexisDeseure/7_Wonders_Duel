#include "GameUI.h"
#include "Board.h"
#include "Player.h"
#include "Instanciator.h"
#include "DeckPile.h"
#include "ConflictPawn.h"
#include "GameParameters.h"
#include "City.h"
#include "Effect.h"
#include "AddVictoryPoint.h"
#include <random>
#include <iostream>
#include <algorithm>

GameUI::GameUI() : age(0), turn(0), isReplaying(false), winner(nullptr) {
    try {
        Instanciator* inst = Instanciator::getInstanciator();
        int length = inst->getGameParameters().getLengthConflictPawnBoard();
        board = new Board(length);
        int nb_b = inst->getGameParameters().getNumberBuildingPerAge();
        int nb_pt = inst->getGameParameters().getNumberProgressTokenBoard();
        int nb_w = inst->getGameParameters().getNumberSelectedWonders();
        deck = new DeckPile(nb_b, nb_pt, nb_w);
        players[0] = new Player(inst->getGameParameters().getCoinsStart());
        players[1] = new Player(inst->getGameParameters().getCoinsStart());
        startGame();
    } catch (const std::exception& e) {
        std::cerr << "Error initializing game: " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

Game::~Game() {
    try {
        delete board;
        delete players[0];
        delete players[1];
        delete deck;
        std::cout << R"(
  __  __               _       _ _                  _          _                    _
 |  \/  |             (_)     | ( )                (_)        (_)              /   | |
 | \  / | ___ _ __ ___ _    __| |/  __ ___   _____  _ _ __     _  ___  _   _  ___  | |
 | |\/| |/ _ \ '__/ __| |  / _` |  / _` \ \ / / _ \| | '__|   | |/ _ \| | | |/ _ \ | |
 | |  | |  __/ | | (__| | | (_| | | (_| |\ V / (_) | | |      | | (_) | |_| |  __/ |_|
 |_|  |_|\___|_|  \___|_|  \__,_|  \__,_| \_/ \___/|_|_|      | |\___/ \__,_|\___| (_)
                                                             _/ |
                                                            |__/
)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error cleaning up game: " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::startMenu(){
    try {
        AiLevel level;
        int choice;

        std::cout << std::endl << "*********************** Choix des joueurs *********************** " << std::endl << std::endl;

        for (int i = 0; i < 2; i++) {
            displayplayerChoice(i + 1);
            choice = players[i]->getPlayerChoice(2);
            switch (choice) {
            case 1:
                std::cout << "Entrez le nom du joueur : " << std::endl;
                players[i]->setName(getStrInput());
                break;
            case 2:
                players[i]->setAI(true);
                players[i]->setAiLevel(AiLevel::EASY);
                players[i]->setName("BOT"); // + AiLeveltoString(level));
                break;
            }
        }

        if (players[0]->getName() == players[1]->getName()) {
            players[0]->setName(players[0]->getName() + " (1)");
            players[1]->setName(players[1]->getName() + " (2)");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in startMenu(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

AiLevel GameUI::aiOptions(Player& player) {
    try {
        displayAiLevelChoice();
        int choice = player.getPlayerChoice(3);
        player.setAI(true);
        switch (choice) {
        case 1:
            return AiLevel::EASY;
        case 2:
            return AiLevel::MEDIUM;
        default:
            return AiLevel::HARD;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in aiOptions(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::displayAiLevelChoice() {
    try {
        std::cout << "Choisissez le niveau de l'IA : " << std::endl;
        std::cout << "\t1. Facile" << std::endl;
        std::cout << "\t2. Moyen" << std::endl;
        std::cout << "\t3. Difficile" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in displayAiLevelChoice(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::displayplayerChoice(int nb_joueur) {
    try {
        std::cout << "Choisissez le type du joueur " << nb_joueur << std::endl;
        std::cout << "\t1. Humain" << std::endl;
        std::cout << "\t2. IA" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in displayplayerChoice(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::startGame() {
    try {
        std::cout << R"(
_________   __      __                  .___                    ________                .__
\______  \ /  \    /  \____   ____    __| _/___________  ______ \______ \  __ __   ____ |  |
    /    / \   \/\/   /  _ \ /    \  / __ |/ __ \_  __ \/  ___/  |    |  \|  |  \_/ __ \|  |
   /    /   \        (  <_> )   |  \/ /_/ \  ___/|  | \/\___ \   |    `   \  |  /\  ___/|  |__
  /____/     \__/\  / \____/|___|  /\____ |\___  >__|  /____  > /_______  /____/  \___  >____/
                  \/             \/      \/    \/           \/          \/            \/
    )" << std::endl;

        startMenu();
        std::cout << "Nom des joueurs : " << players[0]->getName() << " et " << players[1]->getName() << std::endl;
        selectWondersPhase();
        while (age < Instanciator::getInstanciator()->getGameParameters().getNumberAge()) {
            if (playAge()) {
                break;
            }
        }
        endGame();
    } catch (const std::exception& e) {
        std::cerr << "Error in startGame(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::chooseWhoStartsAge(Player& player) {
    try {
        std::cout << player.getName() << ", choisissez qui commence l'âge : " << std::endl;
        std::cout << "\t1 : " << players[0]->getName() << std::endl;
        std::cout << "\t2 : " << players[1]->getName() << std::endl;
        std::cout << "\t3 : Aléatoire" << std::endl;
        int choice = player.getPlayerChoice(3);
        switch (choice) {
        case 1:
            if (&getTurnPlayer() == players[0]) invertTurnPlayer();
            std::cout << getOtherPlayer().getName() << " commencera !" << std::endl;
            break;
        case 2:
            if (&getTurnPlayer() == players[1]) invertTurnPlayer();
            std::cout << getOtherPlayer().getName() << " commencera !" << std::endl;
            break;
        default:
            randomPlayerStart();
            break;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in chooseWhoStartsAge(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

bool GameUI::playAge() {
    try {
        advanceAge();
        std::cout << "Age " << age << " en cours" << std::endl;

        if (board->getConflictPawn().getPosition() < 0) {
            chooseWhoStartsAge(getTurnPlayer());
        } else if (board->getConflictPawn().getPosition() > 0) {
            chooseWhoStartsAge(getOtherPlayer());
        } else {
            randomPlayerStart();
        }

        while (!board->deckIsEmpty()) {
            playTurn();

            if (endTurn()) {
                return true;
            }
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in playAge(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::replay() {
    try {
        if (!isReplaying) isReplaying = true;
    } catch (const std::exception& e) {
        std::cerr << "Error in replay(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::playTurn() {
    try {
        turn++;
        if (!isReplaying) invertTurnPlayer();
        isReplaying = false;
        std::cout << std::endl << "*********************** Tour numéro  " << turn << " - Joueur " << getTurnPlayer().getName() << " *********************** " << std::endl << std::endl;
        getTurnPlayer().play(*this);
    } catch (const std::exception& e) {
        std::cerr << "Error in playTurn(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::selectWondersPhase() {
    try {
        std::cout << std::endl << "*********************** Sélection des Merveilles ***********************" << std::endl << std::endl;
        randomPlayerStart();
        invertTurnPlayer();

        std::vector<Wonder*> allWonders = deck->getAllWonders();
        std::shuffle(allWonders.begin(), allWonders.end(), std::mt19937(std::random_device()()));

        auto selectionPhase = [&](Player* firstPlayer, Player* secondPlayer) {
            // fonction pour la phase de sélection des wonders
            std::vector<Wonder*> wondersToSelect;
            wondersToSelect.reserve(4); // Réservation de la mémoire pour les 4 wonders pour éviter les réallocations

            for (int i = 0; i < 4; i++) {
                wondersToSelect.push_back(allWonders.back());
                allWonders.pop_back();
            }

            std::cout << "Merveilles disponibles : "<<std::endl;
            for (const auto& wonder : wondersToSelect) {
                std::cout <<"\t- "<< wonder->getName() << std::endl;
            }
            std::cout << std::endl;

            firstPlayer->chooseWonder(wondersToSelect);
            secondPlayer->chooseWonder(wondersToSelect);
            secondPlayer->chooseWonder(wondersToSelect);
            firstPlayer->chooseWonder(wondersToSelect);
        };

        selectionPhase(&getTurnPlayer(), &getOtherPlayer());
        selectionPhase(&getOtherPlayer(), &getTurnPlayer());

        std::cout << "Phase de sélection des Merveilles terminée" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in selectWondersPhase(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

bool GameUI::endTurn() {
    try {
        if (updateConflictPawn()) {
            std::cout << "Victoire militaire !" << std::endl;
            if (board->getConflictPawn().getPosition() >= 0) {
                winner = &getTurnPlayer();
            } else {
                winner = &getOtherPlayer();
            }
            return true;
        }
        if (checkScientificVictory()) {
            std::cout << "Victoire scientifique !" << std::endl;
            winner = &getTurnPlayer();
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in endTurn(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

bool GameUI::updateConflictPawn() {
    try {
        ConflictPawn& conflict = board->getConflictPawn();
        int totalShields = getTurnPlayer().getShields() - getOtherPlayer().getShields();
        conflict.move(totalShields);
        if (checkMilitaryVictory()) {
            return true;
        }
        for (auto& step : Instanciator::getInstanciator()->getGameParameters().getConflictPawnBoard()) {
            if (conflict.getPosition() >= step.number && step.effect != nullptr) {
                step.effect->apply(*this);
                step.effect = nullptr;
            }
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in updateConflictPawn(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

bool GameUI::checkMilitaryVictory() const {
    try {
        return board->getConflictPawn().isMilitaryVictory();
    } catch (const std::exception& e) {
        std::cerr << "Error in checkMilitaryVictory(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

bool GameUI::checkScientificVictory() const {
    try {
        return getTurnPlayer().getCity().checkScientificVictory();
    } catch (const std::exception& e) {
        std::cerr << "Error in checkScientificVictory(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::advanceAge() {
    try {
        age++;
        std::cout << std::endl << "*********************** Age " << age << " *********************** " << std::endl << std::endl;

        deck->advanceAge(age);
        board->advanceAge(age, deck->getBuildings());
    } catch (const std::exception& e) {
        std::cerr << "Error in advanceAge(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::endGame() {
    try {
        std::cout << std::endl << "*********************** Fin du jeu *********************** " << std::endl << std::endl;

        if (winner == nullptr) {
            calculateWinner();
        }
        std::cout << "Calcul du gagnant" << std::endl;
        if (winner == nullptr) {
            std::cout << "Egalité !" << std::endl;
        } else {
            std::cout << "Bravo à " << winner->getName() << " qui remporte la victoire !" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in endGame(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::calculateWinner() {
    try {
        int position = board->getConflictPawn().getPosition();
        int victory_points_conflict = 0;
        for (auto& element : Instanciator::getInstanciator()->getGameParameters().getConflictPawnBoard()) {
            if (std::abs(position) >= element.number) {
                victory_points_conflict = element.victory_points;
            }
        }
        if (position > 0) {
            getTurnPlayer().getCity().addVictoryPoints(victory_points_conflict);
        } else {
            getOtherPlayer().getCity().addVictoryPoints(victory_points_conflict);
        }
        int score1 = getTurnPlayer().getScore(*this);
        invertTurnPlayer();
        int score2 = getTurnPlayer().getScore(*this);
        if (score1 > score2) {
            winner = &getOtherPlayer();
        } else if (score1 < score2) {
            winner = &getTurnPlayer();
        } else {
            processEquality();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in calculateWinner(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::processEquality() {
    try {
        int score1 = getNumberOfVictoryPointsBlue(getTurnPlayer());
        int score2 = getNumberOfVictoryPointsBlue(getOtherPlayer());
        if (score1 > score2) {
            winner = &getTurnPlayer();
        } else if (score1 < score2) {
            winner = &getOtherPlayer();
        } else {
            winner = nullptr;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in processEquality(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

int GameUI::getNumberOfVictoryPointsBlue(Player& player) {
    try {
        int number_victory_points_blue = 0;
        for (auto& building : player.getCity().getBuildings()) {
            if (building->getType() == BuildingType::Blue) {
                for (auto& effect : building->getEffects()) {
                    if (dynamic_cast<AddVictoryPoint*>(effect) != nullptr) {
                        number_victory_points_blue += dynamic_cast<AddVictoryPoint*>(effect)->getQuantity();
                    }
                }
            }
        }
        return number_victory_points_blue;
    } catch (const std::exception& e) {
        std::cerr << "Error in getNumberOfVictoryPointsBlue(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::invertTurnPlayer() {
    try {
        std::swap(players[0], players[1]);
    } catch (const std::exception& e) {
        std::cerr << "Error in invertTurnPlayer(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

void GameUI::randomPlayerStart() {
    try {
        if (selectRandomInteger() == 1) {
            invertTurnPlayer();
        }
        std::cout << getOtherPlayer().getName() << " commencera !" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in randomPlayerStart(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

int selectRandomInteger(int min , int max ) {
    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    } catch (const std::exception& e) {
        std::cerr << "Error in selectRandomInteger(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
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

std::string getStrInput() {
    try {
        std::string input;
        std::cin >> input;
        return input;
    } catch (const std::exception& e) {
        std::cerr << "Error in getStrInput(): " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}