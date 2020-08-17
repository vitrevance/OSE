#include "AssetSystem.h"

namespace OSE {

	AssetSystem* AssetSystem::instance;

	AssetSystem::AssetSystem() {
	}

	AssetSystem::~AssetSystem() {
		for (std::pair<const string, StaticMesh*>& it : this->m_staticMeshes) {
			delete it.second;
		}
	}

	void AssetSystem::setAssetDir(string path) {
		this->m_assetDir = path;
	}

	string AssetSystem::loadRawString(string path) {
		std::ifstream ifs(this->m_assetDir + path);
		std::string text((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
		return text;
	}

	StaticMesh* AssetSystem::loadStaticMesh(string name, string path) {
		const aiScene* scene = aiImportFile((this->m_assetDir + path).c_str(),
			aiProcess_Triangulate | aiProcess_PreTransformVertices | aiProcess_GenNormals | aiProcess_OptimizeGraph | aiProcess_OptimizeMeshes);
		if (scene) {

			const aiMesh* amesh = scene->mMeshes[0];
			StaticMesh* mesh = new StaticMesh();

			for (int j = 0; j < amesh->mNumFaces || j <= 1; j++) {
				aiFace aface = amesh->mFaces[j];
				Tetrahedron cellBase;

				cellBase.vertex = vec4(0, 0, 0, -1);

				aiVector3D avert = amesh->mVertices[aface.mIndices[0]];
				cellBase.base_1 = vec4(avert.x, avert.y, avert.z, -1);
				avert = amesh->mVertices[aface.mIndices[1]];
				cellBase.base_2 = vec4(avert.x, avert.y, avert.z, -1);
				avert = amesh->mVertices[aface.mIndices[2]];
				cellBase.base_3 = vec4(avert.x, avert.y, avert.z, -1);

				Tetrahedron cellTop;
				cellTop.vertex = vec4(0, 0, 0, 1);
				cellTop.base_1 = vec4(cellBase.base_1.xyz, 1);
				cellTop.base_2 = vec4(cellBase.base_2.xyz, 1);
				cellTop.base_3 = vec4(cellBase.base_3.xyz, 1);

				std::vector<Tetrahedron> sideCells;
				vec4* base = (vec4*)(&cellBase);
				vec4* top = (vec4*)(&cellTop);
				std::vector<Tetrahedron> sideCell;
				sideCell = cutPrism(base[0], base[1], base[2], top[0], top[1], top[2]);
				sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());
				sideCell = cutPrism(base[0], base[3], base[1], top[0], top[3], top[1]);
				sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());
				sideCell = cutPrism(base[0], base[2], base[3], top[0], top[2], top[3]);
				sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());
				sideCell = cutPrism(base[1], base[2], base[3], top[1], top[2], top[3]);
				sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());

				mesh->cells.push_back(cellBase);
				mesh->cells.push_back(cellTop);
				mesh->cells.insert(mesh->cells.end(), sideCells.begin(), sideCells.end());
			}

			this->m_staticMeshes[name] = mesh;

			aiReleaseImport(scene);

			return mesh;
		}
		else {
			OSE_LOG(LOG_OSE_ERROR, ("Failed to load asset: " + string(aiGetErrorString())))
		}
		return nullptr;
	}

	StaticMesh* AssetSystem::getStaticMesh(string name) {
		return this->m_staticMeshes[name];
	}

	std::map<string, StaticMesh*>& AssetSystem::getStaticMeshes() {
		return this->m_staticMeshes;
	}

	std::vector<Tetrahedron> AssetSystem::cutPrism(vec4 a1, vec4 a2, vec4 a3, vec4 b1, vec4 b2, vec4 b3) {
		std::vector<Tetrahedron> result;
		Tetrahedron t1;
		t1.vertex = a1;
		t1.base_1 = b1;
		t1.base_2 = b2;
		t1.base_3 = b3;
		Tetrahedron t2;
		t2.vertex = a1;
		t2.base_1 = b2;
		t2.base_2 = b3;
		t2.base_3 = a3;
		Tetrahedron t3;
		t3.vertex = a1;
		t3.base_1 = a3;
		t3.base_2 = a2;
		t3.base_3 = b2;
		result.push_back(t1);
		result.push_back(t2);
		result.push_back(t3);
		return result;
	}
}