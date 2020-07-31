#include "AssetSystem.h"

namespace OSE {

	AssetSystem* AssetSystem::instance;

	AssetSystem::AssetSystem() {
		float* vertices = new float[9]
		{
			-0.5, -0.5, 0,
			0, 0.5, 0,
			0.5, -0.5, 0
		};
		unsigned int* indices = new unsigned int[3]{ 0, 1, 2 };
		this->primitiveTriangle = new StaticMesh(vertices, 9, indices, 3);
		/*
		vertices = new float[72]
		{
		-1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
		1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
		-1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
		-1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
		-1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
		};
		*/
		vertices = new float[24]
		{
			-1, -1, -1,
			1, -1, -1,
			1, 1, -1,
			-1, 1, -1,
			-1, -1, 1,
			1, -1, 1,
			1, 1, 1,
			-1, 1, 1
		};

		indices = new unsigned int[36]
		{
			0, 1, 3, 3, 1, 2,
			1, 5, 2, 2, 5, 6,
			5, 4, 6, 6, 4, 7,
			4, 0, 7, 7, 0, 3,
			3, 2, 7, 7, 2, 6,
			4, 5, 0, 0, 5, 1
		};
		this->primitiveCube = new StaticMesh(vertices, 24, indices, 36);
	}

	AssetSystem::~AssetSystem() {
		delete this->primitiveTriangle;
		delete this->primitiveCube;
	}

	void AssetSystem::setAssetDir(string path) {
		this->m_assetDir = path;
	}

	string AssetSystem::loadRawString(string path) {
		std::ifstream ifs(this->m_assetDir + path);
		std::string text((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		return text;
	}
}