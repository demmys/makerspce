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
    Condition condition;
    std::string testfile;
    bool result = Parser::parse(input, testfile, config, condition);

    if(result){
        cout << "loading model " << testfile << "..." << endl;

        IPhoneCaseModel model(&config, testfile);

        cout << "model loaded." << endl
             << "Faces: " << model.mesh.numFaces << endl
             << "Vertices: " << model.mesh.numVertices << endl;

        IPhoneCaseModel::Size size = model.getSize();
        cout << "Running all specs..." << endl;
        float width = condition.right.at(0);
        float height = condition.right.at(1);
        if(size.width > width && size.height > height){
            cout << "." << endl;
        } else{
            cout << "Expected width = " << width << ", height = " << height << " but actual is width = " << size.width << ", height = " << size.height << "." << endl;
            return EXIT_FAILURE;
        }
        cout << "All green." << endl;
    } else{
        cerr << "Error: Parse failed." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
