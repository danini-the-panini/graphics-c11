#include "mesh.h"

const GLuint
  POINT_SIZE = 3,
  NORMAL_SIZE = 3,
  VERTEX_SIZE = 6;

Mesh::Mesh()
  : handle(0), shouldCalcNorms(false)
{
  glGenVertexArrays(1, &handle);
}

Mesh::~Mesh()
{

}

Mesh* Mesh::point(glm::vec3 v)
{
  points.push_back(v);
  return this;
}

Mesh* Mesh::normal(glm::vec3 v)
{
  normals.push_back(v);
  return this;
}

Mesh* Mesh::face(GLuint a, GLuint b, GLuint c)
{
  faces.push_back(a);
  faces.push_back(b);
  faces.push_back(c);
  return this;
}

Mesh* Mesh::line(GLuint a, GLuint b)
{
  faces.push_back(a);
  faces.push_back(b);
  return this;
}

Mesh* Mesh::calculateNormals(bool v)
{
  shouldCalcNorms = v;
  return this;
}

Mesh* Mesh::build()
{
  if (shouldCalcNorms)
  {
    GLulong a,b,c;
    vector<vec3> *adj = new vector<vec3>[points.size()];
    for (GLulong i = 0, end = faces.size(); i < end; i+=3)
    {
      a = faces[i]; b = faces[i+1]; c = faces[i+2];
      vec3 n = normalize(
        cross(points[a]-points[b],
          points[a]-points[c]));
      adj[a].push_back(n);
      adj[b].push_back(n);
      adj[c].push_back(n);
    }
    for (GLulong i = 0, end = points.size(); i < end; i++)
    {
      vec3 norm(0,1,0);
      if (!adj[i].empty())
      {
        norm = vec3(0,0,0);
        for (vec3 n: adj[i]) norm += n;
      }
      normals.push_back(norm);
    }
  }

  vector<float> vertices;

  for (GLulong i = 0, end = points.size(); i < end; i++)
  {
    vertices.push_back(points[i].x);
    vertices.push_back(points[i].y);
    vertices.push_back(points[i].z);

    vertices.push_back(normals[i].x);
    vertices.push_back(normals[i].y);
    vertices.push_back(normals[i].z);
  }

  bind();

  GLuint ptr;
  glGenBuffers(1, &ptr);
  glBindBuffer(GL_ARRAY_BUFFER, ptr);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
          vertices.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &ptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ptr);

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint),
          faces.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(Shader::POSITION_LOC);
  glVertexAttribPointer(Shader::POSITION_LOC, POINT_SIZE, GL_FLOAT, GL_FALSE,
          VERTEX_SIZE * sizeof(float), 0);

  glEnableVertexAttribArray(Shader::NORMAL_LOC);
  glVertexAttribPointer(Shader::NORMAL_LOC, NORMAL_SIZE, GL_FLOAT, GL_FALSE,
          VERTEX_SIZE * sizeof(float), (GLvoid*)(POINT_SIZE * sizeof(float)));

  return this;
}

Mesh* Mesh::cube(float w, float h, float d)
{
  return (new Mesh())

  ->point(vec3(-w, -h, -d))
  ->point(vec3(-w, -h,  d))
  ->point(vec3( w, -h,  d))
  ->point(vec3( w, -h, -d))
  ->point(vec3(-w,  h, -d))
  ->point(vec3(-w,  h,  d))
  ->point(vec3( w,  h,  d))
  ->point(vec3( w,  h, -d))

  // top
  ->face(1, 0, 2)
  ->face(2, 0, 3)

  // bottom
  ->face(4, 5, 6)
  ->face(4, 6, 7)

  // right
  ->face(7, 6, 2)
  ->face(7, 2, 3)

  // left
  ->face(5, 4, 1)
  ->face(1, 4, 0)

  // front
  ->face(5, 1, 6)
  ->face(6, 1, 2)

  // back
  ->face(0, 4, 7)
  ->face(0, 7, 3)

  ->calculateNormals()

  ->build();
}

Mesh* Mesh::sphere(float radius, int rows, int cols)
{
  Mesh* m = new Mesh();

  vec3 v;
  for(int i = 0; i <= rows; i++)
  {

      float lat = (float)(M_PI * ((float) i / (float)rows - 0.5f));
      float s1 = sin(lat);
      float c1 = cos(lat);

      for(int j = 0; j < cols; j++)
      {
          float lng = (float)(2.f * M_PI * ((float) j / (float)cols));
          float x = cos(lng);
          float y = sin(lng);

          v = vec3(x * c1, y * c1, s1);

          m->point(v*radius);
          m->normal(v);
      }
  }

  int a,b,c,d;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols-1; j++)
    {
      // sew each quad
      a = cols*i + j;
      b = a + 1;
      c = a + cols;
      d = b + cols;
      m->face(a, b, d);
      m->face(a, d, c);
    }
    // sew the edges
    a = cols*i+cols-1;
    b = cols*i;
    c = a + cols;
    d = b + cols;
    m->face(a, b, d);
    m->face(a, d, c);
  }

  return m->build();
}

Mesh* Mesh::wavefront(const char* file)
{
  Mesh* m = new Mesh();

  ifstream in(file);
  string line;

  vector<vec3> normals;
  vector<GLuint> vinds;
  vector<GLuint> ninds;

  while (in)
  {
    getline(in, line);

    auto e = split(line);
    if (e.empty()) continue;
    if (e[0].compare("v") == 0)
    {
      m->point(vec3(atof(e[1].c_str()),atof(e[2].c_str()),atof(e[3].c_str())));
    } else if (e[0].compare("vn") == 0)
    {
      normals.push_back(vec3(atof(e[1].c_str()),atof(e[2].c_str()),atof(e[3].c_str())));
    } else if (e[0].compare("f") == 0)
    {
      for (GLuint i = 1; i < e.size(); i++)
      {
        auto vn = split(e[i],'/',true);

        vinds.push_back(atoi(vn[0].c_str())-1);
        ninds.push_back(atoi(vn[2].c_str())-1);
      }
    }
  }
  in.close();

  bool* visited = new bool[m->points.size()];
  for (GLulong i = 0, end = m->points.size(); i < end; i++)
    visited[i] = 0;

  vec3* normals2 = new vec3[normals.size()];

  for (GLulong i = 0, end = vinds.size(); i < end; i++)
  {
    GLuint ni = ninds[i];
    GLuint vi = vinds[i];
    if (!visited[vi])
    {
      visited[vi] = true;

      normals2[vi] = normals[ni];
    }
  }

  for (GLulong i = 0, end = normals.size(); i < end; i++)
  {
    m->normal(normals2[i]);
  }

  for (GLulong i = 0, end = vinds.size(); i < end; i+=3)
    m->face(vinds[i], vinds[i+1], vinds[i+2]);

  return m->build();
}

void Mesh::bind()
{
  glBindVertexArray(handle);
}

void Mesh::draw(GLenum type)
{
  bind();

  if (type == GL_PATCHES)
    glPatchParameteri(GL_PATCH_VERTICES, 3);

  glDrawElements(type, (GLsizei)faces.size(), GL_UNSIGNED_INT, 0);
}
