#include "include\\Common.fxh"

#define MaxBones 120

/************* Resources *************/
cbuffer CBufferPerFrame
{
	float4 AmbientColor = { 1.0f, 1.0f, 1.0f, 0.0f };
		float4 LightColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		float3 LightPosition = { 0.0f, 0.0f, 0.0f };
		float3 LightDirection = { 0.0f, 0.0f, 0.0f };
		float LightRadius = 10.0f;
	float3 LightLookAt = { 0.0f, 0.0f, 0.0f };
		float SpotLightOuterAngle = { 0.0f };
	float SpotLightInnerAngle = { 0.0f };
	float3 CameraPosition;
}

cbuffer CBufferPerObject
{
	float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
	float4x4 World : WORLD;
	float4 SpecularColor : SPECULAR = { 1.0f, 1.0f, 1.0f, 1.0f };
	float SpecularPower : SPECULARPOWER = 25.0f;
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

extern int numLights : register(c0);
POINT_LIGHT PointLights[2];

struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float3 Normal : NORMAL;
	float2 TextureCoordinate : TEXCOORD0;
	float3 WorldPosition : TEXCOORD1;
	float Attenuation : TEXCOORD2;
	float3 LightDirection : TEXCOORD3;
	float3 LightLookAt : TEXCOORD4;
};
/*************** Point Light ***************/
/************* Vertex Shader *************/

VS_OUTPUT vertex_shaderPL( VS_INPUT IN )
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;

	float4x4 skinTransform = (float4x4)0;
		skinTransform += BoneTransforms[IN.BoneIndices.x] * IN.BoneWeights.x;
	skinTransform += BoneTransforms[IN.BoneIndices.y] * IN.BoneWeights.y;
	skinTransform += BoneTransforms[IN.BoneIndices.z] * IN.BoneWeights.z;
	skinTransform += BoneTransforms[IN.BoneIndices.w] * IN.BoneWeights.w;

	float4 position = mul( IN.ObjectPosition, skinTransform );
		OUT.Position = mul( position, WorldViewProjection );
	OUT.WorldPosition = mul( position, World ).xyz;

	float4 normal = mul( float4(IN.Normal, 0), skinTransform );
		OUT.Normal = normalize( mul( normal, World ).xyz );

	OUT.TextureCoordinate = IN.TextureCoordinate;

	float3 lightDirection = LightPosition - OUT.WorldPosition;
		OUT.Attenuation = saturate( 1.0f - (length( lightDirection ) / LightRadius) );

	return OUT;
}

/************* Pixel Shaders *************/

