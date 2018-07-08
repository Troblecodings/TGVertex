#include "TGVertex.hpp"

bool TGVertexFile::hasColor() {
	return this->header & 1 == 1;
}

bool TGVertexFile::hasUV() {
	return this->header & 2 == 2;
}

Vertex* TGVertexFile::addVertex() {
	size_t size = this->vertex_list.size();
	this->vertex_list.resize(size + 1);
	return &this->vertex_list[size];
}

void load_tgvertex_file(char* name, TGVertexFile* v_file) {
	FILE* file = fopen(name, "rba");
	long length = ftell(file) - 1;
	fseek(file, 0, SEEK_SET);

#ifdef DEBUG
	if (file == NULL) {
		OUT_LV_DEBUG("File " + name + " couldn't be opened, that shouldn't happen!");
		return;
	}
#endif // DEBUG

	fread(&v_file->header, sizeof(uint8_t), 1, file);

	if (v_file->hasColor() && v_file->hasUV()) {
		READ_AND_ADD(9,
			READ_LINE(vert->color, 4); 
		    READ_LINE(vert->uv, 2);)
	} 
	else if (v_file->hasUV()) {
		READ_AND_ADD(5,
		    READ_LINE(vert->uv, 2);)
	}
	else if (v_file->hasColor()) {
		READ_AND_ADD(7,
			READ_LINE(vert->color, 4);)
	}
	else {
		READ_AND_ADD(3)
	}

}