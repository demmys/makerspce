#ifndef makerspec_Vertice_hpp
#define makerspec_Vertice_hpp

#include <vector>
#include "Vector3D.hpp"

namespace makerspec{

    class Vertice : public Vector3D{
        public:
            std::vector<unsigned int> faceIndices;
            Vertice &operator=(const Vector3D &v);
            Vertice &operator-=(const Vector3D &v);
    };

}

#endif
