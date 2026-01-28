#include "GLDRAWER.h"

#include "../../ext/glfw/include/GLFW/glfw3.h"

#define MATH_EPS 1e-8

using namespace std;

VEC3 colorWrap(const VEC3& nonWrapped)
{
  VEC3 wrapped = nonWrapped;
  for(int i = 0; i < 3; i++)
  {
    wrapped[i] = wrapped[i] > 1.0? wrapped[i] - floor(wrapped[i]) : wrapped[i];
  }
  return wrapped;
}

///////////////////////////////////////////////////////////////////////
// draw coordinate axes, xyz = rgb
///////////////////////////////////////////////////////////////////////
void drawAxes()
{
  // draw coordinate axes
  glPushMatrix();
  //glTranslatef(-0.1f, -0.1f, -0.1f);
  glLineWidth(1.0f);
  glBegin(GL_LINES);
  // x axis is red
  glColor4f(10.0f, 0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glColor4f(10.0f, 0.0f, 0.0f, 0.0f);
  glVertex3f(10.0f, 0.0f, 0.0f);

  // y axis is green
  glColor4f(0.0f, 10.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glColor4f(0.0f, 10.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 10.0f, 0.0f);

  // z axis is blue
  glColor4f(0.0f, 0.0f, 10.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glColor4f(0.0f, 0.0f, 10.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 10.0f);
  glEnd();
  glLineWidth(1.0f);
  glPopMatrix();
}

void drawStrand(const std::vector<VEC3>& pts, const VEC3& col, const double& weight)
{
  glPushMatrix();
  glLineWidth(weight);

  glBegin(GL_LINE_STRIP);
  glColor4f(col[0],col[1],col[2],1);
  for(unsigned int i = 0; i < pts.size(); i++)
  {
    const VEC3& pt = pts[i];
    glVertex3f(pt[0], pt[1], pt[2]);
  }
  glEnd();

  glLineWidth(1.0f);
  glPopMatrix();
}

void drawLine(const VEC3& a, const VEC3& b, const VEC3& col, const double& weight)
{
  glPushMatrix();
  glLineWidth(weight);
  glBegin(GL_LINES);

  glColor4f(col[0], col[1], col[2], 1);
  glVertex3f(a[0], a[1], a[2]);
  glVertex3f(b[0], b[1], b[2]);
  
  glEnd();

  glLineWidth(1.0f);
  glPopMatrix();
}

void drawPoints(const std::vector<VEC3> & pts, const VEC3& col, const double& rad)
{
  glPushMatrix();
  glPointSize(rad);
  glColor4f(col[0], col[1], col[2], 1);
  glBegin(GL_POINTS);

  for(unsigned int i = 0; i < pts.size(); i++)
  {
    const VEC3& a = pts[i];
    glVertex3f(a[0], a[1], a[2]);
  }

  glPointSize(1.0);
  glEnd();
  glPopMatrix();
}

void drawPoint(const VEC3& pt, const VEC3& col, const double& rad)
{
  glPushMatrix();
  glPointSize(rad);
  glColor4f(col[0], col[1], col[2], 1);
  glBegin(GL_POINTS);

  glVertex3f(pt[0], pt[1], pt[2]);

  glPointSize(1.0);
  glEnd();
  glPopMatrix();
}