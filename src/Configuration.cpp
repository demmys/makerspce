#include "Configuration.hpp"

namespace makerspec{

    Configuration Configuration::defaultConfiguration = Configuration(Configuration::mm, 1.0, 0.01);

    Configuration::Configuration(Configuration::ScaleUnit unit, float toleranceOfDegree, float toleranceOfCoord){
        this->unit = unit;
        this->toleranceOfDegree = toleranceOfDegree;
        this->toleranceOfCoord = toleranceOfCoord;
    }

    /*
     * Getter
     */
    Configuration::ScaleUnit Configuration::getUnit(){
        return this->unit;
    }
    float Configuration::getToleranceOfDegree(){
        return this->toleranceOfDegree;
    }
    float Configuration::getToleranceOfCoord(){
        return this->toleranceOfCoord;
    }

}
