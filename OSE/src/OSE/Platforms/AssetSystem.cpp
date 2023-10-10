#include <OSE/Platforms/AssetSystem.hpp>

#include <assimp/cimport.h>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#ifdef __windows
#include <windows.h>
#endif

namespace OSE {

AssetSystem* AssetSystem::instance;

AssetSystem::AssetSystem() {
}

AssetSystem::~AssetSystem() {
  for (std::pair<const string, StaticMesh*>& it : this->m_staticMeshes) {
    delete it.second;
  }
  for (std::pair<const string, Material*>& it : this->m_materials) {
    delete it.second;
  }
  for (std::pair<const string, Texture*>& it : this->m_textures) {
    delete it.second;
  }
  /*
  for (std::pair<const string, Convex*>& it : this->m_convexes) {
          delete it.second;
  }
  */
}

void AssetSystem::setAssetDir(string path) {
  this->m_assetDir = (std::filesystem::path(this->getRunnableDir()) / path)
                         .make_preferred()
                         .lexically_normal()
                         .string();
}

string AssetSystem::loadRawString(const string& path) {
  std::ifstream ifs(this->m_assetDir + path);
  if (!ifs.good()) {
    OSE_LOG(LOG_OSE_ERROR, "Failed to load asset: " + path);
    return "";
  }
  std::stringstream ss;
  ss << ifs.rdbuf();
  return std::move(ss).str();
}

StaticMesh* AssetSystem::loadStaticMesh(const string& name, string path,
                                        vec4 bottomExtrusion,
                                        vec4 topExtrusion) {
  if (this->m_staticMeshes.count(name) > 0) {
    OSE_LOG(LOG_OSE_ERROR, "AssetSystem: static mesh with name <" + name +
                               "> already exists!");
    return nullptr;
  }
  const aiScene* scene = aiImportFile(
      (this->m_assetDir + path).c_str(),
      aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeGraph |
          aiProcess_OptimizeMeshes | aiProcess_GenUVCoords);
  if (scene) {
    const aiMesh* amesh = scene->mMeshes[0];
    StaticMesh* mesh = new StaticMesh();

    for (int j = 0; j < amesh->mNumFaces || j <= 0; j++) {
      aiFace aface = amesh->mFaces[j];
      Tetrahedron cellBase;

      cellBase.vertex = bottomExtrusion;

      aiVector3D avert = amesh->mVertices[aface.mIndices[0]];
      cellBase.base_1 = vec4(avert.x, avert.y, avert.z, 0) + bottomExtrusion;
      avert = amesh->mVertices[aface.mIndices[1]];
      cellBase.base_2 = vec4(avert.x, avert.y, avert.z, 0) + bottomExtrusion;
      avert = amesh->mVertices[aface.mIndices[2]];
      cellBase.base_3 = vec4(avert.x, avert.y, avert.z, 0) + bottomExtrusion;

      aiVector3D auv = amesh->mTextureCoords[0][aface.mIndices[0]];
      cellBase.uvbase_1 = vec2(auv.x, auv.y);
      auv = amesh->mTextureCoords[0][aface.mIndices[1]];
      cellBase.uvbase_2 = vec2(auv.x, auv.y);
      auv = amesh->mTextureCoords[0][aface.mIndices[2]];
      cellBase.uvbase_3 = vec2(auv.x, auv.y);
      cellBase.uvvertex =
          (cellBase.uvbase_1 + cellBase.uvbase_2 + cellBase.uvbase_3) / 3;

      Tetrahedron cellTop = cellBase;
      cellTop.vertex += topExtrusion - bottomExtrusion;
      cellTop.base_1 += topExtrusion - bottomExtrusion;
      cellTop.base_2 += topExtrusion - bottomExtrusion;
      cellTop.base_3 += topExtrusion - bottomExtrusion;

      std::vector<Tetrahedron> sideCells;
      vec4* base = (vec4*)(&cellBase);
      vec4* top = (vec4*)(&cellTop);
      std::vector<Tetrahedron> sideCell;
      sideCell = cutPrism(base[0], base[4].xy(), base[1], base[4].zw(), base[2],
                          base[5].xy(), top[0], top[4].xy(), top[1],
                          top[4].zw(), top[2], top[5].xy());
      sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());
      sideCell = cutPrism(base[0], base[4].xy(), base[3], base[5].zw(), base[1],
                          base[4].zw(), top[0], top[4].xy(), top[3],
                          top[5].zw(), top[1], top[4].zw());
      sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());
      sideCell = cutPrism(base[0], base[4].xy(), base[2], base[5].xy(), base[3],
                          base[5].zw(), top[0], top[4].xy(), top[2],
                          top[5].xy(), top[3], top[5].zw());
      sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());
      sideCell = cutPrism(base[1], base[4].zw(), base[2], base[5].xy(), base[3],
                          base[5].zw(), top[1], top[4].zw(), top[2],
                          top[5].xy(), top[3], top[5].zw());
      sideCells.insert(sideCells.end(), sideCell.begin(), sideCell.end());

      mesh->cells.push_back(cellBase);
      mesh->cells.push_back(cellTop);
      mesh->cells.insert(mesh->cells.end(), sideCells.begin(), sideCells.end());
    }
    this->m_staticMeshes[name] = mesh;

    aiReleaseImport(scene);

    return mesh;
  } else {
    OSE_LOG(LOG_OSE_ERROR,
            ("Failed to load asset: " + string(aiGetErrorString())));
  }
  return nullptr;
}

StaticMesh* AssetSystem::getStaticMesh(const string& name) {
  return this->m_staticMeshes[name];
}

std::map<string, StaticMesh*>& AssetSystem::getStaticMeshes() {
  return this->m_staticMeshes;
}

