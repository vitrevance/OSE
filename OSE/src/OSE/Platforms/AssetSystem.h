#ifndef OSE_ASSETSYSTEM_H
#define OSE_ASSETSYSTEM_H

#include <OSE/Core.h>
#include <fstream>
#include <OSE/Systems/Renderer.h>
#include <OSE/Blueprints/Material.h>
#include <OSE/Blueprints/Texture.h>
#include <OSE/Blueprints/Convex.h>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/material.h>

#ifdef WIN64
namespace PLATFORM_WIN64 {
#include <Windows.h>
}
#endif

namespace OSE {
	class OSE_API AssetSystem {
	public:
		static AssetSystem* instance;

		AssetSystem();
		~AssetSystem();

		void setAssetDir(string path);

		string loadRawString(const string& path);
		//STATIC MESH
		StaticMesh* loadStaticMesh(const string& name, string path, vec4 bottomExtrusion = vec4(0, 0, 0, -1), vec4 topExtrusion = vec4(0, 0, 0, 1));
		StaticMesh* getStaticMesh(const string& name);
		//MATERIAL
		Material* createMaterial(const string& name, string materialText);
		void attachMaterial(const string& meshName, string materialName);
		void attachMaterial(StaticMesh* mesh, Material* material);
		Material* getMeshMaterial(StaticMesh* mesh);
		//TEXTURE
		Texture* loadTexture(const string& name, const string& path);
		Texture* getTexture(const string& name);
		//MESH CONVEX
		Convex* genConvexForMesh(const string& name);
		Convex* getConvex(const string& name);

		std::map<string, StaticMesh*>& getStaticMeshes();
		std::map<string, Material*>& getMaterials();
		std::map<string, Texture*>& getTextures();

	protected:
		string m_assetDir;
		std::map<string, StaticMesh*> m_staticMeshes;
		std::map<string, Material*> m_materials;
		std::map<StaticMesh*, Material*> m_meshMaterials;
		std::map<string, Texture*> m_textures;
		std::map<string, Convex*> m_convexes;
		
		std::vector<Tetrahedron> cutPrism(vec4 a1, vec2 u1, vec4 a2, vec2 u2, vec4 a3, vec2 u3, vec4 b1, vec2 v1, vec4 b2, vec2 v2, vec4 b3, vec2 v3);

		string getRunnableDir();
	};
}
#endif