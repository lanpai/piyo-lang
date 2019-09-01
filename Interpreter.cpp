#include "Interpreter.h"

#include <sstream>
#include <map>
#include <regex>

namespace pLang {

    std::map<std::string, TokenType> TOKEN_IDENTIFIER = {
        {   "int",      TokenType::TYPE         },
        {   "float",    TokenType::TYPE         },
        {   "double",   TokenType::TYPE         },
        {   "string",   TokenType::TYPE         },
        {   "=",        TokenType::EQUAL        },
        {   "+",        TokenType::ADD          },
        {   "-",        TokenType::SUB          },
        {   "*",        TokenType::MULT         },
        {   "/",        TokenType::DIV          },
        {   "+=",       TokenType::ADD_EQUAL    },
        {   "-=",       TokenType::SUB_EQUAL    },
        {   "*=",       TokenType::MULT_EQUAL   },
        {   "/=",       TokenType::DIV_EQUAL    },
        {   "\"",       TokenType::WRAPPER      },
        {   "(",        TokenType::WRAPPER      },
        {   ")",        TokenType::WRAPPER      },
        {   ";",        TokenType::TERMINATOR   }
    };

    std::map<std::string, Type> TO_TYPE = {
        {   "int",      Type::INT               },
        {   "float",    Type::FLOAT             },
        {   "double",   Type::DOUBLE            },
        {   "string",   Type::STRING            }
    };

    Interpreter::Interpreter() {

    }

    void
    PushToken(std::string &token, std::vector<Token> &tokens) {
        if (token.length() > 0) {
            switch (TOKEN_IDENTIFIER[token]) {
                // Handle types
                case TokenType::TYPE:
                    tokens.push_back(Token(TokenType::TYPE, token));
                    break;

                // Handle operators
                case TokenType::EQUAL:
                case TokenType::ADD:
                case TokenType::SUB:
                case TokenType::MULT:
                case TokenType::DIV:
                case TokenType::ADD_EQUAL:
                case TokenType::SUB_EQUAL:
                case TokenType::MULT_EQUAL:
                case TokenType::DIV_EQUAL:
                    tokens.push_back(Token(TOKEN_IDENTIFIER[token], token));
                    break;

                default:
                    // Check if int
                    if (std::regex_match(token, std::regex("^[0-9]+$")))
                        tokens.push_back(Token(TokenType::INT, token));
                    // Check if float
                    else if (std::regex_match(token, std::regex("^[0-9]+\\.[0-9]+f$")))
                        tokens.push_back(Token(TokenType::FLOAT, token));
                    // Check if double
                    else if (std::regex_match(token, std::regex("^[0-9]+\\.[0-9]+$")))
                        tokens.push_back(Token(TokenType::DOUBLE, token));
                    // Check if identififer (alphabetic + _)
                    else if (std::regex_match(token, std::regex("^[a-zA-Z_]*$")))
                        tokens.push_back(Token(TokenType::IDENTIFIER, token));
                    else
                        throw std::logic_error("invalid token '" + token + "'");
                    break;
            }

            token.clear();
        }
    }

