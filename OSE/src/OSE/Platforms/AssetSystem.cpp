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
			unsigned int totalSizeVerts = 0;
			unsigned int totalSizeInds = 0;

			for (int i = 0; i < scene->mNumMeshes; i++) {
				totalSizeVerts += scene->mMeshes[i]->mNumVertices;
				totalSizeInds += scene->mMeshes[i]->mNumFaces * 3;
			}

			unsigned int totalInds4D = totalSizeInds * 2 + totalSizeVerts * 3;
			unsigned int totalVerts4D = totalSizeVerts * 2;

			unsigned int nv = 0, ni = 0;
			Vertex* verts = new Vertex[totalVerts4D];
			unsigned int* inds = new unsigned int[totalInds4D];
			

			for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
				const aiMesh* amesh = scene->mMeshes[i];
				for (unsigned int j = 0; j < amesh->mNumVertices; j++) {
					aiVector3D& vertex = amesh->mVertices[j];
					aiVector3D& normal = amesh->mNormals[j];
					Vertex vert1, vert2;
					vert1.pos[0] = vertex.x;
					vert1.pos[1] = vertex.y;
					vert1.pos[2] = vertex.z;
					vert2.pos[3] = -1;
					vert1.norm[0] = normal.x;
					vert1.norm[1] = normal.y;
					vert1.norm[2] = normal.z;

					vert2.pos[0] = vertex.x;
					vert2.pos[1] = vertex.y;
					vert2.pos[2] = vertex.z;
					vert2.pos[3] = 1;
					vert2.norm[0] = normal.x;
					vert2.norm[1] = normal.y;
					vert2.norm[2] = normal.z;
					vert2.norm[3] = 0;

					verts[nv + totalSizeVerts] = vert2;
					verts[nv] = vert1;

					if (nv % 2 == 0) {
						inds[totalSizeInds * 2 + nv * 3] = nv % totalVerts4D;
						inds[totalSizeInds * 2 + nv * 3 + 2] = (nv + totalSizeVerts + 1) % totalVerts4D;
						inds[totalSizeInds * 2 + nv * 3 + 1] = (nv + totalSizeVerts) % totalVerts4D;
					}
					else {
						inds[totalSizeInds * 2 + nv * 3] = nv % totalVerts4D;
						inds[totalSizeInds * 2 + nv * 3 + 1] = (nv - 1) % totalVerts4D;
						inds[totalSizeInds * 2 + nv * 3 + 2] = (nv + totalSizeVerts + 1) % totalVerts4D;
					}

					nv++;
				}
				for (unsigned int j = 0; j < amesh->mNumFaces; j++) {
					aiFace& face = amesh->mFaces[j];
					inds[ni + totalSizeInds] = face.mIndices[0] + totalSizeVerts;
					inds[ni + totalSizeInds + 1] = face.mIndices[1] + totalSizeVerts;
					inds[ni + totalSizeInds + 2] = face.mIndices[2] + totalSizeVerts;

					inds[ni] = face.mIndices[0];
					inds[ni + 1] = face.mIndices[1];
					inds[ni + 2] = face.mIndices[2];

					ni += 3;
				}
			}

			StaticMesh* mesh = new StaticMesh(verts, totalVerts4D, inds, totalInds4D);
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
}