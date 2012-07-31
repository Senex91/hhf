#ifndef GameRenderer_H
#define GameRenderer_H

#include <string>

#include "GameState.h"
/**
 * @brief GameRenderer renders the game as received by the server.
 */
class GameRenderer {
public:
	GameRenderer();
	~GameRenderer();

	void renderNextState(GameState const& );
	
private:

};
#endif
