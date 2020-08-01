#include "AssetSystem.h"

namespace OSE {

	AssetSystem* AssetSystem::instance;

	AssetSystem::AssetSystem() {
		/*
		float* vertices = new float[9]
		{
			-0.5, -0.5, 0,
			0, 0.5, 0,
			0.5, -0.5, 0
		};
		unsigned int* indices = new unsigned int[3]{ 0, 1, 2 };
		this->primitiveTriangle = new StaticMesh(vertices, 9, indices, 3);
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
		*/
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

	StaticMesh* AssetSystem::loadStaticMesh(string name, string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile((this->m_assetDir + path).c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

		if (scene) {
			unsigned int totalSizeVerts = 0;
			unsigned int totalSizeInds = 0;

			for (int i = 0; i < scene->mNumMeshes; i++) {
				totalSizeVerts += scene->mMeshes[i]->mNumVertices;
				totalSizeInds += scene->mMeshes[i]->mNumFaces * 3;
			}

			unsigned int nv = 0, ni = 0;
			Vertex* verts = new Vertex[totalSizeVerts];
			unsigned int* inds = new unsigned int[totalSizeInds];

			for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
				const aiMesh* amesh = scene->mMeshes[i];
				for (unsigned int j = 0; j < amesh->mNumVertices; j++) {
					aiVector3D& vertex = amesh->mVertices[j];
					aiVector3D& normal = amesh->mNormals[j];
					Vertex vert;
					vert.x = vertex.x;
					vert.y = vertex.y;
					vert.z = vertex.z;
					vert.normx = normal.x;
					vert.normy = normal.y;
					vert.normz = normal.z;
					verts[nv++] = vert;
				}
				for (unsigned int j = 0; j < amesh->mNumFaces; j++) {
					aiFace& face = amesh->mFaces[j];
					inds[ni++] = face.mIndices[0];
					inds[ni++] = face.mIndices[1];
					inds[ni++] = face.mIndices[2];
				}
			}

			StaticMesh* mesh = new StaticMesh(verts, totalSizeVerts, inds, totalSizeInds);
			this->m_staticMeshes[name] = mesh;
			return mesh;
		}
		else {
			OSE_LOG(LOG_OSE_ERROR, ("Failed to load asset: " + string(importer.GetErrorString())))
		}
		return nullptr;
	}

	StaticMesh* AssetSystem::getStaticMesh(string name) {
		return this->m_staticMeshes[name];
	}

	std::map<string, StaticMesh*>& AssetSystem::getStaticMeshes() {
		return this->m_staticMeshes;
	}
}