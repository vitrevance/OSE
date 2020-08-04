#ifndef OSE_ASSETSYSTEM_H
#define OSE_ASSETSYSTEM_H

#include <OSE/Core.h>
#include <fstream>
#include <OSE/Systems/Renderer.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

namespace OSE {
	class OSE_API AssetSystem {
	public:
		static AssetSystem* instance;

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