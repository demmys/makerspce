#ifndef makerspec_Edge_hpp
#define makerspec_Edge_hpp

#include <vector>

namespace makerspec{

    class Edge{
        unsigned int verticeIndices[2];
        std::vector<unsigned int> faceIndices;
    }

}

#endif
