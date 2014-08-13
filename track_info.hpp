#ifndef TRACK_INFO_HPP
#define TRACK_INFO_HPP

#include <glm/glm.hpp>
#include <vector>

class TrackInfo {
	class PointInfo {
		public:
			unsigned int index;
			float distance;
			float distance_to_next;
			float angle;

			glm::vec3 center;
			glm::vec3 left0;
			glm::vec3 right0;
			glm::vec3 left1;
			glm::vec3 right1;

			bool hasPoint(glm::vec3 point) const {
				return
					pointInTriangle(point, left0, left1, right0) ||
					pointInTriangle(point, right0, left1, right1);
			};

		private:
			bool pointInTriangle(glm::vec3 p, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) const {
				// Barycentric coordinates, wtf.
				// http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle
				float a = 0.5 * (-p1.y * p2.x + p0.y * (-p1.x + p2.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y);
				int sign = a < 0 ? -1 : 1;
				float s = (p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y) * sign;
				float t = (p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y) * sign;
				return s > 0 && t > 0 && (s + t) < 2 * a * sign;
			}
	};

	struct LeftRight {
		glm::vec3 left;
		glm::vec3 right;
	};

	public:
		TrackInfo(const std::vector<glm::vec3>& key_points, float width);

		glm::vec3 positionAt(float distance) const;
		float distanceNear(float distance, glm::vec3 position) const;

	private:
		std::vector<PointInfo> _point_information;
		float _length;
		const float _width;

		unsigned int indexAt(float distance) const;
		const PointInfo& getPointInfo(unsigned int i) const {
			return _point_information[i % _point_information.size()];
		}
};

#endif
