#include "TGVertex.hpp"

bool TGVertexFile::hasColor() {
	return (this->header & 1) == 1;
}

bool TGVertexFile::hasUV() {
	return (this->header & 2) == 2;
}

void TGVertexFile::setHasColor(bool has) {
	if (has) {
		this->header |= 1;
	}
	else {
		this->header ^= 1;
	}
}

void TGVertexFile::setHasUV(bool has) {
	if (has) {
		this->header |= 2;
	}
	else {
		this->header ^= 2;
	}
}

Vertex* TGVertexFile::addVertex() {
	size_t size = this->vertex_list.size();
	this->vertex_list.resize(size + 1);
	return &this->vertex_list[size];
}

void load_tgvertex_file(char* name, TGVertexFile* v_file) {
	FILE* file = fopen(name, "rb");

#ifdef DEBUG
	if (file == NULL) {
		OUT_LV_DEBUG("File " + name + " couldn't be opened, that shouldn't happen!");
		return;
	}
#endif // DEBUG

	fread(&v_file->header, sizeof(uint8_t), 1, file);
	size_t length = 0;
	fread(&length, sizeof(size_t), 1, file);

	if (v_file->hasColor() && v_file->hasUV()) {
		READ_AND_ADD(
			READ_LINE(vert->color, 4);
		    READ_LINE(vert->uv, 2);)
	} 
	else if (v_file->hasUV()) {
		READ_AND_ADD(
		    READ_LINE(vert->uv, 2);)
	}
	else if (v_file->hasColor()) {
		READ_AND_ADD(
			READ_LINE(vert->color, 4);
		    vert->color_only = 1;)
	}
	else {
		READ_AND_ADD(;)
	}
	fclose(file);
}

void save_tgvertex_file(char* name, TGVertexFile* v_file) {
	FILE* file = fopen(name, "wb");

#ifdef DEBUG
	if (file == NULL) {
		OUT_LV_DEBUG("File " + name + " couldn't be opened, that shouldn't happen!");
		return;
	}
#endif // DEBUG

	fwrite(&v_file->header, sizeof(uint8_t), 1, file);

	size_t size_of_block = v_file->vertex_list.size();
	fwrite(&size_of_block, sizeof(size_t), 1, file);

	if (v_file->hasColor() && v_file->hasUV()) {
		WRITE_AND_ADD(
			WRITE_LINE(vertex.color, 4);
		    WRITE_LINE(vertex.uv, 2);)
	}
	else if (v_file->hasUV()) {
		WRITE_AND_ADD(
			WRITE_LINE(vertex.uv, 2);)
	}
	else if (v_file->hasColor()) {
		WRITE_AND_ADD(
			WRITE_LINE(vertex.color, 4);)
	}
	else {
		WRITE_AND_ADD(;)
	}
	fclose(file);
}
