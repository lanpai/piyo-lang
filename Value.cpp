#include "Value.h"

#include <typeinfo>
#include <stdexcept>

namespace pLang {

    // Constructors

    Value::Value(int value) {
        this->type = Type::INT;
        this->value = value;
    }
    Value::Value(float value) {
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
    Value::Value(bool value) {
        this->type = Type::BOOL;
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
            case Type::BOOL:
                return (int)std::get<bool>(this->value);
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
            case Type::BOOL:
                return (float)std::get<bool>(this->value);
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
            case Type::BOOL:
                return (double)std::get<bool>(this->value);
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
            case Type::BOOL:
                return std::get<bool>(this->value) ? "true" : "false";
        }
    }
    bool
    Value::GetBool() const {
        switch (this->type) {
            case Type::INT:
                return (bool)std::get<int>(this->value);
            case Type::FLOAT:
                return (bool)std::get<float>(this->value);
            case Type::DOUBLE:
                return (bool)std::get<double>(this->value);
            case Type::STRING:
                return (bool)std::get<std::string>(this->value).length();
            case Type::BOOL:
                return std::get<bool>(this->value);
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
                this->value = (int)value;
                break;
            case Type::FLOAT:
                this->value = (float)value;
                break;
            case Type::DOUBLE:
                this->value = (double)value;
                break;
            case Type::STRING:
                this->value = std::to_string(value);
                break;
            case Type::BOOL:
                this->value = (bool)value;
                break;
        }
    }
    void
    Value::SetValue(const float &value) {
        switch (this->type) {
            case Type::INT:
                this->value = (int)value;
                break;
            case Type::FLOAT:
                this->value = (float)value;
                break;
            case Type::DOUBLE:
                this->value = (double)value;
                break;
            case Type::STRING:
                this->value = std::to_string(value);
                break;
            case Type::BOOL:
                this->value = (bool)value;
                break;
        }
    }
    void
    Value::SetValue(const double &value) {
        switch (this->type) {
            case Type::INT:
                this->value = (int)value;
                break;
            case Type::FLOAT:
                this->value = (float)value;
                break;
            case Type::DOUBLE:
                this->value = (double)value;
                break;
            case Type::STRING:
                this->value = std::to_string(value);
                break;
            case Type::BOOL:
                this->value = (bool)value;
                break;
        }
    }
    void
    Value::SetValue(const std::string &value) {
        switch (this->type) {
            case Type::INT:
                try {
                    this->value = std::stoi(value);
                }
                catch (const std::exception &e) {
                    throw std::logic_error("can not convert type string into type int");
                }
                break;
            case Type::FLOAT:
                try {
                    this->value = std::stof(value);
                }
                catch (const std::exception &e) {
                    throw std::logic_error("can not convert type string into type float");
                }
                break;
            case Type::DOUBLE:
                try {
                    this->value = std::stod(value);
                }
                catch (const std::exception &e) {
                    throw std::logic_error("can not convert type string into type double");
                }
                break;
            case Type::STRING:
                this->value = value;
                break;
            case Type::BOOL:
                this->value = (bool)value.length();
                break;
        }
    }
    void
    Value::SetValue(const Value &value) {
        switch (this->GetType()) {
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
            case Type::BOOL:
                this->value = value.GetBool();
                break;
        }
    }

