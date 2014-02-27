#pragma once

#include "include.h"

class Shader
{
public:
  static Shader* current();
  static GLuint loadShader(const char* file, GLenum type);
  static void shaderLog(GLuint handle);
  static void programLog(GLuint handle);

  Shader();
  ~Shader();

  Shader* vertex(const char* file);
  Shader* geometry(const char* file);
  Shader* tess_control(const char* file);
  Shader* tess_eval(const char* file);
  Shader* fragment(const char* file);
  Shader* compute(const char* file);

  Shader* build();

  GLint findAttribute(const char* name);
  GLint findUniform(const char* name);

  void updateMat4(const char* name, mat4 v);
  void updateFloat(const char* name, float);
  void updateInt(const char* name, int);
  void updateVec3(const char* name, vec3 v);
  void updateVec4(const char* name, vec4 v);
  void updateVec3Array(const char* name, const vec3* v, int size);

  GLint getPositionLocation();
  GLint getNormalLocation();

  void use();

private:
  GLuint handle;
  GLuint vert, tc, te, geom, frag, comp;
  static Shader* current_shader;

  GLint position;
  GLint normal;

  map<const char*, GLint> uniforms;
};