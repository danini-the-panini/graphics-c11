#version 330

layout (location = 0) out vec4 out_color;

uniform vec3 sharm[9];

in vec3 v_normal;

vec3 lightNormal(vec3 dirn)
{
  vec3 colour = sharm[0];
  colour += sharm[1] * dirn.x;
  colour += sharm[2] * dirn.y;
  colour += sharm[3] * dirn.z;
  colour += sharm[4] * (dirn.x * dirn.z);
  colour += sharm[5] * (dirn.z * dirn.y);
  colour += sharm[6] * (dirn.y * dirn.x);
  colour += sharm[7] * (3.0f * dirn.z * dirn.z - 1.0f); colour += sharm[8] * (dirn.x * dirn.x - dirn.y * dirn.y);
  return colour;
}

void main()
{
    out_color = vec4(lightNormal(v_normal),1);
}

