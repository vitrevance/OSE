#ifndef OSE_ASSETSYSTEM_H
#define OSE_ASSETSYSTEM_H

#include <OSE/Core.h>
#include <fstream>
#include <OSE/Blueprints/ShaderProgram.h>

namespace OSE {
	class OSE_API AssetSystem {
	public:
		static AssetSystem* instance;

		AssetSystem();
		~AssetSystem();

		void setAssetDir(string path);

		ShaderProgram loadShader(string shader);

	protected:
		string m_assetDir;
	};
}
#endif