    void
    Interpreter::Parse(const std::string &content) {
        // Create global scope
        Scope global;

        // Split content into Tokens
        std::stringstream ss(content);
        char c;
        std::vector<Token> tokens;
        std::string currToken;

        // Wrapper counter
        std::vector<char> wrapperStack;
    
        enum class ReadState {
            DEFAULT,
            LINE_COMMENT,
            BLOCK_COMMENT,
            STRING
        } currState = ReadState::DEFAULT;

        // Read single characters
        int i = 0;
        while (ss.get(c)) {
            // Check current state
            switch (currState) {
                // Disable LINE_COMMENT state on end line
                case ReadState::LINE_COMMENT:
                    if (c == '\n') currState = ReadState::DEFAULT;
                    break;

                // Disable BLOCK_COMMENT state on */
                case ReadState::BLOCK_COMMENT:
                    if (c == '/' && content[i - 1] == '*') currState = ReadState::DEFAULT;
                    break;

                // Continue reading to token, disable STRING on un-escaped "
                case ReadState::STRING:
                    if (c == '"' && content[i - 1] != '\\') {
                        currState = ReadState::DEFAULT;
                        tokens.push_back(Token(TokenType::STRING, currToken));
                        currToken.clear();
                    }
                    else
                        currToken += c;
                    break;

                // Default read state
                case ReadState::DEFAULT:
                    // Check current character
                    switch (c) {
                        case '/':
                            PushToken(currToken, tokens);

                            // Enable LINE_COMMENT on //
                            if (content.length() - 1 > i && content[i + 1] == '/')
                                currState = ReadState::LINE_COMMENT;
                                break;

                            // Enable BLOCK_COMMENT on /*
                            if (content.length() - 1 > i && content[i + 1] == '*')
                                currState = ReadState::BLOCK_COMMENT;
                                break;

                            break;

                        case '"':
                            PushToken(currToken, tokens);

                            // Enable STRING on "
                            currState = ReadState::STRING;

                            break;

                        // Wrapper logic
                        case '(':
                            PushToken(currToken, tokens);
                            tokens.push_back(Token(TokenType::WRAPPER, "("));
                            wrapperStack.push_back('(');
                            break;

                        case ')':
                            if (wrapperStack.back() == '(') {
                                PushToken(currToken, tokens);
                                tokens.push_back(Token(TokenType::WRAPPER, ")"));
                                wrapperStack.pop_back();
                            }
                            else if (wrapperStack.size() == 0)
                                throw std::logic_error("extraneous ')'");
                            else
                                throw std::logic_error("expected '" + std::string(1, wrapperStack.back()) + "' but got ')'");
                            break;

                        case ' ':
                        case '\n':
                            PushToken(currToken, tokens);
                            break;

                        case ';':
                            PushToken(currToken, tokens);

                            this->ParseLine(tokens, global);

                            tokens.clear();

                            break;

                        default:
                            currToken += c;
                            break;
                    }
                    break;
            }
            i++;
        }
    }

    void
    Interpreter::ParseLine(const std::vector<Token> &tokens, Scope &scope) {
        std::printf("\033[1m\033[33mparsing line:\033[0m ");

        std::vector<TokenType> types;
        for (Token token : tokens)
            std::printf("%s ", token.value.c_str());
        std::printf("\n");

        for (int i = 0; i < tokens.size(); i++) {
            std::printf("   \033[1m\033[30mparsing:\033[0m %s [%d]\n", tokens[i].value.c_str(), (int)tokens[i].type);
            types.push_back(tokens[i].type);
            switch (tokens[i].type) {
                case TokenType::IDENTIFIER:
                    if (tokens[i].value == "print") {
                        std::printf("       %s\n", scope.GetVariable(tokens[i + 2].value).GetString().c_str());
                    }
                    break;

                case TokenType::TYPE:
                    // Check if variable declaration
                    if (tokens.size() - 1 > i && tokens[i + 1].type == TokenType::IDENTIFIER) {
                        std::printf("created new variable %s\n", tokens[i + 1].value.c_str());

                        switch (TO_TYPE[tokens[i].value]) {
                            case Type::INT:
                                scope.AddVariable(tokens[i + 1].value, Value(0));
                                break;
                            case Type::FLOAT:
                                scope.AddVariable(tokens[i + 1].value, Value(0.0f));
                                break;
                            case Type::DOUBLE:
                                scope.AddVariable(tokens[i + 1].value, Value(0.0));
                                break;
                            case Type::STRING:
                                scope.AddVariable(tokens[i + 1].value, Value(""));
                                break;
                        }
                        i++;
                    }
                    else {
                        throw std::logic_error("expected identifier after type");
                    }
                    break;

                // Check if EQUAL operator
                case TokenType::EQUAL:
                    if (i > 0 && tokens.size() - 1 > i && tokens[i - 1].type == TokenType::IDENTIFIER) {
                        std::printf("changing variable %s\n", tokens[i - 1].value.c_str());
                        switch (tokens[i + 1].type) {
                            case TokenType::INT:
                                scope.GetVariable(tokens[i - 1].value) = std::stoi(tokens[i + 1].value);
                                i++;
                                break;
                            case TokenType::FLOAT:
                                scope.GetVariable(tokens[i - 1].value) = std::stof(tokens[i + 1].value);
                                i++;
                                break;
                            case TokenType::DOUBLE:
                                scope.GetVariable(tokens[i - 1].value) = std::stod(tokens[i + 1].value);
                                i++;
                                break;
                            case TokenType::STRING:
                                scope.GetVariable(tokens[i - 1].value) = tokens[i + 1].value;
                                i++;
                                break;
                            default:
                                throw std::logic_error("expected value after type");
                        }
                    }
                    break;

                default:
                    break;
            }
        }
    }

    /*Value
    Interpreter::ParseValue(const std::vector<Token> &tokens) {
        return Value("test");
    }*/

}