float4 pixel_shaderPL( VS_OUTPUT IN ) : SV_Target
{
	float4 OUT = (float4)0;

	float3 lightDirection = LightPosition - IN.WorldPosition;
	lightDirection = normalize( lightDirection );

	float3 viewDirection = normalize( CameraPosition - IN.WorldPosition );

		float3 normal = normalize( IN.Normal );
		float n_dot_l = dot( normal, lightDirection );
	float3 halfVector = normalize( lightDirection + viewDirection );
		float n_dot_h = dot( normal, halfVector );

	float4 color = ColorTexture.Sample( ColorSampler, IN.TextureCoordinate );
		float4 lightCoefficients = lit( n_dot_l, n_dot_h, SpecularPower );

		float3 ambient = get_vector_color_contribution( AmbientColor, color.rgb );
		float3 diffuse = get_vector_color_contribution( LightColor, lightCoefficients.y * color.rgb ) * IN.Attenuation;
		float3 specular = get_scalar_color_contribution( SpecularColor, min( lightCoefficients.z, color.w ) ) * IN.Attenuation;

		LIGHT_CONTRIBUTION_DATA lightContributionData;
	lightContributionData.Color = color;
	lightContributionData.Normal = normal;
	lightContributionData.ViewDirection = viewDirection;
	lightContributionData.SpecularColor = SpecularColor;
	lightContributionData.SpecularPower = SpecularPower;

	float3 totalLightContribution = (float3)0;

		for ( int i = 0; i < 1; i++ )
		{
			lightContributionData.LightDirection = get_light_data( PointLights[i].Position, IN.WorldPosition, PointLights[i].LightRadius );
			lightContributionData.LightColor = PointLights[i].Color;
			totalLightContribution += get_light_contribution( lightContributionData );
		}


	OUT.rgb = ambient + diffuse + specular + totalLightContribution;
	OUT.a = 1.0f;

	return OUT;
}
float4 pixel_shaderPLW( VS_OUTPUT IN ) : SV_Target
{
	float4 OUT = (float4)0;

	float3 lightDirection = LightPosition - IN.WorldPosition;
	lightDirection = normalize( lightDirection );

	float3 viewDirection = normalize( CameraPosition - IN.WorldPosition );

		float3 normal = normalize( IN.Normal );
		float n_dot_l = dot( normal, lightDirection );
	float3 halfVector = normalize( lightDirection + viewDirection );
		float n_dot_h = dot( normal, halfVector );

	float4 color = ColorTexture.Sample( ColorSampler, IN.TextureCoordinate );
		float4 lightCoefficients = lit( n_dot_l, n_dot_h, SpecularPower );

		float3 ambient = get_vector_color_contribution( AmbientColor, color.rgb );
		float3 diffuse = get_vector_color_contribution( LightColor, lightCoefficients.y * color.rgb ) * IN.Attenuation;
		float3 specular = get_scalar_color_contribution( SpecularColor, min( lightCoefficients.z, color.w ) ) * IN.Attenuation;

		LIGHT_CONTRIBUTION_DATA lightContributionData;
	lightContributionData.Color = color;
	lightContributionData.Normal = normal;
	lightContributionData.ViewDirection = viewDirection;
	lightContributionData.SpecularColor = SpecularColor;
	lightContributionData.SpecularPower = SpecularPower;

	float3 totalLightContribution = (float3)0;

		for ( int i = 0; i < 2; i++ )
		{
			lightContributionData.LightDirection = get_light_data( PointLights[i].Position, IN.WorldPosition, PointLights[i].LightRadius );
			lightContributionData.LightColor = PointLights[i].Color;
			totalLightContribution += get_light_contribution( lightContributionData );
		}


	OUT.rgb = ambient + diffuse + specular + totalLightContribution;
	OUT.a = 1.0f;

	return OUT;
}

/********** DirectionalLight **********/
/************* Vertex Shader *************/

VS_OUTPUT vertex_shaderDL( VS_INPUT IN )
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;

	float4x4 skinTransform = (float4x4)0;
		skinTransform += BoneTransforms[IN.BoneIndices.x] * IN.BoneWeights.x;
	skinTransform += BoneTransforms[IN.BoneIndices.y] * IN.BoneWeights.y;
	skinTransform += BoneTransforms[IN.BoneIndices.z] * IN.BoneWeights.z;
	skinTransform += BoneTransforms[IN.BoneIndices.w] * IN.BoneWeights.w;

	float4 position = mul( IN.ObjectPosition, skinTransform );
		OUT.Position = mul( position, WorldViewProjection );

	float4 normal = mul( float4(IN.Normal, 0), skinTransform );
		OUT.Normal = normalize( mul( normal, World ).xyz );

	OUT.TextureCoordinate = IN.TextureCoordinate;

	float3 lightDirection = LightDirection;
		OUT.LightDirection = normalize( -lightDirection );

	return OUT;
}

/************* Pixel Shaders *************/

float4 pixel_shaderDL( VS_OUTPUT IN ) : SV_Target
{
	float4 OUT = (float4)0;

	float3 normal = normalize( IN.Normal );
	float3 lightDir = IN.LightDirection;
	float3 lightDirection = normalize( lightDir );
	float n_dot_l = dot( lightDirection, normal );

	float4 color = ColorTexture.Sample( ColorSampler, IN.TextureCoordinate );
		float3 ambient = AmbientColor.rgb * AmbientColor.a * color.rgb;

		float3 diffuse = (float3)0;

		if ( n_dot_l > 0 )
		{
			diffuse = LightColor.rgb * LightColor.a * n_dot_l * color.rgb;
		}

	OUT.rgb = ambient + diffuse;
	OUT.a = color.a;

	return OUT;
}

