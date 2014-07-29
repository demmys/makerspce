#include "Model.hpp"

namespace makerspec{

    Model::Model(Configuration *config, const std::string &filename){
        this->config = config;

        // load model
        Assimp::Importer importer;
        const aiScene* pScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

        if(pScene){
            this->init(*(pScene->mMeshes[0]));
        } else{
            // TODO throw InvalidFileException
        }
    }

    Model::~Model(){
        delete[] mesh.faces;
        delete[] mesh.vertices;
    }

    void Model::getFacesByNormal(std::vector<unsigned int> &indices, const UnitVector3D &normal){
        for(unsigned int i = 0; i < mesh.numFaces; i++){
            if(mesh.faces[i].normal == normal){
                indices.push_back(i);
            }
        }
    }

    void Model::getFacesByNormal(std::vector<unsigned int> &indices, float x, float y, float z){
        UnitVector3D normal(config, x, y, z);
        return getFacesByNormal(indices, normal);
    }

    void Model::init(const aiMesh &mesh){
        unsigned int i, j, k, l;
        unsigned int *verticeAliases = new unsigned int[mesh.mNumVertices];

        // initialization
        this->mesh.numFaces = mesh.mNumFaces;
        this->mesh.numVertices = mesh.mNumVertices;
        this->mesh.vertices = new Vertice[mesh.mNumVertices];
        this->mesh.faces = new Face[mesh.mNumFaces];
        for(unsigned int i = 0; i < mesh.mNumFaces; i++){
            this->mesh.faces[i] = Face(config);
        }

        // initialize verticeAliases
        for(i = 0; i < mesh.mNumVertices; i++){
            verticeAliases[i] = i;
        }

        // set vertices
        Vector3D minimum(mesh.mVertices[0]);
        for(i = 0, j = 0; i < mesh.mNumVertices; i++, j++){
            Vector3D vertice(mesh.mVertices[i]);
            // check whether the target vertice already exists
            for(k = 0; k < j; k++){
                if(this->mesh.vertices[k] == vertice){
                    verticeAliases[i] = k;
                    for(l = i + 1; l < mesh.mNumVertices; l++){
                        verticeAliases[l]--;
                    }
                    break;
                }
            }
            if(k == j){
                this->mesh.vertices[j] = vertice;
                if(vertice.x < minimum.x){
                    minimum.x = vertice.x;
                }
                if(vertice.y < minimum.y){
                    minimum.y = vertice.y;
                }
                if(vertice.z < minimum.z){
                    minimum.z = vertice.z;
                }
            } else{
                j--;
                (this->mesh.numVertices)--;
            }
        }

        // set minimum point to origin
        for(i = 0; i < this->mesh.numVertices; i++){
            this->mesh.vertices[i] -= minimum;
        }

        // set faces
        for(i = 0; i < mesh.mNumFaces; i++){
            if(mesh.mFaces[i].mNumIndices > 3){
                // TODO throw TriangulateFailedException
            }

            // set faces[x].verticeIndices & vertices[x].faceIndices
            for(j = 0; j < 3; j++){
                unsigned int index = verticeAliases[mesh.mFaces[i].mIndices[j]];
                this->mesh.faces[i].verticeIndices[j] = index;
                this->mesh.vertices[index].faceIndices.push_back(i);
            }
            // set faces[x].normal
            this->mesh.faces[i].normal = Vector3D(mesh.mNormals[mesh.mFaces[i].mIndices[0]]);
        }

        delete[] verticeAliases;
    }

}
