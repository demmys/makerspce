#include "Vertice.hpp"

namespace makerspec{

    Vertice &Vertice::operator=(const Vector3D &v){
        Vector3D::operator=(v);
        return *this;
    }


    Vertice &Vertice::operator-=(const Vector3D &v){
        Vector3D::operator-=(v);
        return *this;
    }

}
