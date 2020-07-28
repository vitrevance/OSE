#include "AssetSystem.h"

namespace OSE {

	AssetSystem* AssetSystem::instance;

	AssetSystem::AssetSystem() {
		this->primitiveTriangle = new StaticMesh();
		this->primitiveTriangle->vertices = new t_float[9]
		{
			-0.5, -0.5, 0,
			0, -0.5, 0,
			0.5, -0.5, 0
		};
		this->primitiveTriangle->indices = new unsigned int[3]
		{
			0, 1, 2
		};
	}

	AssetSystem::~AssetSystem() {

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