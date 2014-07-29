#include "IPhoneCaseModel.hpp"
#include <iostream>
using namespace std;
using namespace makerspec;

int main(int argc, char *argv[]){

    Configuration config = Configuration(Configuration::mm, 1, 0.01);

    if(argc > 1){
        cout << "loading model..." << endl;

        IPhoneCaseModel model(&config, string(argv[1]));

        unsigned int i, j;

        cout << "model loaded." << endl
             << "\tmNumFaces: " << model.mesh.numFaces
             << ", mNumVertices: " << model.mesh.numVertices
             << endl;

        for(i = 0; i < model.mesh.numFaces; i++){
            cout << "\tFaces[" << i << "]" << endl
                 << "\t\tnormal: "
                 << model.mesh.faces[i].normal.x << ", "
                 << model.mesh.faces[i].normal.y << ", "
                 << model.mesh.faces[i].normal.z << endl;
            cout << "\t\tindices: "
                 << model.mesh.faces[i].verticeIndices[0] << ", "
                 << model.mesh.faces[i].verticeIndices[1] << ", "
                 << model.mesh.faces[i].verticeIndices[2] << endl;
        }

        for(i = 0; i < model.mesh.numVertices; i++){
            cout << "\tVertices[" << i << "]" << endl
                 << "\t\tcoord: "
                 << model.mesh.vertices[i].x << ", "
                 << model.mesh.vertices[i].y << ", "
                 << model.mesh.vertices[i].z << endl
                 << "\t\tindices: ";
            vector<unsigned int>::iterator k = model.mesh.vertices[i].faceIndices.begin();
            while(k != model.mesh.vertices[i].faceIndices.end()){
                cout << *(k++) << ", ";
            }
            cout << endl;
        }

        vector<unsigned int> yTopInnerFaceIndices = model.getYTopInnerFace();
        cout << "Y Top Inner Faces: " << yTopInnerFaceIndices.size() << endl;
        for(vector<unsigned int>::iterator i = yTopInnerFaceIndices.begin(); i != yTopInnerFaceIndices.end(); i++){
            cout << "Faces[" << *i << "]: " << endl;
            Face &face = model.mesh.faces[*i];
            for(j = 0; j < 3; j++){
                Vertice &vertice = model.mesh.vertices[face.verticeIndices[j]];
                cout << "\tindex[" << j << "] = Vertices[" << face.verticeIndices[j] << "]: "
                    << vertice.x << ", "
                    << vertice.y << ", "
                    << vertice.z << endl;
            }
        }

        vector<unsigned int> yBottomInnerFaceIndices = model.getYBottomInnerFace();
        cout << "Y Bottom Inner Faces: " << yBottomInnerFaceIndices.size() << endl;
        for(vector<unsigned int>::iterator i = yBottomInnerFaceIndices.begin(); i != yBottomInnerFaceIndices.end(); i++){
            cout << "Faces[" << *i << "]: " << endl;
            Face &face = model.mesh.faces[*i];
            for(j = 0; j < 3; j++){
                Vertice &vertice = model.mesh.vertices[face.verticeIndices[j]];
                cout << "\tindex[" << j << "] = Vertices[" << face.verticeIndices[j] << "]: "
                    << vertice.x << ", "
                    << vertice.y << ", "
                    << vertice.z << endl;
            }
        }

        //cerr << "load file " << argv[1] << " failed." << endl;
    } else{
        cerr << "no input file." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
