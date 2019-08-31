#ifndef __VALUE_H
#define __VALUE_H

#include <string>

namespace pLang {

    enum class Type {
        INT,
        FLOAT,
        DOUBLE,
        STRING
    };

    class IValue {};

    template <typename T>
    class Value : public IValue {
        public:
            Value(const T &value);

            const T &GetValue() const;
            void SetValue(const T &value);

            Type GetType() const;

            // Operator overloads
            template <typename R>
            Value<T> operator+(const Value<R> &rhs) const;
            template <typename R>
            Value<T> operator-(const Value<R> &rhs) const;
            template <typename R>
            Value<T> operator*(const Value<R> &rhs) const;
            template <typename R>
            Value<T> operator/(const Value<R> &rhs) const;

        private:
            Type type;

            T value;
    };

    // Operator overload definitions

    template <typename T>
    template <typename R>
    Value<T>
    Value<T>::operator+(const Value<R> &rhs) const {
        return this->GetValue() + rhs.GetValue();
    }

    template <typename T>
    template <typename R>
    Value<T>
    Value<T>::operator-(const Value<R> &rhs) const {
        return this->GetValue() - rhs.GetValue();
    }

    template <typename T>
    template <typename R>
    Value<T>
    Value<T>::operator*(const Value<R> &rhs) const {
        return this->GetValue() * rhs.GetValue();
    }

    template <typename T>
    template <typename R>
    Value<T>
    Value<T>::operator/(const Value<R> &rhs) const {
        return this->GetValue() / rhs.GetValue();
    }
    
    // String concatenation
    template <>
    template <typename R>
    Value<std::string>
    Value<std::string>::operator+(const Value<R> &rhs) const {
        return this->GetValue() + std::to_string(rhs.GetValue());
    }

}

#endif