std::map<string, Material*>& AssetSystem::getMaterials() {
  return this->m_materials;
}

std::map<string, Texture*>& AssetSystem::getTextures() {
  return this->m_textures;
}

Material* AssetSystem::createMaterial(const string& name, string materialText) {
  if (this->m_materials.count(name) > 0) {
    OSE_LOG(LOG_OSE_ERROR,
            "AssetSystem: material with name <" + name + "> already exists!");
    return nullptr;
  }
  std::string::size_type defloc = materialText.find("material");
  if (defloc == string::npos) {
    OSE_LOG(LOG_OSE_ERROR,
            "AssetSystem: material <" + name + "> : bad format!");
    return nullptr;
  }
  Material* material = new Material(this->m_materials.size() + 1);
  materialText.insert(defloc + 8, std::to_string(material->id));
  unsigned long long texture = materialText.find("#texture ");
  while (texture != string::npos) {
    if (texture > defloc) {
      break;
    }
    unsigned int texEnd = materialText.find('\n', texture + 10);
    string texName = materialText.substr(texture + 9, texEnd - texture - 9);
    material->textures.push_back(texName);
    if (materialText.size() < texEnd + 1) {
      OSE_LOG(LOG_OSE_ERROR,
              "AssetSystem: material <" + name + "> : bad format!");
      delete material;
      return nullptr;
    }
    if (this->m_textures[texName] == nullptr) {
      OSE_LOG(LOG_OSE_WARNING, "AssetSystem: material <" + name +
                                   "> : unresolved reference to texture <" +
                                   texName + "> !");
    }
    materialText = materialText.substr(texEnd + 1);
    texture = materialText.find("#texture ");
  }
  material->text = materialText;
  this->m_materials[name] = material;
  return material;
}

Material* OSE::AssetSystem::loadMaterial(const string& name,
                                         const string& path) {
  string texture_text = AssetSystem::loadRawString(path);
  return AssetSystem::createMaterial(name, texture_text);
}

void AssetSystem::attachMaterial(const string& meshName, string materialName) {
  this->m_meshMaterials[this->m_staticMeshes[meshName]] =
      this->m_materials[materialName];
}

void AssetSystem::attachMaterial(StaticMesh* mesh, Material* material) {
  this->m_meshMaterials[mesh] = material;
}

Material* AssetSystem::getMeshMaterial(StaticMesh* mesh) {
  return this->m_meshMaterials[mesh];
}

Texture* AssetSystem::loadTexture(const string& name, const string& path) {
  if (this->m_textures.count(name) > 0) {
    OSE_LOG(LOG_OSE_ERROR,
            "AssetSystem: texture with name <" + name + "> already exists!");
    return nullptr;
  }
  Texture* texture = new Texture();
  int width, height, channels;
  texture->pixels = stbi_load((this->m_assetDir + path).c_str(), &width,
                              &height, &channels, STBI_rgb_alpha);
  if (texture->pixels == nullptr) {
    delete texture;
    OSE_LOG(LOG_OSE_ERROR, "Failed to load asset : " + path);
    return nullptr;
  }
  texture->width = width;
  texture->height = height;
  this->m_textures[name] = texture;
  return texture;
}

Texture* AssetSystem::getTexture(const string& name) {
  return this->m_textures[name];
}

Convex* AssetSystem::genConvexForMesh(const string& name) {
  StaticMesh* mesh = this->m_staticMeshes[name];
  Convex* result = new Convex();
  for (Tetrahedron& it : mesh->cells) {
    result->vertices.insert(it.base_1);
    result->vertices.insert(it.base_2);
    result->vertices.insert(it.base_3);
  }
  result->parent = mesh;
  this->m_convexes[name] = result;
  return result;
}

Convex* AssetSystem::getConvex(const string& name) {
  return this->m_convexes[name];
}

std::vector<Tetrahedron> AssetSystem::cutPrism(vec4 a1, vec2 u1, vec4 a2,
                                               vec2 u2, vec4 a3, vec2 u3,
                                               vec4 b1, vec2 v1, vec4 b2,
                                               vec2 v2, vec4 b3, vec2 v3) {
  std::vector<Tetrahedron> result;
  Tetrahedron t1;
  t1.vertex = a1;
  t1.base_1 = b1;
  t1.base_2 = b2;
  t1.base_3 = b3;
  t1.uvvertex = u1;
  t1.uvbase_1 = v1;
  t1.uvbase_2 = v2;
  t1.uvbase_3 = v3;
  Tetrahedron t2;
  t2.vertex = a1;
  t2.base_1 = b2;
  t2.base_2 = b3;
  t2.base_3 = a3;
  t2.uvvertex = u1;
  t2.uvbase_1 = v2;
  t2.uvbase_2 = v3;
  t2.uvbase_3 = u3;
  Tetrahedron t3;
  t3.vertex = a1;
  t3.base_1 = a3;
  t3.base_2 = a2;
  t3.base_3 = b2;
  t3.uvvertex = u1;
  t3.uvbase_1 = u3;
  t3.uvbase_2 = u2;
  t3.uvbase_3 = v2;
  result.push_back(t1);
  result.push_back(t2);
  result.push_back(t3);
  return result;
}

string AssetSystem::getRunnableDir() {
  string path;
#ifdef __windows
  char buffer[MAX_PATH];
  GetModuleFileNameA(NULL, buffer, MAX_PATH);
  std::string::size_type pos = std::string(buffer).find_last_of("\\/");
  path = string(buffer).substr(0, pos + 1);
#else
  path = std::filesystem::current_path().string();
#endif
  return path;
}
}  // namespace OSE