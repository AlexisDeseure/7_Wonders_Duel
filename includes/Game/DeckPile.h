#ifndef DECKPILE_H
#define DECKPILE_H

#include <vector>
#include <utility>

class Building;
class Wonder;
class ProgressToken;

class DeckPile{
private:
    std::pair<std::vector<Building*>, std::vector<Building*>> buildings;
    std::vector<Wonder*> wonders;
    std::pair<std::vector<ProgressToken*>,std::vector<ProgressToken*>> progress_tokens;
public:
    DeckPile(int nb_buildings, int nb_token, int nb_wonder);

};

#endif // DECKPILE_H