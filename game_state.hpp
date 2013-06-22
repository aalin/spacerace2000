#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

class GameState {
	public:
		GameState();
		virtual ~GameState();
		virtual void setup() = 0;
		virtual void pause() = 0;
		virtual void update(double s) = 0;
		virtual void draw() = 0;
};

#endif
