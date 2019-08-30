#include "Value.h"

namespace pLANG {

    template <class T>
    Value<T>::Value(Type type, T value) {
        this->type = type;
        this->value = value;
    }

    template <class T>
    T
    Value<T>::GetValue() {
        return this->value;
    }

    template <class T>
    void
    Value<T>::SetValue(T value) {
        this->value = value;
    }

}
