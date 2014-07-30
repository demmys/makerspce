#ifndef makerspec_Parser_hpp
#define makerspec_Parser_hpp

#include <vector>
#include <fstream>
#include "Configuration.hpp"

namespace makerspec{

    class Parser{
        public:
            static bool parse(std::ifstream &input, std::string &testfile, Configuration &config);
    };

}

#endif
