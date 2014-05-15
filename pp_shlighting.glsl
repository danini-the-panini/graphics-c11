#version 330

layout (location = 0) out vec4 out_color;

uniform vec3 sharm[16];

uniform vec3 lights[2];
uniform vec3 ld[2];

in vec3 f_normal;
in vec3 f_position;
in vec3 f_eye;

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
  colour += sharm[13] * d.x*(4.0f*z2-3.0f*y2-3.0f*x2);
  colour += sharm[14] * (x2-y2)*d.z;
  colour += sharm[15] * d.x*(x2-3.0f*y2);

  colour.x = max(0,colour.x);
  colour.y = max(0,colour.y);
  colour.z = max(0,colour.z);
  return colour;
}

void main()
{
    vec3 ambient = vec3(0,0,0);

    float ia = 0.0f;
    float id = 0.7f;
    float is = 0.3f;
    float s = 100.0f;
    
    vec3 v = normalize(f_eye-f_position);

    for (int i = 0; i < 2; i++)
    {
      vec3 l = normalize(lights[i]);
      vec3 r = normalize(reflect(-l,f_normal));

      float ip = ia + max(dot(l,f_normal),0)*id + pow(max(dot(r,v),0),s)*is;
      ambient += ip*ld[i];
    }

    ambient += lightNormal(f_normal);

    out_color = vec4(ambient,1);
}

