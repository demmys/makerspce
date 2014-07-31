#ifndef makerspec_Parser_hpp
#define makerspec_Parser_hpp

#include <vector>
#include <fstream>
#include <iostream>
#include "Configuration.hpp"

namespace makerspec{

    // condition
    struct Condition{
        enum Operator{ biggerThan, lessThan };
        std::vector<std::string> left;
        Condition::Operator op;
        std::vector<float> right;
    };

    class Parser{
        public:
            static bool parse(std::ifstream &input, std::string &testfile, Configuration &config, Condition &condition);
    };


}

#endif
