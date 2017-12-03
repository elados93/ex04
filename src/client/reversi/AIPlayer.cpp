
// Created by Elad Aharon & Shahar Palmor on 14/11/17.
// ID: 311200786 307929927
//

#include "AIPlayer.h"
#include "ConsolePrinter.h"
#include "HumanPlayer.h"
#include <algorithm>

using namespace std;

AIPlayer::AIPlayer(char s, GameRules &gameRules1) : gameRules(gameRules1), symbol(s) {}

Point AIPlayer::getMove(GameState &gameState) {
    GameState demoGame(gameState);
    vector<Point*> AIVector = gameState.vec2;

    if (AIVector.empty())
        return Point(-1, -1); // return (-1, -1) to show AIPlayer has no moves.

    int scores[AIVector.size()]; // Here will be all the scores of each possible move of the AIPlayer.

    // Iterates over all the possible moves of AIPlayer.
    for (unsigned int i = 0; i < AIVector.size(); ++i) {
        gameRules.makeMove(demoGame, *AIVector.at(i), PLAYER_2); // The computer makes his move on the demo board.

        gameRules.makePossibleMoves(demoGame, PLAYER_1);

        scores[i] = playDemo(demoGame);

        demoGame = gameState; // Initialize the game as it was before testing the point.
    }

    int scoreMin = *min_element(scores, scores + AIVector.size()); // Get the min score from all the scores.
    unsigned int pointToReturnIndex = 0;
    //geting the point represented by the index of the play demo function.
    for (unsigned int j = 0; j < AIVector.size(); ++j)
        if (scores[j] == scoreMin) {
            pointToReturnIndex = j;
            break;
        }


    Point p(*AIVector.at(pointToReturnIndex));
    return p;
}

int AIPlayer::playDemo(GameState &demoGame) {
    GameState demoComputerGame(demoGame);
    gameRules.makePossibleMoves(demoGame, PLAYER_1);
    vector<Point*> *humanVector = gameRules.getPossibleMoves(demoGame, PLAYER_1);// gets all the possible moves of the human player
    //after one of the AI players options.

    int scores[humanVector->size()];

    for (unsigned int i = 0; i < humanVector->size(); ++i) {
        gameRules.makeMove(demoComputerGame, *humanVector->at(i) , PLAYER_1); // Make a possible move of the human player.

        Point counters = demoComputerGame.board->countOwner(); // Counts the players differences in the game.
        scores[i] = counters.getX() - counters.getY(); // Store that value in scores.
        demoComputerGame = demoGame; // Initialize back to the game state before the human move.
    }
    int scoreLen = (sizeof(scores) / sizeof(int));
    int scoreMax = *max_element(scores, scores + scoreLen); // Get the max score from all the scores.
    return scoreMax;
}

char AIPlayer::getSymbol() const {
    return symbol;
}
