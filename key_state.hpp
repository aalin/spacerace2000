#ifndef KEY_STATE_HPP
#define KEY_STATE_HPP

class KeyState {
	public:
		enum class State {
			UNCHANGED,
			PRESSED,
			RELEASED
		};

		KeyState() {
			_pressed = false;
			_was_pressed = false;
		};

		void update(bool pressed) {
			_was_pressed = _pressed;
			_pressed = pressed;
		}

		State getState() {
			if(_pressed == _was_pressed)
				return State::UNCHANGED;

			if(_pressed)
				return State::PRESSED;

			return State::RELEASED;
		};

	private:
		bool _pressed;
		bool _was_pressed;
};

#endif
