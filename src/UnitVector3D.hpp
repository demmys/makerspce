#ifndef makerspec_UnitVector3D_hpp
#define makerspec_UnitVector3D_hpp

#define _USE_MATH_DEFINES
#include <cmath>
#include "Configuration.hpp"
#include "Vector3D.hpp"

namespace makerspec{

    class UnitVector3D : public Vector3D{
        public:
            UnitVector3D();
            UnitVector3D(Configuration *config);
            UnitVector3D(Configuration *config, float x, float y, float z);
            UnitVector3D &operator=(const Vector3D &v);
            UnitVector3D &operator-();
            bool operator==(const UnitVector3D &v);
            bool operator!=(const UnitVector3D &v);
        private:
            Configuration *config;
    };

}

#endif
