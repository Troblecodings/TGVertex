#pragma once

#define TGV_VERSION_0_0_1 1 
#define TGV_VERSION_0_0_2 2
#define TGV_VERSION_LATEST TGV_VERSION_0_0_2

#include "stdbase.hpp"
#include "Vertex.hpp"

#ifdef USE_TGE
#define ADD_TO_BUFFER(buffer, file, color_only) for (size_t i = 0; i < file.polygon_count; i++) {\
glm::vec4 color = { file.color_list[i][0], file.color_list[i][1], file.color_list[i][2], file.color_list[i][3] };\
for (Vertex vert : file.vertex_list[i]) {\
buffer->add({ { vert.pos[0], vert.pos[1], vert.pos[2] }, color,{ vert.uv[0], vert.uv[1] }, color_only });\
}\
}
#endif

#define READ_LINE(buf, count) fread(buf, sizeof(float), count, file);
#define WRITE_LINE(buf, count) fwrite(buf, sizeof(float), count, file);

#define READ_AND_ADD(append) for (size_t i = 0; i < length; i++)\
{\
Vertex* vert = v_file->addVertex(pylogen);\
READ_LINE(vert->pos, 3);\
append\
}

#define WRITE_AND_ADD(append) for(Vertex vertex : v_file->vertex_list[pylogen]){\
WRITE_LINE(vertex.pos, 3);\
append\
}

struct TGVertexFile {
	uint8_t header;
	std::vector<std::vector<Vertex>> vertex_list = {};

	//Since TGV_VERSION_0_0_2
	std::vector<uint32_t> texture_index = {};
	std::vector<float*> color_list = {};

	uint32_t version = TGV_VERSION_0_0_2; //One of the defined macros (e.g. TGV_VERSION_0_0_2)
	uint32_t polygon_count;

	bool hasColor();
	bool hasUV();
	void setHasColor(bool has);
	void setHasUV(bool has);

	Vertex* addVertex(size_t pylogen);
};

void load_tgvertex_file(char* name, TGVertexFile* v_file);

void save_tgvertex_file(char* name, TGVertexFile* v_file);
