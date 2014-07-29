#include "IPhoneCaseModel.hpp"

namespace makerspec{

    IPhoneCaseModel::IPhoneCaseModel(Configuration *config, const std::string &filename) : Model(config, filename){}

    std::vector<unsigned int> &IPhoneCaseModel::getYTopInnerFace(){
        static std::vector<unsigned int> indices;

        if(indices.size() > 0){
            return indices;
        }

        // get all Y minus direction faces
        std::vector<unsigned int> *minusYFaces = getFacesByNormal(0.0, -1.0, 0.0);
        // set interim Y top face to first one
        std::vector<unsigned int>::iterator i = minusYFaces->begin();
        unsigned int verticeIndex = mesh.faces[*i].verticeIndices[0];
        float maximum = mesh.vertices[verticeIndex].y;
        indices.push_back(*i);
        // search top face
        for(i++; i != minusYFaces->end(); i++){
            verticeIndex = mesh.faces[*i].verticeIndices[0];
            float current = mesh.vertices[verticeIndex].y;
            float delta = maximum - current;
            // change maximum
            if(delta < 0){
                maximum = current;
                // clear if the new one is not on the same face
                if(std::abs(delta) > config->getToleranceOfCoord()){
                    indices.clear();
                }
                indices.push_back(*i);
            } else if(std::abs(delta) < config->getToleranceOfCoord()){
                indices.push_back(*i);
            }
        }
        delete minusYFaces;
        return indices;
    }

    std::vector<unsigned int> &IPhoneCaseModel::getYBottomInnerFace(){
        static std::vector<unsigned int> indices;

        if(indices.size() > 0){
            return indices;
        }

        // get all Y plus direction faces
        std::vector<unsigned int> *plusYFaces = getFacesByNormal(0.0, 1.0, 0.0);
        // set interim Y bottom face to first one
        std::vector<unsigned int>::iterator i = plusYFaces->begin();
        unsigned int verticeIndex = mesh.faces[*i].verticeIndices[0];
        float minimum = mesh.vertices[verticeIndex].y;
        indices.push_back(*i);
        // search top face
        for(i++; i != plusYFaces->end(); i++){
            verticeIndex = mesh.faces[*i].verticeIndices[0];
            float current = mesh.vertices[verticeIndex].y;
            float delta = current - minimum;
            // change minimum
            if(delta < 0){
                minimum = current;
                // clear if the new one is not on the same face
                if(std::abs(delta) > config->getToleranceOfCoord()){
                    indices.clear();
                }
                indices.push_back(*i);
            } else if(std::abs(delta) < config->getToleranceOfCoord()){
                indices.push_back(*i);
            }
        }
        delete plusYFaces;
        return indices;
    }

}
