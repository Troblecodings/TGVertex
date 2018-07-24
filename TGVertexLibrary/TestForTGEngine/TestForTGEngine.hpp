#pragma once

#define DEBUG

#include <TGEngine.hpp>
#define USE_TGE
#include <TGVertexLib.hpp>

struct Test : App {

	TGVertexFile file = {};

	virtual void drawloop(VertexBuffer* buffer);

};

void testWrite(char* name);

void testRead(char* name, Test* buffer);