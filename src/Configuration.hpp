#ifndef makerspec_Configuration_hpp
#define makerspec_Configuration_hpp

namespace makerspec{

    class Configuration{
        public:
            enum ScaleUnit{ mm, inch };
            static Configuration defaultConfiguration;
            Configuration(Configuration::ScaleUnit unit, float toleranceOfDegree, float toleranceOfCoord);
            // getter
            Configuration::ScaleUnit getUnit();
            float getToleranceOfDegree();
            float getToleranceOfCoord();
        private:
            Configuration::ScaleUnit unit;
            // 0 <= toleranceOfDegree < 180
            float toleranceOfDegree;
            float toleranceOfCoord;
    };
}

#endif
