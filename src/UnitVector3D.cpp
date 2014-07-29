#include "UnitVector3D.hpp"

namespace makerspec{

    UnitVector3D::UnitVector3D(){
        this->config = &Configuration::defaultConfiguration;
    }
    UnitVector3D::UnitVector3D(Configuration *config){
        this->config = config;
    }
    UnitVector3D::UnitVector3D(Configuration *config, float x, float y, float z) : Vector3D(x, y, z){
        this->config = config;
    }

    UnitVector3D &UnitVector3D::operator=(const Vector3D &v){
        Vector3D::operator=(v);
        return *this;
    }

    bool UnitVector3D::operator==(const UnitVector3D &v){
        float dx = std::abs(this->x - v.x);
        float dy = std::abs(this->y - v.y);
        float dz = std::abs(this->z - v.z);
        if(dx == 0 && dy == 0 && dz == 0){
            return true;
        }
        float d = dx * dx + dy * dy + dz * dz;
        float tolerance = std::cos((config->getToleranceOfDegree() / 180) * M_PI);
        if(1 - (d / 2) > tolerance){
            return true;
        }
        return false;
    }

    bool UnitVector3D::operator!=(const UnitVector3D &v){
        return !(*this == v);
    }

}
