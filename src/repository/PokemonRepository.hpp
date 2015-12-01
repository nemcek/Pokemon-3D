//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_POKEMONREPOSITORY_HPP
#define POKEMON3D_POKEMONREPOSITORY_HPP

#include "src/objects/Pokemon.hpp"
#include "src/repository/Repository.hpp"

class PokemonRepository : public Repository {

private:
    std::vector<Pokemon *> pokemons;

public:
    PokemonRepository();
    Pokemon *findPokemon(unsigned short id);
    void add(Pokemon *pokemon);
};

#endif //POKEMON3D_POKEMONREPOSITORY_HPP
