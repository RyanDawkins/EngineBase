
#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCo;
layout (location = 3) in vec3 inColor;

layout (location = 0) smooth out vec4 vPosition;
layout (location = 1) smooth out vec4 vNormal;
layout (location = 2) smooth out vec2 vTexCo;
layout (location = 3) smooth out vec4 vColor;

uniform mat4 uObjectTransform = mat4x4(1.0);
//uniform mat4 uObjectInverseTransform = mat4x4(1.0);

uniform mat4 uObjectWorldViewPerpsect = mat4x4(1.0);

void main() 
{
	gl_Position = uObjectWorldViewPerpsect * vec4(inPosition, 1.0);

	vPosition = uObjectTransform * vec4(inPosition, 1.0);

	vec4 N = vec4(inNormal, 0.0);
	vNormal = normalize(uObjectTransform * N);
	//vNormal.z *= -1; // left hand to right hand

	vTexCo = inTexCo;
	vColor = vec4(inColor, 1.0);
}
