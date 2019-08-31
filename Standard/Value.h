#ifndef __VALUE_H
#define __VALUE_H

#include <string>

namespace pLANG {

    enum class Type {
        INT,
        FLOAT,
        DOUBLE,
        STRING
    };

    class IValue {};

    template <class T>
    class Value : public IValue {
        public:
            Value(const T &value);

            const T &GetValue() const;
            void SetValue(const T &value);

            Type GetType() const;

            Value<T> operator+(const Value<int> &rhs) const;

        private:
            Type type;

            T value;
    };

}

#endif
