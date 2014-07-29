#include "IPhoneCaseModel.hpp"

namespace makerspec{

    IPhoneCaseModel::IPhoneCaseModel(Configuration *config, const std::string &filename) : Model(config, filename){}

    IPhoneCaseModel::Size &IPhoneCaseModel::getSize(){
        static IPhoneCaseModel::Size size;

        if(size.width){
            return size;
        }

        float xTop, xBottom, yTop, yBottom;
        std::vector<unsigned int> xTopFaces, xBottomFaces, yTopFaces, yBottomFaces;
        UnitVector3D xNormal(config, -1.0, 0.0, 0.0), yNormal(config, 0.0, -1.0, 0.0);

        getXYInwallFaces(xTopFaces, xNormal);
        getXYInwallFaces(xBottomFaces, -xNormal);
        getXYInwallFaces(yTopFaces, yNormal);
        getXYInwallFaces(yBottomFaces, -yNormal);

        xTop = mesh.vertices[mesh.faces[xTopFaces[0]].verticeIndices[0]].x;
        xBottom = mesh.vertices[mesh.faces[xBottomFaces[0]].verticeIndices[0]].x;
        yTop = mesh.vertices[mesh.faces[yTopFaces[0]].verticeIndices[0]].y;
        yBottom = mesh.vertices[mesh.faces[yBottomFaces[0]].verticeIndices[0]].y;

        if(xTop > yTop){
            size.width = xTop - xBottom;
            size.height = yTop - yBottom;
        } else{
            size.width = yTop - yBottom;
            size.height = xTop - xBottom;
        }

        return size;
    }

    void IPhoneCaseModel::getXYInwallFaces(std::vector<unsigned int> &indices, UnitVector3D &normal){
        int searchMax = 1, xInwall = std::abs(normal.y);
        if(normal.x > 0 || normal.y > 0){
            searchMax = -1;
        }
        // get candidates
        std::vector<unsigned int> candidates;
        getFacesByNormal(candidates, normal);
        // set first one to interim target
        std::vector<unsigned int>::iterator i = candidates.begin();
        unsigned int verticeIndex = mesh.faces[*i].verticeIndices[0];
        float interimCoord = mesh.vertices[verticeIndex][xInwall];
        indices.push_back(*i);
        // search correct coord
        for(i++; i != candidates.end(); i++){
            verticeIndex = mesh.faces[*i].verticeIndices[0];
            float current = mesh.vertices[verticeIndex][xInwall];
            float delta = searchMax * (interimCoord - current);
            // change interim coord
            if(delta < 0){
                interimCoord = current;
                // clear if the new one is not on the same face
                if(std::abs(delta) > config->getToleranceOfCoord()){
                    indices.clear();
                }
                indices.push_back(*i);
            } else if(std::abs(delta) < config->getToleranceOfCoord()){
                indices.push_back(*i);
            }
        }
    }

}
