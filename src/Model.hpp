#ifndef makerspec_Model_hpp
#define makerspec_Model_hpp

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.hpp"

namespace makerspec{

    class Model{
        public:
            Model(Configuration *config, const std::string &filename);
            ~Model();
            Mesh mesh;
            std::vector<unsigned int> *getFacesByNormal(const UnitVector3D &normal);
            std::vector<unsigned int> *getFacesByNormal(float x, float y, float z);
        protected:
            Configuration *config;
        private:
            void init(const aiMesh &mesh);
    };

}

#endif
