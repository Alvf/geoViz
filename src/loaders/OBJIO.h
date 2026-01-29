#ifndef OBJ_IO_H
#define OBJ_IO_H

#include "SETTINGS.h"

using namespace std;
// File formats: Pobjs have pentas and verts and 4D
// Tobjs have tets and verts and 3D
// objs are as standard

// reads VERY BASIC strand obj (assumes vertices are just in the order of ingestion)
bool readBasicStrandOBJ(const char* filename, vector<VEC3>& verts);
// outputs basic strand obj (puts vertices in order of vector<VEC3> and connects the dots)
bool writeBasicStrandOBJ(const vector<VEC3>& verts, const char* filename);

// reads multi-strand obj (assumes vertex soup followed by l 1 2 3 4 5 .... kind of formatting)
bool readMultStrandOBJ(const char* filename, vector<VEC3>& vs, vector<vector<int>>& edges);

// writes multistrand file with verts and edge indices
bool writeMultStrandOBJ(const vector<VEC3>& vs, const vector<vector<int>>& edges, const char* filename);
bool writeMultStrandOBJ(const vector<vector<VEC3>>& allVs, const char* filename);

#endif