#include "include.h"

#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "lense.h"
#include "light.h"
#include "camera_control.h"
#include "input_callbacks.h"

using namespace std;

int main(void)
{

  Window* window = new Window(640, 480, "Simple example");

  window->init([&] {

    // glDisable(GL_CULL_FACE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    window->background(vec3(1,1,1));

    Shader* lighting = (new Shader())
      ->vertex("simple_vert.glsl")
      // ->geometry("pass_geom.glsl")
      ->fragment("pp_shlighting.glsl")
      ->build();

    Shader* pass = (new Shader())
      ->vertex("simple_vert.glsl")
      ->fragment("pass_frag.glsl")
      ->build();

    lighting->use();

    Mesh* monkey = Mesh::wavefront("monkey.obj");
    Mesh* ball = Mesh::sphere();
    Mesh* box = Mesh::cube(0.1f,0.1f,0.1f);
    Mesh* axis = (new Mesh())
      ->point(vec3(0,0,0))->normal(vec3(0,1,0))
      ->point(vec3(0,1,0))->normal(vec3(0,1,0))
      ->line(0,1)
      ->build();

    Camera* camera = new Camera(vec3(1,2,1), vec3(0,0,0));
    Lense* lense = new Lense(45.0f);

    window->useCamera(camera);
    window->useLense(lense);

    vec3 ld1(0,0.2,0.5);
    vec3 ld2(0.9,0.7,0.4);

    vector<Light*> lights;
    Light* testLight = new Light(vec3(), ld1*0.5f);
    Light* testLight2 = new Light(vec3(), ld2);
    lights.push_back(testLight);
    lights.push_back(testLight2);
    lights.push_back(new Light(vec3(-5,3,1), ld1));
    lights.push_back(new Light(vec3(2,5,5), ld2*0.3f));

    for (auto l: lights)
      window->addLight(l);

    CameraControl* control = new CameraControl(camera);

    window->addListener(control);

    window->eachFrame([&] (int width, int height)
    {
      mat4 world, lightWorld;

      lightWorld = rotate(mat4(), (float) glfwGetTime() * 25.f, vec3(0.f, 1.f, 0.f));
      testLight->setPosition((lightWorld*vec4(2,-2,5,1)).xyz());
      lightWorld = rotate(mat4(), (float) glfwGetTime() * -12.5f, vec3(0.f, 1.f, 0.f));
      testLight2->setPosition((lightWorld*vec4(5,3,1,1)).xyz());

      window->withShader(lighting, [&] (Shader* s)
      {
        s->updateMat4("world",world);
        monkey->draw();
      });

      window->withShader(pass, [&] (Shader* s)
      {
        // s->updateMat4("world",world);
        // s->updateVec3("color",vec3(1,0,1));
        // ball->draw();

        for (auto l: lights)
        {
          s->updateMat4("world",translate(mat4(), l->getPosition()));
          s->updateVec3("color",l->getColor());
          box->draw();
        }

        world = scale(mat4(),vec3(100));
        s->updateMat4("world",world);
        s->updateVec3("color",vec3(1,0,0));
        axis->draw(GL_LINES);
        s->updateMat4("world",rotate(world, 90.f, vec3(1,0,0)));
        s->updateVec3("color",vec3(0,1,0));
        axis->draw(GL_LINES);
        s->updateMat4("world",rotate(world, 90.f, vec3(0,0,1)));
        s->updateVec3("color",vec3(0,0,1));
        axis->draw(GL_LINES);

      });
    });

    delete lighting;
    delete pass;
    delete camera;
    delete lense;
    // for (auto l: lights)
    //   delete l;
    delete testLight;
    delete control;
    delete monkey;
    delete box;
  });


  delete window;

  return EXIT_SUCCESS;
}
