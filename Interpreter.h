#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <string>
#include <vector>

#include "Scope.h"

namespace pLang {

    enum class TokenType {
        VALUE, // Default TokenType
        IDENTIFIER,
        TYPE,

        // TYPES
        INT,
        FLOAT,
        DOUBLE,
        STRING,

        // OPERATORS
        EQUAL,
        ADD,
        SUB,
        MULT,
        DIV,
        ADD_EQUAL,
        SUB_EQUAL,
        MULT_EQUAL,
        DIV_EQUAL,

        // MISC
        WRAPPER,
        TERMINATOR
    };

    struct Token {
        Token(TokenType type, const std::string &value) {
            this->type = type;
            this->value = value;
        }
        TokenType type;
        std::string value;
    };

    class Interpreter {
        public:
            Interpreter();

            void Parse(const std::string &content);
            void ParseLine(const std::vector<Token> &tokens, Scope &scope);
            Value ParseValue(const std::vector<Token> &tokens);
    };

}

#endif
