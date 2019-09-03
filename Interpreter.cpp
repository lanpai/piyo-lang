#include "Interpreter.h"

#include <sstream>
#include <map>
#include <regex>

namespace pLang {

    std::map<std::string, TokenType> TOKEN_IDENTIFIER = {
        // INT, FLOAT, DOUBLE, STRING handled in ParseMiscToken()
        {   "int",      TokenType::TYPE         },
        {   "float",    TokenType::TYPE         },
        {   "double",   TokenType::TYPE         },
        {   "string",   TokenType::TYPE         },
        {   "bool",     TokenType::TYPE         },
        {   "true",     TokenType::BOOL         },
        {   "false",    TokenType::BOOL         },
        {   "=",        TokenType::EQUAL        },
        {   "+",        TokenType::ADD          },
        {   "-",        TokenType::SUB          },
        {   "*",        TokenType::MULT         },
        {   "/",        TokenType::DIV          },
        {   "%",        TokenType::MOD          },
        {   "+=",       TokenType::ADD_EQUAL    },
        {   "-=",       TokenType::SUB_EQUAL    },
        {   "*=",       TokenType::MULT_EQUAL   },
        {   "/=",       TokenType::DIV_EQUAL    },
        {   "%=",       TokenType::MOD_EQUAL    },
        {   "!",        TokenType::NOT          },
        {   "\"",       TokenType::WRAPPER      },
        {   "(",        TokenType::WRAPPER      },
        {   ")",        TokenType::WRAPPER      },
        {   ";",        TokenType::TERMINATOR   },
        {   "==",       TokenType::IS_EQUAL     },
        {   "!=",       TokenType::IS_NOT_EQUAL },
        {   ">",        TokenType::IS_GREATER   },
        {   "<",        TokenType::IS_LESSER    },
        {   ">=",       TokenType::IS_G_EQUAL   },
        {   "<=",       TokenType::IS_L_EQUAL   },
    };

    std::map<std::string, Type> TO_TYPE = {
        {   "int",      Type::INT               },
        {   "float",    Type::FLOAT             },
        {   "double",   Type::DOUBLE            },
        {   "string",   Type::STRING            },
        {   "bool",     Type::BOOL              }
    };

    std::map<char, char> WRAPPER_MATCH = {
        { '(', ')' }
    };

    Interpreter::Interpreter() {

    }
    
