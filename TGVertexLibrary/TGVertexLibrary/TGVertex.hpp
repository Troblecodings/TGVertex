#pragma once

#include "stdbase.hpp"
#include "Vertex.hpp"

#ifdef DEBUG
#define OUT_LV_DEBUG(text) std::cout << "[DEBUG]:" << text << std::endl
#else
#define OUT_LV_DEBUG(text)
#endif // DEBUG

#define READ_LINE(buf, count) fread(buf, sizeof(float), count, file);

#define WRITE_LINE(buf, count) fwrite(buf, sizeof(float), count, file);

#ifdef DEBUG
READ_AND_ADD(size_per_vertex, append) if (length % size_per_vertex != 0) {\
	OUT_LV_DEBUG("Wrong length of file (" << length << ") for header size per vertex (" << size_per_vertex << ")");\
	return;\
}\
for (size_t i = 0; i < length / (size_t)(size_per_vertex); i++)\
{\
Vertex* vert = v_file->addVertex(); \
READ_LINE(vert->pos, 3); \
append\
}
#else
#define READ_AND_ADD(size_per_vertex, append) for (size_t i = 0; i < (size_t) (length / size_per_vertex); i++)\
{\
Vertex* vert = v_file->addVertex();\
READ_LINE(vert->pos, 3);\
append\
}
#endif // DEBUG

#define WRITE_AND_ADD(append) for(Vertex vertex : v_file->vertex_list)\
{\
WRITE_LINE(vertex.pos, 3);\
append\
}

struct TGVertexFile {
	uint8_t header;
	std::vector<Vertex> vertex_list = {};

	bool hasColor();
	bool hasUV();

	Vertex* addVertex();
};

void load_tgvertex_file(char* name, TGVertexFile* v_file);