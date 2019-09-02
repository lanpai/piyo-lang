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
    Value::Value(const Value &value) {
        this->type = value.type;
        this->value = value.value;
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
                try {
                    return std::stoi(std::get<std::string>(this->value));
                }
                catch (const std::exception &e) {
                    throw std::logic_error("can not convert type string into type int");
                }
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
                try {
                    return std::stof(std::get<std::string>(this->value));
                }
                catch (const std::exception &e) {
                    throw std::logic_error("can not convert type string into type float");
                }
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
                try {
                    return std::stod(std::get<std::string>(this->value));
                }
                catch (const std::exception &e) {
                    throw std::logic_error("can not convert type string into type double");
                }
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
        switch (this->type) {
            case Type::INT:
            case Type::FLOAT:
            case Type::DOUBLE:
                this->value = value;
                break;
            case Type::STRING:
                this->value = std::to_string(value);
                break;
        }
    }
    void
    Value::SetValue(const float &value) {
        switch (this->type) {
            case Type::INT:
            case Type::FLOAT:
            case Type::DOUBLE:
                this->value = value;
                break;
            case Type::STRING:
                this->value = std::to_string(value);
                break;
        }
    }
    void
    Value::SetValue(const double &value) {
        switch (this->type) {
            case Type::INT:
            case Type::FLOAT:
            case Type::DOUBLE:
                this->value = value;
                break;
            case Type::STRING:
                this->value = std::to_string(value);
                break;
        }
    }
    void
    Value::SetValue(const std::string &value) {
        switch (this->type) {
            case Type::INT:
                throw std::logic_error("can not convert type string into type int");
                break;
            case Type::FLOAT:
                throw std::logic_error("can not convert type string into type float");
                break;
            case Type::DOUBLE:
                throw std::logic_error("can not convert type string into type double");
                break;
            case Type::STRING:
                this->value = value;
                break;
        }
    }
    void
    Value::SetValue(const Value &value) {
        switch (value.GetType()) {
            case Type::INT:
                this->value = value.GetInt();
                break;
            case Type::FLOAT:
                this->value = value.GetFloat();
                break;
            case Type::DOUBLE:
                this->value = value.GetDouble();
                break;
            case Type::STRING:
                this->value = value.GetString();
                break;
        }
    }

    // Cast
    Value
    Value::CastValue(Type type) const {
        switch (this->type) {
            case Type::INT:
                return Value(this->GetInt());
                break;
            case Type::FLOAT:
                return Value(this->GetFloat());
                break;
            case Type::DOUBLE:
                return Value(this->GetDouble());
                break;
            case Type::STRING:
                return Value(this->GetString());
                break;
        }
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
    Value
    Value::operator-(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() - rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() - rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() - rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type int and type string");
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() - rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() - rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() - rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type float and type string");
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() - rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() - rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() - rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type double and type string");
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator - between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator - between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator - between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type string and type string");
                }
        }
    }
    Value
    Value::operator*(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() * rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() * rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() * rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type int and type string");
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() * rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() * rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() * rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type float and type string");
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() * rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() * rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() * rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type double and type string");
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator - between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator - between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator - between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type string and type string");
                }
        }
    }
    Value
    Value::operator/(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() / rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() / rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() / rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type int and type string");
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() / rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() / rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() / rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type float and type string");
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() / rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() / rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() / rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type double and type string");
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator - between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator - between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator - between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator - between type string and type string");
                }
        }
    }
    Value
    Value::operator%(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() % rhs.GetInt();
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator % between type int and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator % between type int and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator % between type int and type string");
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator % between type float and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator % between type float and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator % between type float and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator % between type float and type string");
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator % between type double and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator % between type double and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator % between type double and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator % between type double and type string");
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator % between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator % between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator % between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator % between type string and type string");
                }
        }
    }

    Value
    Value::operator+=(const Value &rhs) {
        *this = *this + rhs;
        return *this;
    }
    Value
    Value::operator-=(const Value &rhs) {
        *this = *this - rhs;
        return *this;
    }
    Value
    Value::operator*=(const Value &rhs) {
        *this = *this * rhs;
        return *this;
    }
    Value
    Value::operator/=(const Value &rhs) {
        *this = *this / rhs;
        return *this;
    }
    Value
    Value::operator%=(const Value &rhs) {
        *this = *this % rhs;
        return *this;
    }

}
