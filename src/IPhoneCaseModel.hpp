#ifndef makerspec_IPhoneCaseModel_hpp
#define makerspec_IPhoneCaseModel_hpp

#include "Model.hpp"

namespace makerspec{

    class IPhoneCaseModel : public Model{
        public:
            IPhoneCaseModel(Configuration *config, const std::string &filename);
            std::vector<unsigned int> &getYTopInnerFace();
            std::vector<unsigned int> &getYBottomInnerFace();
            std::vector<unsigned int> &getXTopInnerFace();
            std::vector<unsigned int> &getXBottomInnerFace();
    };
}

#endif
