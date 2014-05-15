#version 430

layout (location = 1) in vec3 position;
layout (location = 2) in vec3 normal;

uniform vec3 sharm[16];

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec3 f_normal;
out vec3 f_position;
out vec3 f_eye;

vec3 lightNormal(vec3 d)
{
  vec3 colour = sharm[0];

  float x2 = d.x * d.x;
  float y2 = d.y * d.y;
  float z2 = d.z * d.z;

  colour += sharm[1 ] * d.y;
  colour += sharm[2 ] * d.z;
  colour += sharm[3 ] * d.x;

  colour += sharm[4 ] * (d.x * d.y);
  colour += sharm[5 ] * (d.y * d.z);
  colour += sharm[6 ] * (2.0f * z2 - y2 - x2);
  colour += sharm[7 ] * (d.x * d.z);
  colour += sharm[8 ] * (x2 - y2);

  colour += sharm[9 ] * d.y*(3.0f*x2-y2);
  colour += sharm[10] * d.x*d.y*d.z;
  colour += sharm[11] * d.y*(4.0f*z2-y2-x2);
  colour += sharm[12] * d.z*(2.0f*z2-3.0f*y2-3.0f*x2);
  colour += sharm[13] * d.x*(4.0f*z2-y2-x2);
  colour += sharm[14] * (x2-y2)*d.z;
  colour += sharm[15] * d.x*(x2-3.0f*y2);
  return colour;
}

void main()
{
    f_eye = (inverse(view) * vec4 (0, 0, 1, 1)).xyz;

    f_normal = (world * vec4(normal,0)).xyz;

    float x = max(0,length(lightNormal(f_normal)));

    vec3 pos = normalize(position)*x;

    f_position = (world * vec4(pos,1)).xyz;
    gl_Position = projection * view * world * vec4(pos,1);
}

