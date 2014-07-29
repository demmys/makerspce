#ifndef makerspec_Mesh_hpp
#define makerspec_Mesh_hpp

#include "Face.hpp"
#include "Vertice.hpp"

namespace makerspec{

    class Mesh{
        public:
            unsigned int numFaces;
            unsigned int numVertices;
            Face *faces;
            Vertice *vertices;
    };

}

#endif
