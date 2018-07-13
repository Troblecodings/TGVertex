#pragma once

#define TGV_VERSION_0_0_1 1 
#define TGV_VERSION_0_0_2 2
#define TGV_VERSION_LATEST TGV_VERSION_0_0_2

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
Vertex* vert = v_file->addVertex(pylogen);\
READ_LINE(vert->pos, 3);\
append\
}
#endif // DEBUG

#define WRITE_AND_ADD(append) for(size_t i = 0; i < length; i++)\
{\
for(Vertex vertex : v_file->vertex_list[i]){\
WRITE_LINE(vertex.pos, 3);\
append\
}\
}

struct TGVertexFile {
	uint8_t header;
	std::vector<std::vector<Vertex>> vertex_list = {};

	//Since TGV_VERSION_0_0_2
	std::vector<uint32_t> texture_index = {};
	std::vector<float*> color_list = {};

	uint32_t version; //One of the defined macros (e.g. TGV_VERSION_0_0_1)
	uint32_t polygon_count;

	bool hasColor();
	bool hasUV();
	void setHasColor(bool has);
	void setHasUV(bool has);

	Vertex* addVertex(size_t pylogen);
};

void load_tgvertex_file(char* name, TGVertexFile* v_file);

void save_tgvertex_file(char* name, TGVertexFile* v_file);