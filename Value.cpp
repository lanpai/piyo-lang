#include "Value.h"

#include <typeinfo>
#include <stdexcept>

namespace pLang {

    // Constructors

    Value::Value(const int &value) {
        this->type = Type::INT;
        this->value = value;
    }
    Value::Value(const float &value) {
        this->type = Type::FLOAT;
        this->value = value;
    }
    Value::Value(const double &value) {
        this->type = Type::DOUBLE;
        this->value = value;
    }
    Value::Value(const std::string &value) {
        this->type = Type::STRING;
        this->value = value;
    }

    // Getters

    int
    Value::GetInt() const {
        switch (this->type) {
            case Type::INT:
                return std::get<int>(this->value);
            case Type::FLOAT:
                return (int)std::get<float>(this->value);
            case Type::DOUBLE:
                return (int)std::get<double>(this->value);
            case Type::STRING:
                throw std::invalid_argument("can not convert type int into type string");
        }
    }
    float
    Value::GetFloat() const {
        switch (this->type) {
            case Type::INT:
                return (float)std::get<int>(this->value);
            case Type::FLOAT:
                return std::get<float>(this->value);
            case Type::DOUBLE:
                return (float)std::get<double>(this->value);
            case Type::STRING:
                throw std::invalid_argument("can not convert type float into type string");
        }
    }
    double
    Value::GetDouble() const {
        switch (this->type) {
            case Type::INT:
                return (double)std::get<int>(this->value);
            case Type::FLOAT:
                return (double)std::get<float>(this->value);
            case Type::DOUBLE:
                return std::get<double>(this->value);
            case Type::STRING:
                throw std::invalid_argument("can not convert type double into type string");
        }
    }
    std::string
    Value::GetString() const {
        switch (this->type) {
            case Type::INT:
                return std::to_string(std::get<int>(this->value));
            case Type::FLOAT:
                return std::to_string(std::get<float>(this->value));
            case Type::DOUBLE:
                return std::to_string(std::get<double>(this->value));
            case Type::STRING:
                return std::get<std::string>(this->value);
        }
    }
    Type
    Value::GetType() const {
        return this->type;
    }

    // Setters
    void
    Value::SetValue(const int &value) {
        this->value = value;
    }
    void
    Value::SetValue(const float &value) {
        this->value = value;
    }
    void
    Value::SetValue(const double &value) {
        this->value = value;
    }
    void
    Value::SetValue(const std::string &value) {
        this->value = value;
    }

    // Operator overloads
    Value
    Value::operator+(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() + rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() + rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() + rhs.GetDouble();
                    case Type::STRING:
                        return std::to_string(this->GetInt()) + rhs.GetString();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() + rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() + rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() + rhs.GetDouble();
                    case Type::STRING:
                        return std::to_string(this->GetFloat()) + rhs.GetString();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() + rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() + rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() + rhs.GetDouble();
                    case Type::STRING:
                        return std::to_string(this->GetDouble()) + rhs.GetString();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetString() + std::to_string(rhs.GetInt());
                    case Type::FLOAT:
                        return this->GetString() + std::to_string(rhs.GetFloat());
                    case Type::DOUBLE:
                        return this->GetString() + std::to_string(rhs.GetDouble());
                    case Type::STRING:
                        return this->GetString() + rhs.GetString();
                }
        }
    }

}
