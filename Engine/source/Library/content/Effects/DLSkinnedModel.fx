#include "include\\Common.fxh"

#define MaxBones 120

/************* Resources *************/
cbuffer CBufferPerFrame
{
	float4 AmbientColor = { 1.0f, 1.0f, 1.0f, 0.0f };
	float3 LightDirection = { 0.0f, 0.0f, 0.0f };
    float3 CameraPosition;
}

cbuffer CBufferPerObject
{
    float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
    float4x4 World : WORLD;
}

cbuffer CBufferSkinning
{
    float4x4 BoneTransforms[MaxBones];
}

Texture2D ColorTexture;

SamplerState ColorSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

/************* Data Structures *************/

struct VS_INPUT
{
    float4 ObjectPosition : POSITION;
    float2 TextureCoordinate : TEXCOORD;
    float3 Normal : NORMAL;
    uint4 BoneIndices : BONEINDICES;
    float4 BoneWeights : WEIGHTS;	
};

struct VS_OUTPUT
{
    float4 Position : SV_Position;
    float3 Normal : NORMAL;
    float2 TextureCoordinate : TEXCOORD0;
    float3 WorldPosition : TEXCOORD1;
    float Attenuation : TEXCOORD2;
};

/************* Vertex Shader *************/

VS_OUTPUT vertex_shader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;      

    float4x4 skinTransform = (float4x4)0;
    skinTransform += BoneTransforms[IN.BoneIndices.x] * IN.BoneWeights.x;
    skinTransform += BoneTransforms[IN.BoneIndices.y] * IN.BoneWeights.y;
    skinTransform += BoneTransforms[IN.BoneIndices.z] * IN.BoneWeights.z;
    skinTransform += BoneTransforms[IN.BoneIndices.w] * IN.BoneWeights.w;
    
    float4 position = mul(IN.ObjectPosition, skinTransform);	
    OUT.Position = mul(position, WorldViewProjection);
    OUT.WorldPosition = mul(position, World).xyz;
    
    float4 normal = mul(float4(IN.Normal, 0), skinTransform);
    OUT.Normal = normalize(mul(normal, World).xyz);
    
    OUT.TextureCoordinate = IN.TextureCoordinate;

    float3 lightDirection = LightDirection;
    OUT.Attenuation = saturate(1.0f - (length(lightDirection)));

    return OUT;
}

/************* Pixel Shaders *************/

float4 pixel_shader(VS_OUTPUT IN) : SV_Target
{
    float4 OUT = (float4)0;

    float3 lightDirection = LightDirection;
    lightDirection = normalize(lightDirection);

    float3 viewDirection = normalize(CameraPosition - IN.WorldPosition);

    float3 normal = normalize(IN.Normal);
    float n_dot_l = dot(normal, lightDirection);
    float3 halfVector = normalize(lightDirection + viewDirection);
    float n_dot_h = dot(normal, halfVector);

    float4 color = ColorTexture.Sample(ColorSampler, IN.TextureCoordinate);

    float3 ambient = get_vector_color_contribution(AmbientColor, color.rgb);

    OUT.rgb = ambient;
    OUT.a = 1.0f;

    return OUT;
}

/************* Techniques *************/

technique11 main11
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_5_0, vertex_shader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, pixel_shader()));
    }
}