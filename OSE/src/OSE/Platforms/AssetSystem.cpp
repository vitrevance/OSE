#include "AssetSystem.h"

namespace OSE {

	AssetSystem* AssetSystem::instance;

	AssetSystem::AssetSystem() {

	}

	AssetSystem::~AssetSystem() {

	}

	void AssetSystem::setAssetDir(string path) {
		this->m_assetDir = path;
	}

	ShaderProgram AssetSystem::loadShader(string shader) {
		std::ifstream fvert(this->m_assetDir + shader + ".vert");
		fvert.seekg(0, std::ios::end);
		std::size_t size = fvert.tellg();
		string textv(size, ' ');
		fvert.read(&textv[0], size);
		fvert.close();

		std::ifstream ffrag(this->m_assetDir + shader + ".frag");
		ffrag.seekg(0, std::ios::end);
		size = ffrag.tellg();
		string textf(size, ' ');
		ffrag.read(&textf[0], size);
		ffrag.close();

		return ShaderProgram(textv, textf);
	}
}