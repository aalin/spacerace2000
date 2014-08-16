#ifndef TRACK_ANGLES_HPP
#define TRACK_ANGLES_HPP

#include <glm/glm.hpp>
#include <vector>

class TrackAngles {
	public:
		TrackAngles(const std::vector<glm::vec3>& _points);

		float angleAt(int i) const {
			while(i < 0)
				i += _angles.size();

			float angle = _angles.at(i % _angles.size());

			// if(angle < 30.0) return -30.0;
			// if(angle > 30.0) return 30.0;

			return angle;
		}

		float smoothAngleAt(int i) const;

	private:
		std::vector<float> _angles;
};

#endif
