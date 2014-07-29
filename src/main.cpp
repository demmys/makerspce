#include "IPhoneCaseModel.hpp"
#include <iostream>
using namespace std;
using namespace makerspec;

int main(int argc, char *argv[]){

    Configuration config = Configuration(Configuration::mm, 1, 0.01);

    if(argc > 1){
        cout << "loading model..." << endl;

        IPhoneCaseModel model(&config, string(argv[1]));

        cout << "model loaded." << endl
             << "Faces: " << model.mesh.numFaces << endl
             << "Vertices: " << model.mesh.numVertices << endl;

        IPhoneCaseModel::Size size = model.getSize();
        cout << "Case Size: (" << size.width << ", " << size.height << ")" << endl;

        //cerr << "load file " << argv[1] << " failed." << endl;
    } else{
        cerr << "no input file." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
