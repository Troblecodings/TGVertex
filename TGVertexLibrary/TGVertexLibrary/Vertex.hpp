#pragma once

#include "stdbase.hpp"

struct Vertex {
	float pos[3];
	float color[4];
	float uv[2];
	uint8_t color_only;
};