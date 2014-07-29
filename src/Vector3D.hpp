#ifndef makerspec_Vector3D_hpp
#define makerspec_Vector3D_hpp

#include <assimp/vector3.h>

namespace makerspec{

    class Vector3D{
        public:
            float x;
            float y;
            float z;
            Vector3D(){};
            Vector3D(float x, float y, float z);
            Vector3D(const Vector3D &base);
            Vector3D(const aiVector3D &base);
            float operator[](int index);
            Vector3D &operator=(const Vector3D &v);
            Vector3D &operator+=(const Vector3D &v);
            Vector3D &operator-=(const Vector3D &v);
            bool operator==(const Vector3D &v);
            bool operator!=(const Vector3D &v);
    };

}

#endif
