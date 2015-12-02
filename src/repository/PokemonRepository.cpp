//
// Created by Martin on 30. 11. 2015.
//

#include "src/repository/PokemonRepository.hpp"

PokemonRepository::PokemonRepository() {

}

PokemonPtr PokemonRepository::findPokemon(unsigned short id) {
    for (auto pokemonLoop : this->pokemons) {
        if (pokemonLoop->id == id)
            return pokemonLoop;
    }

    return nullptr;
}

void PokemonRepository::add(PokemonPtr pokemon) {
    this->pokemons.push_back(pokemon);
}
