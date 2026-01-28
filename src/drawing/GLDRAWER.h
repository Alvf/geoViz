#ifndef DRAW_GL_H
#define DRAW_GL_H

#include "../SETTINGS.h"

VEC3 colorWrap(const VEC3& nonWrapped);

// draws the x/y/z axes
void drawAxes();

// given a sequence of points in a row, draws a single strand
void drawStrand(const std::vector<VEC3>& pts, const VEC3& col = VEC3(0.0,0.0,0.0), const double& weight = 4.0);

// given two points and a color, draws a little debug line
void drawLine(const VEC3& a, const VEC3& b, const VEC3& col, const double& weight = 3.0);

// draws points with a certain color
void drawPoints(const std::vector<VEC3> & pts, const VEC3& col, const double& rad);

// draws a single point with a certain color
void drawPoint(const VEC3& pt, const VEC3& col, const double& rad);

#endif