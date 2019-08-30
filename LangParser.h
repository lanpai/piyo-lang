#ifndef __LANG_PARSER_H
#define __LANG_PARSER_H

#include <string>

class LangParser {
    public:
        LangParser();

        void Parse(const std::string &content);
        void ParseLine(const std::string &line);

    private:

};

#endif