    // Cast
    Value
    Value::CastValue(Type type) const {
        switch (this->type) {
            case Type::INT:
                return Value(this->GetInt());
            case Type::FLOAT:
                return Value(this->GetFloat());
            case Type::DOUBLE:
                return Value(this->GetDouble());
            case Type::STRING:
                return Value(this->GetString());
            case Type::BOOL:
                return Value(this->GetBool());
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
                        return this->GetString() + rhs.GetString();
                    case Type::BOOL:
                        return this->GetInt() + rhs.GetBool();
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
                        return this->GetString() + rhs.GetString();
                    case Type::BOOL:
                        return this->GetFloat() + rhs.GetBool();
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
                        return this->GetString() + rhs.GetString();
                    case Type::BOOL:
                        return this->GetDouble() + rhs.GetBool();
                }
            case Type::STRING:
                return this->GetString() + rhs.GetString();
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() + rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() + rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() + rhs.GetDouble();
                    case Type::STRING:
                        return this->GetString() + rhs.GetString();
                    case Type::BOOL:
                        return this->GetBool() + rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '-' between type int and type string");
                    case Type::BOOL:
                        return this->GetInt() - rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '-' between type float and type string");
                    case Type::BOOL:
                        return this->GetFloat() - rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '-' between type double and type string");
                    case Type::BOOL:
                        return this->GetDouble() - rhs.GetBool();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '-' between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '-' between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '-' between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '-' between type string and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '-' between type string and type bool");
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() - rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() - rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() - rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '-' between type bool and type string");
                    case Type::BOOL:
                        return this->GetBool() - rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '*' between type int and type string");
                    case Type::BOOL:
                        return this->GetInt() * rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '*' between type float and type string");
                    case Type::BOOL:
                        return this->GetFloat() * rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '*' between type double and type string");
                    case Type::BOOL:
                        return this->GetDouble() * rhs.GetBool();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '*' between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '*' between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '*' between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '*' between type string and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '*' between type string and type bool");
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() * rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() * rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() * rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '*' between type bool and type string");
                    case Type::BOOL:
                        return this->GetBool() * rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '/' between type int and type string");
                    case Type::BOOL:
                        return this->GetInt() / rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '/' between type float and type string");
                    case Type::BOOL:
                        return this->GetFloat() / rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '/' between type double and type string");
                    case Type::BOOL:
                        return this->GetDouble() / rhs.GetBool();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '/' between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '/' between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '/' between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '/' between type string and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '/' between type string and type bool");
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() / rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() / rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() / rhs.GetDouble();
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '/' between type bool and type string");
                    case Type::BOOL:
                        return this->GetBool() / rhs.GetBool();
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
                        throw std::logic_error("can not perform operator '%' between type int and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '%' between type int and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '%' between type int and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '%' between type int and type float");
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '%' between type float and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '%' between type float and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '%' between type float and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '%' between type float and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '%' between type float and type float");
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '%' between type double and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '%' between type double and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '%' between type double and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '%' between type double and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '%' between type double and type float");
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '%' between type string and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '%' between type string and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '%' between type string and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '%' between type string and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '%' between type string and type float");
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        throw std::logic_error("can not perform operator '%' between type bool and type int");
                    case Type::FLOAT:
                        throw std::logic_error("can not perform operator '%' between type bool and type float");
                    case Type::DOUBLE:
                        throw std::logic_error("can not perform operator '%' between type bool and type double");
                    case Type::STRING:
                        throw std::logic_error("can not perform operator '%' between type bool and type string");
                    case Type::BOOL:
                        throw std::logic_error("can not perform operator '%' between type bool and type bool");
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

    bool
    Value::operator==(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() == rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() == rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() == rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetInt() == rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() == rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() == rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() == rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetFloat() == rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() == rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() == rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() == rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetDouble() == rhs.GetBool();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::STRING:
                        return this->GetString() == rhs.GetString();
                    default:
                        return false;
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() == rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() == rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() == rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetBool() == rhs.GetBool();
                }
        }
    }

    bool
    Value::operator!=(const Value &rhs) const {
        return !(*this == rhs);
    }

    Value
    Value::operator>(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() > rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() > rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() > rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetInt() > rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() > rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() > rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() > rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetFloat() > rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() > rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() > rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() > rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetDouble() > rhs.GetBool();
                }
            case Type::STRING:
                return false;
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() > rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() > rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() > rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetBool() > rhs.GetBool();
                }
        }
    }

    Value
    Value::operator<(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() < rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() < rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() < rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetInt() < rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() < rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() < rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() < rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetFloat() < rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() < rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() < rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() < rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetDouble() < rhs.GetBool();
                }
            case Type::STRING:
                return false;
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() < rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() < rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() < rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetBool() < rhs.GetBool();
                }
        }
    }

    Value
    Value::operator>=(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() >= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() >= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() >= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetInt() >= rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() >= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() >= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() >= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetFloat() >= rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() >= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() >= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() >= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetDouble() >= rhs.GetBool();
                }
            case Type::STRING:
                return false;
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() >= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() >= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() >= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetBool() >= rhs.GetBool();
                }
        }
    }

    Value
    Value::operator<=(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() <= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() <= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() <= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetInt() <= rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() <= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() <= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() <= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetFloat() <= rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() <= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() <= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() <= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetDouble() <= rhs.GetBool();
                }
            case Type::STRING:
                return false;
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() <= rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() <= rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() <= rhs.GetDouble();
                    case Type::STRING:
                        return false;
                    case Type::BOOL:
                        return this->GetBool() <= rhs.GetBool();
                }
        }
    }

    Value
    Value::operator&&(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() && rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() && rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() && rhs.GetDouble();
                    case Type::STRING:
                        return this->GetInt() && rhs.GetBool();
                    case Type::BOOL:
                        return this->GetInt() && rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() && rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() && rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() && rhs.GetDouble();
                    case Type::STRING:
                        return this->GetFloat() && rhs.GetBool();
                    case Type::BOOL:
                        return this->GetFloat() && rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() && rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() && rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() && rhs.GetDouble();
                    case Type::STRING:
                        return this->GetDouble() && rhs.GetBool();
                    case Type::BOOL:
                        return this->GetDouble() && rhs.GetBool();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() && rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() && rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() && rhs.GetDouble();
                    case Type::STRING:
                        return this->GetBool() && rhs.GetBool();
                    case Type::BOOL:
                        return this->GetBool() && rhs.GetBool();
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() && rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() && rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() && rhs.GetDouble();
                    case Type::STRING:
                        return this->GetBool() && rhs.GetBool();
                    case Type::BOOL:
                        return this->GetBool() && rhs.GetBool();
                }
        }
    }

    Value
    Value::operator||(const Value &rhs) const {
        switch (this->type) {
            case Type::INT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetInt() || rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetInt() || rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetInt() || rhs.GetDouble();
                    case Type::STRING:
                        return this->GetInt() || rhs.GetBool();
                    case Type::BOOL:
                        return this->GetInt() || rhs.GetBool();
                }
            case Type::FLOAT:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetFloat() || rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetFloat() || rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetFloat() || rhs.GetDouble();
                    case Type::STRING:
                        return this->GetFloat() || rhs.GetBool();
                    case Type::BOOL:
                        return this->GetFloat() || rhs.GetBool();
                }
            case Type::DOUBLE:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetDouble() || rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetDouble() || rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetDouble() || rhs.GetDouble();
                    case Type::STRING:
                        return this->GetDouble() || rhs.GetBool();
                    case Type::BOOL:
                        return this->GetDouble() || rhs.GetBool();
                }
            case Type::STRING:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() || rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() || rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() || rhs.GetDouble();
                    case Type::STRING:
                        return this->GetBool() || rhs.GetBool();
                    case Type::BOOL:
                        return this->GetBool() || rhs.GetBool();
                }
            case Type::BOOL:
                switch (rhs.type) {
                    case Type::INT:
                        return this->GetBool() || rhs.GetInt();
                    case Type::FLOAT:
                        return this->GetBool() || rhs.GetFloat();
                    case Type::DOUBLE:
                        return this->GetBool() || rhs.GetDouble();
                    case Type::STRING:
                        return this->GetBool() || rhs.GetBool();
                    case Type::BOOL:
                        return this->GetBool() || rhs.GetBool();
                }
        }
    }
}
