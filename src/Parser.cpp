#include "Parser.hpp"
#include <boost/variant/get.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/variant/recursive_variant.hpp>

using namespace boost::spirit;

namespace makerspec{

    // scales
    struct scales_ : qi::symbols<char, Configuration::ScaleUnit>{
        scales_(){
            add
                ("mm", Configuration::mm)
                ("inch", Configuration::inch)
            ;
        };
    } scales;

    // tolerance
    struct Tolerance{
        enum ToleranceType{ deg, mm, inch };
        Tolerance::ToleranceType type;
        float content;
    };
    Tolerance createTolerance(Tolerance::ToleranceType type, float content){
        Tolerance t;
        t.type = type;
        t.content = content;
        return t;
    };

    // directive
    typedef boost::variant<
        std::string,
        Configuration::ScaleUnit,
        std::vector<Tolerance>
    > DirectiveContent;

    struct Directive{
        enum DirectiveType{ subject, scale, tolerances };
        Directive::DirectiveType type;
        DirectiveContent content;
    };

    Directive createDirective(Directive::DirectiveType type, std::string content){
        Directive d;
        d.type = type;
        d.content = content;
        return d;
    };
    Directive createDirective(Directive::DirectiveType type, Configuration::ScaleUnit content){
        Directive d;
        d.type = type;
        d.content = content;
        return d;
    };
    Directive createDirective(Directive::DirectiveType type, std::vector<Tolerance> content){
        Directive d;
        d.type = type;
        d.content = content;
        return d;
    };

    /*
     * makerspec_grammar
     */
    template<typename Iterator>
    struct makerspec_grammar : qi::grammar<Iterator, std::vector<Directive>(), ascii::space_type>{
        makerspec_grammar() : makerspec_grammar::base_type(makerspec){
            using namespace boost::phoenix;
            using namespace qi::labels;
            using qi::_val;
            using qi::lit;
            using qi::float_;
            using qi::lexeme;
            using ascii::char_;
            using ascii::string;

            makerspec %= *directive;

            directive = (lit("#subject") >> text)
                            [_val = bind(static_cast<Directive (*)(Directive::DirectiveType, std::string)>(createDirective), Directive::subject, _1)]
                      | (lit("#scale") >> scales)
                            [_val = bind(static_cast<Directive (*)(Directive::DirectiveType, Configuration::ScaleUnit)>(createDirective), Directive::scale, _1)]
                      | (lit("#tolerance") >> *tolerance)
                            [_val = bind(static_cast<Directive (*)(Directive::DirectiveType, std::vector<Tolerance>)>(createDirective), Directive::tolerances, _1)];

            text %= lexeme['"' >> +(char_ - '"') >> '"'];

            tolerance = lexeme[float_ >> lit("deg")]
                            [_val = bind(createTolerance, Tolerance::deg, _1)]
                      | lexeme[float_ >> lit("mm")]
                            [_val = bind(createTolerance, Tolerance::mm, _1)]
                      | lexeme[float_ >> lit("inch")]
                            [_val = bind(createTolerance, Tolerance::inch, _1)];
        }
        qi::rule<Iterator, std::vector<Directive>(), ascii::space_type> makerspec;
        qi::rule<Iterator, Directive(), ascii::space_type> directive;
        qi::rule<Iterator, std::string(), ascii::space_type> text;
        qi::rule<Iterator, Tolerance(), ascii::space_type> tolerance;
    };



    bool Parser::parse(std::ifstream &input, std::string &testfile, Configuration &config){
        input.unsetf(std::ios::skipws);

        std::string storage;
        std::copy(std::istream_iterator<char>(input), std::istream_iterator<char>(), back_inserter(storage));
        std::string::const_iterator iterator = storage.begin();
        std::string::const_iterator end = storage.end();

        makerspec_grammar<std::string::const_iterator> grammar;
        std::vector<Directive> directives;
        bool result = phrase_parse(iterator, end, grammar, ascii::space, directives);

        if(result && iterator == end){
            Configuration::ScaleUnit unit = Configuration::mm;
            float toleranceOfDegree;
            float toleranceOfMm;
            float toleranceOfInch;
            float toleranceOfCoord;
            std::string filename;
            std::vector<Directive>::iterator i;
            for(i = directives.begin(); i != directives.end(); i++){
                switch(i->type){
                    case Directive::subject:
                        filename = boost::get<std::string>(i->content);
                        break;
                    case Directive::scale:
                        unit = boost::get<Configuration::ScaleUnit>(i->content);
                        break;
                    case Directive::tolerances:
                        std::vector<Tolerance> tolerances = boost::get<std::vector<Tolerance> >(i->content);
                        std::vector<Tolerance>::iterator j;
                        for(j = tolerances.begin(); j != tolerances.end(); j++){
                            switch(j->type){
                                case Tolerance::deg:
                                    toleranceOfDegree = j->content;
                                    break;
                                case Tolerance::mm:
                                    toleranceOfMm = j->content;
                                    break;
                                case Tolerance::inch:
                                    toleranceOfInch = j->content;
                                    break;
                            }
                        }
                        break;
                }
            }
            toleranceOfCoord = unit == Configuration::mm ? toleranceOfMm : toleranceOfInch;
            config = Configuration(unit, toleranceOfDegree, toleranceOfCoord);
            testfile = filename;
            return true;
        } else{
            return false;
        }
    }

}
