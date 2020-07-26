#ifndef OSE_ASSETSYSTEM_H
#define OSE_ASSETSYSTEM_H

#include <OSE/Core.h>
#include <fstream>
#include <OSE/Systems/Renderer.h>

namespace OSE {
	class OSE_API AssetSystem {
	public:
		static AssetSystem* instance;

		AssetSystem();
		~AssetSystem();

		void setAssetDir(string path);

		string loadRawString(string path);

	protected:
		string m_assetDir;
	};
}
#endif