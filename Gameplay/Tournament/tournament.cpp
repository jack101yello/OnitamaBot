#include "tournament.h"

// Create a new tournament with all new players
Tournament::Tournament(long unsigned int number_combatants) {
    scoreboard.clear();
    for(long unsigned int i = 0; i < number_combatants; i++) {
        scoreboard.push_back(new MatrixBot(i));
    }
}

Tournament::~Tournament() {
    scoreboard.clear();
}

// Sort all of the players according to ability
void Tournament::play_round(SDL_Renderer* renderer) {
    printf("Commencing a round of the tournamnet.\n");
    std::sort(scoreboard.begin(), scoreboard.end(), [renderer](Player* p1, Player* p2) {
        Game g(p1, p2, 150, renderer); // Create new game
        Player* winner = g.play_game(); // Play the game to determine the winner
        if(winner -> get_index() == p1 -> get_index()) {
            return true; // Player 1 won!
        }
        return false; // Player 2 won!
    });
    printf("The results:\n");
    for(long unsigned int i = 0; i < scoreboard.size(); i++) {
        printf("%d. Player %d\n", (int)(i+1), scoreboard.at(i) -> get_index());
    }
}

// Remove the players who placed in the bottom half
void Tournament::cull_losers() {
    printf("Culling losers.\n");
    for(int i = 0; i < scoreboard.size()/2; i++) {
        scoreboard.pop_back();
    }
}

// All of the players remaining on the scoreboard reproduce
void Tournament::repopulate_scoreboard() {
    printf("Repopulating scoreboard.\n");
    for(MatrixBot* b : scoreboard) {
        scoreboard.push_back(b -> produce_offspring());
    }

    for(long unsigned int i = 0; i < scoreboard.size(); i++) {
        scoreboard.at(i) -> set_index(i); // Re-index everyone for future play
    }

    // Save top player's score
    const std::string filename = "current_best.dat";
    scoreboard.at(0) -> save_data(filename);
}