    void
    ParseMiscToken(std::string &token, std::vector<Token> &tokens) {
        if (token.length() > 0) {
            switch (TOKEN_IDENTIFIER[token]) {
                // Handle types
                case TokenType::TYPE:
                    tokens.push_back(Token(TokenType::TYPE, token));
                    break;

                case TokenType::BOOL:
                    tokens.push_back(Token(TokenType::BOOL, token));
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
                    else if (std::regex_match(token, std::regex("^[a-zA-Z_]*$"))) {
                        tokens.push_back(Token(TokenType::IDENTIFIER, token));
                    }
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

        // Iterate by character
        int i = 0;
        while (ss.get(c)) {
            // Check current state
            switch (currState) {
                // Disable LINE_COMMENT state on line break
                case ReadState::LINE_COMMENT:
                    if (c == '\n') currState = ReadState::DEFAULT;
                    break;

                // Disable BLOCK_COMMENT state on */
                case ReadState::BLOCK_COMMENT:
                    if (c == '/' && content[i - 1] == '*') currState = ReadState::DEFAULT;
                    break;

                // Continue reading to token, disable STRING state on un-escaped *
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
                            // Enable LINE_COMMENT state on //
                            if (content.length() - 1 > i && content[i + 1] == '/') {
                                ParseMiscToken(currToken, tokens);
                                currState = ReadState::LINE_COMMENT;
                                ss.get(c);
                                i += 1;
                                break;
                            }

                            // Enable BLOCK_COMMENT state on /*
                            if (content.length() - 1 > i && content[i + 1] == '*') {
                                ParseMiscToken(currToken, tokens);
                                currState = ReadState::BLOCK_COMMENT;
                                ss.get(c);
                                i += 1;
                                break;
                            }

                            // Check if /=
                            if (content.length() - 1 > i && content[i + 1] == '=') {
                                ParseMiscToken(currToken, tokens);
                                tokens.push_back(Token(TokenType::DIV_EQUAL, std::string(1, c)));
                                ss.get(c);
                                i += 1;
                                break;
                            }

                        // Handle operators
                        case '=':
                        case '>':
                        case '<':
                        case '!':
                        case '+':
                        case '-':
                        case '*':
                        case '%':
                            ParseMiscToken(currToken, tokens);
                            currToken.clear();

                            // Check if /=
                            if (content.length() - 1 > i && content[i + 1] == '=') {
                                tokens.push_back(Token(TOKEN_IDENTIFIER[std::string(1, c) + "="], std::string(1, c)));
                                std::printf("FOUND %s\n", (std::string(1, c) + "=").c_str());
                                ss.get(c);
                                i += 1;
                                break;
                            }

                            tokens.push_back(Token(TOKEN_IDENTIFIER[std::string(1, c)], std::string(1, c)));
                            std::printf("FOUND %c\n", c);
                            break;

                        case '"':
                            ParseMiscToken(currToken, tokens);

                            // Enable STRING on "
                            currState = ReadState::STRING;

                            break;

                        // Wrapper logic
                        case '(':
                            ParseMiscToken(currToken, tokens);
                            tokens.push_back(Token(TokenType::WRAPPER, std::string(1, c)));
                            wrapperStack.push_back(c);
                            break;

                        case ')':
                            if (WRAPPER_MATCH[wrapperStack.back()] == c) {
                                ParseMiscToken(currToken, tokens);
                                tokens.push_back(Token(TokenType::WRAPPER, std::string(1, c)));
                                wrapperStack.pop_back();
                            }
                            else if (wrapperStack.size() == 0)
                                throw std::logic_error("extraneous '" + std::string(1, c) + "'");
                            else
                                throw std::logic_error("expected '" + std::string(1, WRAPPER_MATCH[wrapperStack.back()]) +  "' but got '" + std::string(1, c) + "'");

                        case ' ':
                        case '\n':
                            ParseMiscToken(currToken, tokens);
                            break;

                        case ';':
                            ParseMiscToken(currToken, tokens);

                            if (tokens.size() > 0) {
                                try {
                                    this->ParseLine(tokens, global);
                                }
                                catch (const std::exception &e) {
                                    std::printf("\033[1m\033[30m%s\033[0m\n", e.what());
                                    exit(EXIT_FAILURE);
                                }
                                tokens.clear();
                            }

                            break;

                        default:
                            currToken += c;
                            break;
                    }
            }
            i++;
        }

        if (currToken.length() > 0)
            throw std::logic_error("expected ';'");
    }

    void
    Interpreter::ParseLine(std::vector<Token> &tokens, Scope &scope) {
        // Precedence
        
        int operators = 0;

        // Variable declarations
        if (tokens[0].type == TokenType::TYPE) {
            if (tokens[1].type != TokenType::IDENTIFIER)
                throw std::logic_error("expected identifier after type");

            switch (TO_TYPE[tokens[0].token]) {
                case Type::INT:
                    scope.AddVariable(tokens[1].token, Value((int)0));
                    tokens.erase(tokens.begin());
                    break;
                case Type::FLOAT:
                    scope.AddVariable(tokens[1].token, Value((float)0.0f));
                    tokens.erase(tokens.begin());
                    break;
                case Type::DOUBLE:
                    scope.AddVariable(tokens[1].token, Value((double)0.0));
                    tokens.erase(tokens.begin());
                    break;
                case Type::STRING:
                    scope.AddVariable(tokens[1].token, Value((std::string)""));
                    tokens.erase(tokens.begin());
                    break;
                case Type::BOOL:
                    scope.AddVariable(tokens[1].token, Value((bool)false));
                    tokens.erase(tokens.begin());
            }
        }

        // Prefix-++/--

        // Function calls / Array subscript / Member access
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].token == "print") {
                std::printf("%s\n", tokens[i + 2].GetValue(&scope).GetString().c_str());
                tokens.clear();
            }
        }
        
        // !

        // * / %
        for (int i = 0; i < tokens.size(); i++) {
            switch (tokens[i].type) {
                case TokenType::MULT:
                case TokenType::DIV:
                case TokenType::MOD:
                    if (i == 0)
                        throw std::logic_error("expected token before operator");
                    if (tokens.size() - 1 <= i)
                        throw std::logic_error("expected token after operator");

                    tokens[i - 1] = this->HandleOperator(tokens[i].type, tokens[i - 1], tokens[i + 1], scope);
                    tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);

                    i--;
                    break;
                default:
                    break;
            }
        }

        // + -
        for (int i = 0; i < tokens.size(); i++) {
            switch (tokens[i].type) {
                case TokenType::ADD:
                case TokenType::SUB:
                    if (i == 0)
                        throw std::logic_error("expected token before operator");
                    if (tokens.size() - 1 <= i)
                        throw std::logic_error("expected token after operator");

                    tokens[i - 1] = this->HandleOperator(tokens[i].type, tokens[i - 1], tokens[i + 1], scope);
                    tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);

                    i--;
                    break;
                default:
                    break;
            }
        }

        // > < >= <=

        // == !=
        operators = 0;

        // = += -= *= /= %=
        for (int i = tokens.size() - 1; i >= 0; i--) {
            switch (tokens[i].type) {
                case TokenType::EQUAL:
                case TokenType::ADD_EQUAL:
                case TokenType::SUB_EQUAL:
                case TokenType::MULT_EQUAL:
                case TokenType::DIV_EQUAL:
                case TokenType::MOD_EQUAL:
                    if (i == 0)
                        throw std::logic_error("expected token before operator");
                    if (tokens.size() - 1 <= i)
                        throw std::logic_error("expected token after operator");

                    tokens[i - 1] = this->HandleOperator(tokens[i].type, tokens[i - 1], tokens[i + 1], scope);
                    tokens.erase(tokens.begin() + i, tokens.begin() + i + 2);

                    break;
                default:
                    break;
            }
        }

        // Suffix-++/--
    }

    Token
    Interpreter::HandleOperator(TokenType oper, Token &lhs, Token &rhs, Scope &scope) {
        switch (oper) {
            case TokenType::EQUAL:
                if (lhs.type != TokenType::IDENTIFIER)
                    throw std::logic_error("expected left hand side of operator '=' to be an identifier");
                lhs.GetValue(&scope).SetValue(rhs.GetValue(&scope));
                return lhs;

            case TokenType::ADD_EQUAL:
                return lhs.GetValue(&scope) += rhs.GetValue(&scope);
                break;

            case TokenType::SUB_EQUAL:
                return lhs.GetValue(&scope) -= rhs.GetValue(&scope);
                break;

            case TokenType::MULT_EQUAL:
                return lhs.GetValue(&scope) *= rhs.GetValue(&scope);
                break;

            case TokenType::DIV_EQUAL:
                return lhs.GetValue(&scope) /= rhs.GetValue(&scope);
                break;

            case TokenType::MOD_EQUAL:
                return lhs.GetValue(&scope) %= rhs.GetValue(&scope);
                break;

            case TokenType::ADD:
                return Token(lhs.GetValue(&scope) + rhs.GetValue(&scope));

            case TokenType::SUB:
                return Token(lhs.GetValue(&scope) - rhs.GetValue(&scope));

            case TokenType::MULT:
                return Token(lhs.GetValue(&scope) * rhs.GetValue(&scope));

            case TokenType::DIV:
                return Token(lhs.GetValue(&scope) / rhs.GetValue(&scope));

            case TokenType::MOD:
                return Token(lhs.GetValue(&scope) % rhs.GetValue(&scope));

            default:
                throw std::logic_error("illegal operator");
        }
    }

}
