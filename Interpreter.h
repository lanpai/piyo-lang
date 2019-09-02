#ifndef __INTERPRETER_H
#define __INTERPRETER_H

#include <string>
#include <vector>
#include <assert.h>

#include "Scope.h"

namespace pLang {

    enum class TokenType {
        VOID, // Default TokenType
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
        MOD,
        ADD_EQUAL,
        SUB_EQUAL,
        MULT_EQUAL,
        DIV_EQUAL,
        MOD_EQUAL,

        // MISC
        WRAPPER,
        TERMINATOR
    };

    struct Token {
        Token(TokenType type, const std::string &value) {
            this->type = type;
            this->token = value;
            switch (type) {
                case TokenType::INT:
                    this->value = new Value((int)std::stoi(value));
                    break;
                case TokenType::FLOAT:
                    this->value = new Value((float)std::stof(value));
                    break;
                case TokenType::DOUBLE:
                    this->value = new Value((double)std::stod(value));
                    break;
                case TokenType::STRING:
                    this->value = new Value((std::string)value);
                    break;
                default:
                    this->value = nullptr;
                    break;
            }
        }
        Token(int value) {
            this->type = TokenType::STRING;
            this->token = std::to_string(value);
            this->value = new Value((int)value);
        }
        Token(float value) {
            this->type = TokenType::STRING;
            this->token = std::to_string(value);
            this->value = new Value((float)value);
        }
        Token(double value) {
            this->type = TokenType::STRING;
            this->token = std::to_string(value);
            this->value = new Value((double)value);
        }
        Token(const std::string& value) {
            this->type = TokenType::STRING;
            this->token = value;
            this->value = new Value((std::string)value);
        }
        Token(Value value) {
            switch (value.GetType()) {
                case Type::INT:
                    this->type = TokenType::INT;
                    break;
                case Type::FLOAT:
                    this->type = TokenType::FLOAT;
                    break;
                case Type::DOUBLE:
                    this->type = TokenType::DOUBLE;
                    break;
                case Type::STRING:
                    this->type = TokenType::STRING;
                    break;
            }
            this->token = value.GetString();
            this->value = new Value(value);
        }

        Value &GetValue(Scope *scope = nullptr) {
            if (this->type == TokenType::IDENTIFIER)
                assert(scope != nullptr);
            if (this->type == TokenType::IDENTIFIER)
                return scope->GetVariable(this->token);
            return *value;
        }

        TokenType type;
        std::string token;
        Value *value;
    };

    class Interpreter {
        public:
            Interpreter();

            void Parse(const std::string &content);
            void ParseLine(std::vector<Token> &tokens, Scope &scope);

            Token HandleOperator(TokenType oper, Token &lhs, Token &rhs, Scope &scope);
    };

}

#endif
