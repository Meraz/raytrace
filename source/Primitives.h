#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define SPHERE_COUNT 3
#define TRIANGLE_COUNT 5

namespace CustomPrimitiveStruct
{
	using namespace DirectX;

	struct EachFrameDataStructure	// This struct should be moved out of here. // TODO : Fix
	{
		XMFLOAT4	cameraPosition;
		XMMATRIX	inverseProjection;
		XMMATRIX	inverseView;	
		float screenWidth;
		float screenHeight;
		float padding1;
		float padding2;
	};

	struct Material
	{
		float ambient;
		float specular;
		float diffuse;
		float shininess;		
		float reflectiveFactor;
		float refractiveFactor;
		int isReflective;
		int isRefractive;
	};

	struct SphereStruct
	{
		XMFLOAT4	MidPosition;
		XMFLOAT3	Color;
		float		Radius;
		Material	Material;
	};

	struct TriangleStruct
	{
		XMFLOAT4	Position0;
		XMFLOAT4	Position1;
		XMFLOAT4	Position2;
		XMFLOAT4	Color;
		Material	Material;
	};

	struct Primitive
	{
		SphereStruct		Sphere[SPHERE_COUNT];
		TriangleStruct		Triangle[TRIANGLE_COUNT];
		float SphereCount;
		float TriangleCount;
		float padding1;
		float padding2;
	};
}

#endif