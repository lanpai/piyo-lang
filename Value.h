#ifndef __VALUE_H
#define __VALUE_H

#include <string>
#include <variant>

namespace pLang {

    enum class Type {
        INT,
        FLOAT,
        DOUBLE,
        STRING,
        BOOL
    };

    class Value {
        public:
            // Constructors
            Value(int value);
            Value(float value);
            Value(const double &value);
            Value(const std::string &value);
            Value(bool value);
            Value(const Value &value);

            // Getters
            int GetInt() const;
            float GetFloat() const;
            double GetDouble() const;
            std::string GetString() const;
            bool GetBool() const;
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

            bool operator==(const Value &rhs) const;
            bool operator!=(const Value &rhs) const;

            Value operator>(const Value &rhs) const;
            Value operator<(const Value &rhs) const;
            Value operator>=(const Value &rhs) const;
            Value operator<=(const Value &rhs) const;

            Value operator&&(const Value &rhs) const;
            Value operator||(const Value &rhs) const;

        private:
            Type type;

            std::variant<int, float, double, std::string, bool> value;
    };

}

#endif