/************* Spot Light *************/
/************* Vertex Shader *************/

VS_OUTPUT vertex_shaderSL( VS_INPUT IN )
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;

	float4x4 skinTransform = (float4x4)0;
		skinTransform += BoneTransforms[IN.BoneIndices.x] * IN.BoneWeights.x;
	skinTransform += BoneTransforms[IN.BoneIndices.y] * IN.BoneWeights.y;
	skinTransform += BoneTransforms[IN.BoneIndices.z] * IN.BoneWeights.z;
	skinTransform += BoneTransforms[IN.BoneIndices.w] * IN.BoneWeights.w;

	float4 position = mul( IN.ObjectPosition, skinTransform );
		OUT.Position = mul( position, WorldViewProjection );
	float4 normal = mul( float4(IN.Normal, 0), skinTransform );
		OUT.Normal = normalize( mul( normal, World ).xyz );
	OUT.WorldPosition = mul( IN.ObjectPosition, World ).xyz;
	OUT.TextureCoordinate = get_corrected_texture_coordinate( IN.TextureCoordinate );

	float3 lightDirection = LightPosition - OUT.WorldPosition;
		OUT.Attenuation = saturate( 1.0f - length( lightDirection ) / LightRadius );

	OUT.LightLookAt = -LightLookAt;

	return OUT;
}

/************* Pixel Shader *************/

float4 pixel_shaderSL( VS_OUTPUT IN ) : SV_Target
{
	float4 OUT = (float)0;

	float3 lightDirection = normalize( LightPosition - IN.WorldPosition );
	float3 viewDirection = normalize( CameraPosition - IN.WorldPosition );

	float3 normal = normalize( IN.Normal );
	float n_dot_l = dot( normal, lightDirection );
	float3 halfVector = normalize( lightDirection + viewDirection );
		float n_dot_h = dot( normal, halfVector );
	float3 lightLookAt = normalize( IN.LightLookAt );

		float4 color = ColorTexture.Sample( ColorSampler, IN.TextureCoordinate );
		float4 lightCoefficients = lit( n_dot_l, n_dot_h, SpecularPower );

		float3 ambient = get_vector_color_contribution( AmbientColor, color.rgb );
		float3 diffuse = get_vector_color_contribution( LightColor, lightCoefficients.y * color.rgb ) * IN.Attenuation;
		float3 specular = get_scalar_color_contribution( SpecularColor, min( lightCoefficients.z, color.w ) ) * IN.Attenuation;

		float spotFactor = 0.0f;
	float lightAngle = dot( lightLookAt, lightDirection );
	if ( lightAngle > 0.0f )
	{
		spotFactor = smoothstep( SpotLightOuterAngle, SpotLightInnerAngle, lightAngle );
	}


	OUT.rgb = (ambient + (spotFactor * (diffuse + specular)));// + totalLightContribution;
	OUT.a = 1.0f;

	return OUT;
}



/************* Techniques *************/

technique11 main11
{
	pass p0
	{
		SetVertexShader( CompileShader(vs_5_0, vertex_shaderPL()) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader(ps_5_0, pixel_shaderPL()) );
	}
	pass p1
	{
		SetVertexShader( CompileShader(vs_5_0, vertex_shaderDL()) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader(ps_5_0, pixel_shaderDL()) );
	}
	pass p2
	{
		SetVertexShader( CompileShader(vs_5_0, vertex_shaderSL()) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader(ps_5_0, pixel_shaderSL()) );
	}
	pass p4
	{
		SetVertexShader( CompileShader(vs_5_0, vertex_shaderPL()) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader(ps_5_0, pixel_shaderPLW()) );
	}
}