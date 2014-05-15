#include "shader.h"

Shader* Shader::current_shader = NULL;

Shader* Shader::current()
{
  return Shader::current_shader;
}
GLuint Shader::loadShader(const char* file, GLenum type)
{
  GLuint handle = glCreateShader(type);

  ifstream in(file);
  stringstream buffer;
  buffer << in.rdbuf();
  string content(buffer.str());
  in.close();

  const char * source = content.c_str();
  glShaderSource(handle, 1, &source, NULL);
  glCompileShader(handle);

  shaderLog(handle);

  return handle;
}
void Shader::shaderLog(GLuint handle)
{
  int status;
  glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE)
  {
     /* Get the length of the info log. */
     int len;
     glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &len);

     /* Get the info log. */
     char* log = new char[len];
     glGetShaderInfoLog(handle, len, &len, log);

     /* Print error */
     cerr << "Compilation error: " << log << endl;

     /* Finally, free the memory allocated. */
     delete log;

     /* Exit the program. */
     exit(-1);
  }
}
void Shader::programLog(GLuint handle)
{
  int status;
  glGetProgramiv(handle, GL_LINK_STATUS, &status);

  if (status == GL_FALSE)
  {
     /* Get the length of the info log. */
     int len;
     glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &len);

     /* Get the info log. */
     char* log = new char[len];
     glGetProgramInfoLog(handle, len, &len, log);

     /* Print error */
     cerr << "Link error: " << log << endl;

     /* Finally, free the memory allocated. */
     delete log;

     /* Exit the program. */
     exit(-1);
  }
}

Shader::Shader()
  : vert(0), tc(0), te(0), geom(0), frag(0), comp(0)
{
  handle = glCreateProgram();
}
Shader::~Shader()
{

}

Shader* Shader::vertex(const char* file)
{
  vert = loadShader(file, GL_VERTEX_SHADER);
  return this;
}
Shader* Shader::tess_control(const char* file)
{
  tc = loadShader(file, GL_TESS_CONTROL_SHADER);
  return this;
}
Shader* Shader::tess_eval(const char* file)
{
  te = loadShader(file, GL_TESS_EVALUATION_SHADER);
  return this;
}
Shader* Shader::geometry(const char* file)
{
  geom = loadShader(file, GL_GEOMETRY_SHADER);
  return this;
}
Shader* Shader::fragment(const char* file)
{
  frag = loadShader(file, GL_FRAGMENT_SHADER);
  return this;
}
Shader* Shader::compute(const char* file)
{
  comp = loadShader(file, GL_COMPUTE_SHADER);
  return this;
}

Shader* Shader::build()
{
  if (vert) glAttachShader(handle, vert);
  if (tc) glAttachShader(handle, tc);
  if (te) glAttachShader(handle, te);
  if (geom) glAttachShader(handle, geom);
  if (frag) glAttachShader(handle, frag);
  if (comp) glAttachShader(handle, comp);

  glLinkProgram(handle);

  programLog(handle);

  use();
  
  return this;
}

GLint Shader::findAttribute(const char* name)
{
  return glGetAttribLocation(handle, name);
}
GLint Shader::findUniform(const char* name)
{
  auto it = uniforms.find(name);
  if (it == uniforms.end())
  {
    GLint x = glGetUniformLocation(handle, name);
    uniforms.emplace(name,x);
    return x;
  }
  return it->second;
}

void Shader::updateMat4(const char* name, mat4 v)
{
  GLint x = findUniform(name);
  if (x != -1) glUniformMatrix4fv(x, 1, GL_FALSE, value_ptr(v));
}
void Shader::updateFloat(const char* name, float v)
{
  GLint x = findUniform(name);
  if (x != -1) glUniform1f(x, v);
}
void Shader::updateInt(const char* name, int v)
{
  GLint x = findUniform(name);
  if (x != -1) glUniform1i(x,v);
}
void Shader::updateVec3(const char* name, vec3 v)
{
  GLint x = findUniform(name);
  if (x != -1) glUniform3fv(x, 1, value_ptr(v));
}
void Shader::updateVec4(const char* name, vec4 v)
{
  GLint x = findUniform(name);
  if (x != -1) glUniform4fv(x, 1, value_ptr(v));
}
void Shader::updateVec3Array(const char* name, const vec3* arr, int size)
{
  GLint x = findUniform(name);
  if (x != -1)
  {
    float* floats = new float[3*size];
    for (int i = 0; i < size; i++)
    {
      floats[i*3] = arr[i].x; floats[i*3+1] = arr[i].y; floats[i*3+2] = arr[i].z;
    }
    glUniform3fv(x, size, floats);
  }
}

void Shader::use()
{
  Shader::current_shader = this;
  glUseProgram(handle);
}