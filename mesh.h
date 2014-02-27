#pragma once

#include "include.h"

#include "shader.h"

class Mesh
{
public:
  Mesh();
  ~Mesh();
  Mesh* point(vec3);
  Mesh* normal(vec3);
  Mesh* face(GLuint,GLuint,GLuint);
  Mesh* line(GLuint,GLuint);
  Mesh* calculateNormals(bool v=true);
  Mesh* build();

  void bind();
  void draw(GLenum type=GL_TRIANGLES);

  static Mesh* cube(float w = 0.5f, float h = 0.5f, float d = 0.5f);
  static Mesh* sphere(float radius = 1.0f, int rows = 32, int cols = 32);
  static Mesh* wavefront(const char*);

private:
  GLuint handle;
  vector<vec3> points;
  vector<vec3> normals;
  vector<GLuint> faces;
  bool shouldCalcNorms;
};