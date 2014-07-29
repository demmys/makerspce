#include "Vector3D.hpp"

namespace makerspec{

    Vector3D::Vector3D(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector3D::Vector3D(const Vector3D &base){
        this->x = base.x;
        this->y = base.y;
        this->z = base.z;
    }
    Vector3D::Vector3D(const aiVector3D &base){
        this->x = base.x;
        this->y = base.y;
        this->z = base.z;
    }

    float Vector3D::operator[](int index){
        index %= 3;
        if(index == 0){
            return x;
        } else if(index == 1){
            return y;
        } else{
            return z;
        }
    }

    Vector3D &Vector3D::operator=(const Vector3D &v){
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return *this;
    }

    Vector3D &Vector3D::operator+=(const Vector3D &v){
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    }

    Vector3D &Vector3D::operator-=(const Vector3D &v){
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        return *this;
    }

    bool Vector3D::operator==(const Vector3D &v){
        return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
    }

    bool Vector3D::operator!=(const Vector3D &v){
        return !(*this == v);
    }

}
