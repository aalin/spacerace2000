#ifndef TRACK_ANGLES_HPP
#define TRACK_ANGLES_HPP

#include <glm/glm.hpp>
#include <vector>

class TrackAngles {
	public:
		TrackAngles(const std::vector<glm::vec3>& _points);

		float angleAt(int i) const {
			return loopAccess(_angles, i);
		}

		float smoothAngleAt(int i) const {
			return loopAccess(_smooth_angles, i);
		}

	private:
		std::vector<float> _angles;
		std::vector<float> _smooth_angles;

		float calculateSmoothAngle(int i) const;

		template<typename T>
		T loopAccess(const std::vector<T> v, signed int i) const {
			while(i < 0)
				i += v.size();

			return v.at(i % v.size());
		}
};

#endif
