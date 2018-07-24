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
	ADD_TO_BUFFER(buffer, this->file)
}

void testWrite(char* name) {
	std::vector<Vertex> vert = {
		{ { 1, 0, 0 },{ 0, 0 }, VK_TRUE },
		{ { 1, 1, 0 },{ 0, 0 }, VK_TRUE },
		{ { 0, 1, 0 },{ 0, 0 }, VK_TRUE }
	};
	TGVertexFile vt = { 
		1,
	    {
		    vert
	    }
	};
	vt.setHasColor(true);
	float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	vt.color_list = {
		color
	};
	vt.texture_index = {
		0
	};
	save_tgvertex_file(name, &vt);
}

void testRead(char* name, Test* test) {
	load_tgvertex_file(name, &test->file);
}