#ifndef TRACK_LOADER_HPP
#define TRACK_LOADER_HPP

#include <glm/glm.hpp>
#include <vector>

class TrackLoader {
	public:
		struct SectionRect {
			glm::vec3 top_left;
			glm::vec3 top_right;
			glm::vec3 bottom_left;
			glm::vec3 bottom_right;
		};

		TrackLoader(std::vector<glm::vec3> key_points, unsigned int detail, float width, float height);

		const SectionRect& getSectionRect(unsigned int i) const {
			return _section_rects[i % _section_rects.size()];
		}

		unsigned int numSectionRects() const {
			return _section_rects.size();
		}

		glm::vec3 getPoint(unsigned int i) const {
			return _points[i % _points.size()];
		}

	private:
		const float _width;
		const float _height;

		std::vector<glm::vec3> _points;
		std::vector<SectionRect> _section_rects;

		SectionRect generateSectionRect(unsigned int i) const;
};

#endif
