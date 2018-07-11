#pragma once

#include "stdbase.hpp"
#include "Vertex.hpp"

#define READ_LINE(buf, count) fread(buf, sizeof(float), count, file);

#define WRITE_LINE(buf, count) fwrite(buf, sizeof(float), count, file);

#ifdef DEBUG
#define READ_AND_ADD(append)for (size_t i = 0; i < length; i++)\
{\
Vertex* vert = v_file->addVertex(); \
READ_LINE(vert->pos, 3); \
append\
}
#else
#define READ_AND_ADD(append) for (size_t i = 0; i < length; i++)\
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
	void setHasColor(bool has);
	void setHasUV(bool has);

	Vertex* addVertex();
};

void load_tgvertex_file(char* name, TGVertexFile* v_file);

void save_tgvertex_file(char* name, TGVertexFile* v_file);