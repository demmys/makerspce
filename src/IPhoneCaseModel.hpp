#ifndef makerspec_IPhoneCaseModel_hpp
#define makerspec_IPhoneCaseModel_hpp

#include "Model.hpp"

namespace makerspec{

    class IPhoneCaseModel : public Model{
        public:
            struct Size{
                float width;
                float height;
            };
            IPhoneCaseModel(Configuration *config, const std::string &filename);
            IPhoneCaseModel::Size &getSize();
        private:
            void getXYInwallFaces(std::vector<unsigned int> &indices, UnitVector3D &normal);
    };
}

#endif
