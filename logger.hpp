#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <initializer_list>
#include <string>
#include <iostream>
#include <sstream>

class Logger {
	public:
		Logger(unsigned int color, std::ostream& out = std::cout) : _color(color), _out(out) {}

		~Logger() {
			_out << "\e[38;5;" << _color << "m";
			_out << _stream.rdbuf();
			_out << "\e[0m";
			_out << std::endl;
			_out.flush();
		}

		template <class T>
			Logger& operator<<(const T& thing) {
				_stream << thing;
				return *this;
			}

	private:
		unsigned int _color;
		std::stringstream _stream;
		std::ostream& _out;
};

#define LOG_ERROR Logger(1, std::cout)
#define LOG_INFO Logger(2, std::cout)
#define LOG_WARN Logger(3, std::cout)
#define LOG_DEBUG Logger(4, std::cout)

#endif
