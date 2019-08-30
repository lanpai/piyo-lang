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
            Value(Type type, T value);

            T GetValue();
            void SetValue(T value);

            Value<int> operator+(Value<int> rhs) { return this->GetValue() + rhs.GetValue(); }

        private:
            Type type;

            T value;
    };

}

#endif
