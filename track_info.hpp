#ifndef TRACK_INFO_HPP
#define TRACK_INFO_HPP

#include <glm/glm.hpp>
#include <vector>

class TrackInfo {
	class PointInfo {
		struct Triangle {
			glm::vec3 p0, p1, p2;
		};

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
				return pointInTriangle(point, firstTriangle()) || pointInTriangle(point, secondTriangle());
			};

			float heightAt(glm::vec3 point) const {
				return heightInTriangleAt(point, firstTriangle()) + heightInTriangleAt(point, secondTriangle());
			}

		private:
			Triangle firstTriangle() const {
				return Triangle{left0, left1, right0};
			}
			Triangle secondTriangle() const {
				return Triangle{right0, left1, right1};
			}

			bool pointInTriangle(glm::vec3 p, Triangle asd) const {
				// Barycentric coordinates, wtf.
				// http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle
				float a = 0.5 * (-asd.p1.y * asd.p2.x + asd.p0.y * (-asd.p1.x + asd.p2.x) + asd.p0.x * (asd.p1.y - asd.p2.y) + asd.p1.x * asd.p2.y);
				int sign = a < 0 ? -1 : 1;
				float s = (asd.p0.y * asd.p2.x - asd.p0.x * asd.p2.y + (asd.p2.y - asd.p0.y) * p.x + (asd.p0.x - asd.p2.x) * p.y) * sign;
				float t = (asd.p0.x * asd.p1.y - asd.p0.y * asd.p1.x + (asd.p0.y - asd.p1.y) * p.x + (asd.p1.x - asd.p0.x) * p.y) * sign;
				return s > 0 && t > 0 && (s + t) < 2 * a * sign;
			}

			float heightInTriangleAt(glm::vec3 p, Triangle t) const {
				if(!pointInTriangle(p, t))
					return 0.0;

				const float d0 = glm::distance(glm::vec2(p), glm::vec2(t.p0));
				const float d1 = glm::distance(glm::vec2(p), glm::vec2(t.p1));
				const float d2 = glm::distance(glm::vec2(p), glm::vec2(t.p2));

				const float total = d0 + d1 + d2;
				const glm::vec3 hello = glm::normalize(glm::vec3(d0, d1, d2) / total);

				return hello.x * t.p0.z + hello.y * t.p1.z + hello.z + t.p1.z;
			}
	};

	struct LeftRight {
		glm::vec3 left;
		glm::vec3 right;
	};

	public:
		TrackInfo(const std::vector<glm::vec3>& key_points, float width);

		glm::vec3 betterPositionAt(float distance, glm::vec3 position) const;
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

		std::vector<PointInfo> pointInfosAroundPosition(glm::vec3 position, float distance) const;
};

#endif
