#ifndef SPLINES_HPP
#define SPLINES_HPP

#include <glm/glm.hpp>
#include <vector>

class Splines {
	public:
		Splines(std::vector<glm::vec3> key_points) : _key_points(key_points) { }

		std::vector<glm::vec3> generate(unsigned int detail) const;

	private:
		const std::vector<glm::vec3> _key_points;

		glm::vec3 keyPoint(signed int i) const {
			while(i < 0)
				i += _key_points.size();
			return _key_points[i % _key_points.size()];
		}
};

#endif
