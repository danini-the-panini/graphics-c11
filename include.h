#pragma once
#define GLM_SWIZZLE

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

using glm::cross;
using glm::dot;
using glm::lookAt;
using glm::mat4;
using glm::normalize;
using glm::ortho;
using glm::perspective;
using glm::rotate;
using glm::scale;
using glm::translate;
using glm::value_ptr;
using glm::vec3;
using glm::vec4;

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::for_each;
using std::function;
using std::getline;
using std::ifstream;
using std::map;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;

static void checkError(const char* message)
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
  {
    cout << "Error: " << message << ", " << error << endl;
  }
}

static vector<string> &split(const string &s, char delim, bool includeEmpty, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        if (includeEmpty || !item.empty()) elems.push_back(item);
    }
    return elems;
}

static vector<string> split(const string &s, char delim = ' ', bool includeEmpty = false)
{
    vector<string> elems;
    split(s, delim, includeEmpty, elems);
    return elems;
}
