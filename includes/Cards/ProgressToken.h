//Crée par Mateo
#ifndef PROGRESSTOKEN_H
#define PROGRESSTOKEN_H

#include "Card.h"
#include "City/City.h"

class ProgressToken : public Card{
private:
    bool on_the_board;
    const City* city;
    const Board* board;
public:
    ProgressToken() {
        on_the_board = false;
    };
    bool otb() const{ return on_the_board;};

    void status_true(){on_the_board=true;};
    void status_false(){on_the_board = false;}
};


#endif //PROGRESSTOKEN_H