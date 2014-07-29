#ifndef makerspec_Face_hpp
#define makerspec_Face_hpp

#include "UnitVector3D.hpp"

namespace makerspec{

    class Face{
        public:
            UnitVector3D normal;
            unsigned int verticeIndices[3];
            Face(){};
            Face(Configuration *config);
    };

}

#endif
