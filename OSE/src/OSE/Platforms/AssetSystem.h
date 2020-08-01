#ifndef OSE_ASSETSYSTEM_H
#define OSE_ASSETSYSTEM_H

#include <OSE/Core.h>
#include <fstream>
#include <OSE/Systems/Renderer.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace OSE {
	class OSE_API AssetSystem {
	public:
		static AssetSystem* instance;

		StaticMesh* primitiveTriangle;
		StaticMesh* primitiveCube;

		AssetSystem();
		~AssetSystem();

		void setAssetDir(string path);

		string loadRawString(string path);

		StaticMesh* loadStaticMesh(string name, string path);

		StaticMesh* getStaticMesh(string name);

		std::map<string, StaticMesh*>& getStaticMeshes();


	protected:
		string m_assetDir;
		std::map<string, StaticMesh*> m_staticMeshes;
	};
}
#endif