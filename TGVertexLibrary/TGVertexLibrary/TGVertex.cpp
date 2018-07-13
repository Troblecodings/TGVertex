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

Vertex* TGVertexFile::addVertex(size_t pylogen) {
	size_t size = this->vertex_list[pylogen].size();
	this->vertex_list[pylogen].resize(size + 1);
	return &this->vertex_list[pylogen][size];
}

#define DEBUG
void load_tgvertex_file(char* name, TGVertexFile* v_file) {
	FILE* file = fopen(name, "rb");

#ifdef DEBUG
	if (file == NULL) {
		std::cerr << "File " << name << " couldn't be opened, that shouldn't happen!";
		return;
	}
#endif // DEBUG

	fread(&v_file->version, sizeof(uint32_t), 1, file);
	fread(&v_file->header, sizeof(uint8_t), 1, file);
	fread(&v_file->polygon_count, sizeof(uint32_t), 1, file);

	v_file->vertex_list.resize(v_file->polygon_count);

#ifdef DEBUG
	if (v_file->version <= 1 || v_file->version > TGV_VERSION_LATEST) {
		std::cerr << "Unsupported version: " << v_file->version << ". Latest version supported: " << TGV_VERSION_LATEST;
		return;
	}
#endif

	size_t length = 0;
	for (size_t pylogen = 0; pylogen < v_file->polygon_count; pylogen++)
	{
		fread(&length, sizeof(size_t), 1, file);
		fread(v_file->color_list[pylogen], sizeof(float), 4, file);
		fread(&v_file->texture_index[pylogen], sizeof(uint32_t), 1, file);

		if (v_file->version == TGV_VERSION_0_0_2) {

			if (v_file->hasUV()) {
				READ_AND_ADD(
					READ_LINE(vert->uv, 2);)
			}
			else if (v_file->hasColor()) {
				READ_AND_ADD(
					vert->color_only = 1;)
			}
			else {
				READ_AND_ADD(;)
			}
		}
	}

	fclose(file);
}

void save_tgvertex_file(char* name, TGVertexFile* v_file) {
	FILE* file = fopen(name, "wb");

#ifdef DEBUG
	if (file == NULL) {
		std::cerr << "File " << name << " couldn't be opened, that shouldn't happen!";
		return;
	}
	if (v_file->vertex_list.size() < 1) {
		std::cerr << "Vertex list is empty for file: " << name << ", couldn't be saved!";
		return;
	}
#endif // DEBUG

	fwrite(&v_file->version, sizeof(uint32_t), 1, file);
	fwrite(&v_file->header, sizeof(uint8_t), 1, file);
	fwrite(&(v_file->polygon_count = v_file->vertex_list.size()), sizeof(size_t), 1, file);

	size_t size_of_block = v_file->vertex_list.size();
	fwrite(&size_of_block, sizeof(size_t), 1, file);

	size_t length = 0;
	for (size_t pylogen = 0; pylogen < v_file->polygon_count; pylogen++)
	{
		fwrite(&length, sizeof(size_t), 1, file);
		fwrite(v_file->color_list[pylogen], sizeof(float), 4, file);
		fwrite(&v_file->texture_index[pylogen], sizeof(uint32_t), 1, file);

		if (v_file->hasUV()) {
			WRITE_AND_ADD(
			    WRITE_LINE(vertex.uv, 2);)
		}
		else {
			WRITE_AND_ADD(;)
		}
	}
	fclose(file);
}
