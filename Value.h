#ifndef __VALUE_H
#define __VALUE_H

#include <string>
#include <variant>

namespace pLang {

    enum class Type {
        INT,
        FLOAT,
        DOUBLE,
        STRING
    };

    class Value {
        public:
            // Constructors
            Value(const int &value);
            Value(const float &value);
            Value(const double &value);
            Value(const std::string &value);
            Value(const Value &value);

            // Getters
            int GetInt() const;
            float GetFloat() const;
            double GetDouble() const;
            std::string GetString() const;
            Type GetType() const;

            // Setters
            void SetValue(const int &value);
            void SetValue(const float &value);
            void SetValue(const double &value);
            void SetValue(const std::string &value);
            void SetValue(const Value &value);

            // Cast
            Value CastValue(Type type) const;

            // Operator overloads
            Value operator+(const Value &rhs) const;
            Value operator-(const Value &rhs) const;
            Value operator*(const Value &rhs) const;
            Value operator/(const Value &rhs) const;
            Value operator%(const Value &rhs) const;

            Value operator+=(const Value &rhs);
            Value operator-=(const Value &rhs);
            Value operator*=(const Value &rhs);
            Value operator/=(const Value &rhs);
            Value operator%=(const Value &rhs);

        private:
            Type type;

            std::variant<int, float, double, std::string> value;
    };

}

#endif
