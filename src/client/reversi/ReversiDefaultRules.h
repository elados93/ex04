
// Created by Elad Aharon & Shahar Palmor on 03/11/17.
// ID: 311200786 307929927
//

#ifndef EX02_REVERSIDEFAULTRULES_H
#define EX02_REVERSIDEFAULTRULES_H


#include "GameRules.h"
#include "GameState.h"

class ReversiDefaultRules : public GameRules {
public:
    ReversiDefaultRules(); // Constructor.
    ~ReversiDefaultRules();// Destructor.

    /**
     * make a vector with all the possible moves of symbol.
     * @param symbol The current player.
     * @return The possible moves vector.
     */
    vector<Point*> makePossibleMoves(GameState &gameState, owner symbol);

    /**
 * Returns the possible moves of "symbol"
 * @param symbol The player.
 * @return Possible moves of symbol.
 */
    vector<Point*> getPossibleMoves(GameState &gameState, owner symbol);

    /**
     * Make a single move of "symbol" at point p.
     * @param p Given point to mark.
     * @param symbol The player who plays.
     * @return Possible outcome of the procedure.
     */
    possible_outcome makeMove(GameState &gameState, Point &p, owner symbol);

    /**
     * Check all the surrounding cell of Point p of the player symbol.
     * @param p Point to check his surrounding.
     * @param symbol The current player.
     */
    void checkSurround(GameState &gameState, Point &p, owner symbol);

    /**
     * Move along the dRow & dCol direction and look for possible moves.
     * @param p The point to begin with.
     * @param symbol The current player.
     * @param dRow The difference in row.
     * @param dCol The difference in col.
     */
    void moveAlong(GameState &gameState, Point &p ,owner symbol, int dRow, int dCol);

    /**
     * Free all the points in the vector of "symbol" player.
     * @param symbol The player to delete his vector.
     */
    void freePointsInVec(GameState &gameState, owner symbol);

private:

    /**
     * Returns true if the point is in the board.
     * @param p Point to check.
     * @return True if the point it's in the board.
     */
    bool isLegal(GameState &gameState, Point &p) const;

    /**
     * Get the specific point "point" in vector "vec".
     * @param point Point to extract from vec.
     * @param vec Given vector of Point objects.
     * @return The point in the vector.
     */
    Point* getPointFromVec(Point &point, vector<Point*> vec) const;

    /**
     * checks if a specific point is in the vector of the player with symbol that we get as a parameter.
     * @param gameState
     * @param p is the point to check.
     * @param symbol is the symbol of the current player.
     * @return true if the point is in the vector.
     */
    bool isAlreadyContains(GameState &gameState, Point &p, owner symbol);
};


#endif //EX02_REVERSIDEFAULTRULES_H
