#ifndef RACER_MODEL_HPP
#define RACER_MODEL_HPP

#include "vertex_array.hpp"
#include "vertex.hpp"
#include <vector>

class RacerModel {
	public:
		RacerModel();
		~RacerModel();

		void draw() const;

	private:
		std::vector<Vertex> generateVertices() const;
		VertexArray* _vertex_array;
};

#endif
