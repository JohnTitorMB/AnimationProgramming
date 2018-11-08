
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.
	vec4 pos = vec4(inputPosition, 1.0f);

	
	vec4 posAnimate = boneWeights.x * (skin.mat[int(boneIndices.x)] * pos) 
					+ boneWeights.y * (skin.mat[int(boneIndices.y)] * pos) 
					+ boneWeights.z * (skin.mat[int(boneIndices.z)] * pos) 
					+ boneWeights.w * (skin.mat[int(boneIndices.w)] * pos);
	

	gl_Position = sm.projectionMatrix * (modelViewMatrix * posAnimate);
	outNormal = mat3(modelViewMatrix) * normal;

	outNormal = normalize(outNormal);

}
