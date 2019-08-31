#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <string>

namespace pLANG {

    class Interpreter {
        public:
            Interpreter();

            void Parse(const std::string &content);
            void ParseLine(const std::string &line);

        private:

    };

}

#endif