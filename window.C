#include "window.h"

#include "input_callbacks.h"

static void error_callback(int error, const char* description)
{
  std::cerr << "Error " << error << ": " << description << std::endl;
}

static void initGlew()
{
  if (glewInit() != GLEW_OK)
  {
    cout << "GLEW failed to initialise" << endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
}

static void initGlfw()
{
  if (!glfwInit())
      exit(EXIT_FAILURE);

  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

Window::Window(int _width, int _height, const char *title)
  : width(_width), height(_height)
{

  glfwSetErrorCallback(error_callback);
  initGlfw();
  handle = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!handle)
  {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
}

Window::~Window()
{
  glfwDestroyWindow(handle);
  glfwTerminate();
}

void Window::init(std::function<void (void)> block)
{
  glewExperimental = GL_TRUE;
  glfwMakeContextCurrent(handle);
  initGlew();

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  Input::init(handle);

  block();
}

void Window::eachFrame(std::function<void (int, int)> block)
{
  char title[20];
  double t = glfwGetTime();
  double lastFPS = 0;
  while (!glfwWindowShouldClose(handle))
  {
    double t2 = glfwGetTime();
    double dt = t2-t;
    if (lastFPS > 0.5f)
    {
      sprintf(title,"%gfps",1.0f/dt);
      glfwSetWindowTitle(handle,title);
      lastFPS = 0;
    }
    lastFPS += dt;
    t = t2;

    glfwGetFramebufferSize(handle, &width, &height);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    block(width, height);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
}

void addLightToSH(vec3 *sharm, Light* light) {
  vec3 dirn = normalize(-light->getPosition());
  sharm[0] += light->getColor() * 0.28209479177f;
  sharm[1] += light->getColor() * -0.4886025119f * dirn.y;
  sharm[2] += light->getColor() * 0.4886025119f * -dirn.z;
  sharm[3] += light->getColor() * -0.4886025119f * dirn.x;
  sharm[4] += light->getColor() * 1.09254843059f * (dirn.x * dirn.y);
  sharm[5] += light->getColor() * -1.09254843059f * (dirn.y * -dirn.z);
  sharm[6] += light->getColor() * 0.31539156525f * (3.0f * dirn.z * dirn.z - 1.0f);
  sharm[7] += light->getColor() * -1.09254843059f * (-dirn.z * dirn.x);
  sharm[8] += light->getColor() * -0.54627421529f * (dirn.x * dirn.x - dirn.y * dirn.y);
}

void Window::withShader(Shader *shader, std::function<void (Shader*)> block)
{
  shader->use();
  float ratio = (float) width / (float) height;
  if (camera) shader->updateMat4("view", camera->getView());
  if (lense) shader->updateMat4("projection", lense->getProjection(ratio));

  for (GLuint i = 0; i < 9; i++)
    sharm[i] = vec3();

  sort(lights.begin(), lights.end(), [](Light* a, Light* b) {
    vec3 ac = a->getColor(), bc = b->getColor();
    return dot(ac, ac) > dot(bc, bc);
  });

  // "dim" lights
  for_each (lights.begin()+2, lights.end(), [&](Light* l) {
    addLightToSH(sharm, l);
  });
  shader->updateVec3Array("sharm",sharm,9);
  // "bright" lights
  vec3 bright_p[2];
  vec3 bright_c[2];
  for (GLulong i = 0; i < 2; i++)
  {
    bright_p[i] = lights[i]->getPosition();
    bright_c[i] = lights[i]->getColor();
  }
  shader->updateVec3Array("lights",bright_p,2);
  shader->updateVec3Array("ld",bright_c,2);

  block(shader);
}

void Window::background(vec3 v)
{
  glClearColor(v.x,v.y,v.z,1.f);
}

void Window::useCamera(Camera* camera)
{
  this->camera = camera;
}

void Window::useLense(Lense* lense)
{
  this->lense = lense;
}

void Window::addLight(Light* light)
{
  lights.push_back(light);
}

void Window::removeLight(Light* light)
{
  // TODO...
}

void Window::addListener(Listener* l)
{
  Input::addListener(l);
}