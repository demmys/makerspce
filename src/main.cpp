#include "IPhoneCaseModel.hpp"
#include "Parser.hpp"
#include <iostream>
using namespace std;
using namespace makerspec;

int main(int argc, char *argv[]){

    if(argc < 2){
        cerr << "Error: No input file." << endl;
        return EXIT_FAILURE;
    }

    ifstream input(argv[1], ios_base::in);
    if(!input){
        cerr << "Error: Could not open file: " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    Configuration config;
    std::string testfile;
    bool result = Parser::parse(input, testfile, config);

    if(result){
        cout << "loading model " << testfile << "..." << endl;

        IPhoneCaseModel model(&config, testfile);

        cout << "model loaded." << endl
             << "Faces: " << model.mesh.numFaces << endl
             << "Vertices: " << model.mesh.numVertices << endl;

        IPhoneCaseModel::Size size = model.getSize();
        cout << "Case Size: (" << size.width << ", " << size.height << ")" << endl;
    } else{
        cerr << "Error: Parse failed." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
