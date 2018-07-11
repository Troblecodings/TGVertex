// TestForTGEngine.cpp : Defines the entry point for the console application.
//

#include "TestForTGEngine.hpp"

int main()
{
	Test test = Test();
	testWrite((char*)"Test.tgv");
	testRead((char*)"Test.tgv", &test);
	initTGEngine((App*)&test);
    return 0;
}

void Test::drawloop(VertexBuffer* buffer) {
	buffer->addAll(this->file.vertex_list.data(), this->file.vertex_list.size());
}

void testWrite(char* name) {
	std::vector<Vertex> vert = {
		{ { 1, 0, 0 },{ 1, 0, 0, 1 },{ 0, 0 }, VK_TRUE },
	    { { 1, 1, 0 },{ 1, 0, 0, 1 },{ 0, 0 }, VK_TRUE },
	    { { 0, 1, 0 },{ 1, 0, 0, 1 },{ 0, 0 }, VK_TRUE }
	};
	TGVertexFile vt = { 
		0,
		vert
	};
	vt.setHasColor(true);
	save_tgvertex_file(name, &vt);
}

void testRead(char* name, Test* test) {
	load_tgvertex_file(name, &test->file);
}