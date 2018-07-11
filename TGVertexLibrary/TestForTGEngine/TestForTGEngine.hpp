#pragma once

#define DEBUG

#include <TGVertex.hpp>
#include <TGEngine.hpp>

struct Test : App {

	TGVertexFile file = {};

	virtual void drawloop(VertexBuffer* buffer);

};

void testWrite(char* name);

void testRead(char* name, Test* buffer);