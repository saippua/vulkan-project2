// #version 450
//
// layout(binding = 0) uniform UniformBufferObject {
// 	mat4 model;
// 	mat4 view;
//  	mat4 proj;
// } ubo;
//
// layout(location = 0) in vec3 inPosition;
// layout(location = 1) in vec3 inColor;
// layout(location = 2) in vec2 inTexCoord;
//
// layout(location = 3) in vec3 instancePos;
// layout(location = 4) in vec3 instanceRot;
// layout(location = 5) in float instanceScale;
//
// layout(location = 0) out vec3 fragColor;
//
// void main() {
// 	//vec4 locPos = vec4(inPosition.xyz, 1.0);
//     //vec4 pos = vec4((locPos.xyz * instanceScale) + instancePos, 1.0);
// 	//gl_Position = ubo.proj * ubo.model * ubo.view * pos;
//     gl_Position = ubo.proj * ubo.view * (vec4(instancePos, 1) + (ubo.model * (vec4(inPosition * instanceScale, 1.0))));
//     fragColor = inColor;



#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);
    fragColor = inColor;
}
