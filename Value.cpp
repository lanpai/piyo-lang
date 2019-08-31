#include "Value.h"

namespace pLang {

    template <>
    Value<int>::Value(const int &value) {
        this->value = value;
        this->type = Type::INT;
    }

    template <>
    Value<float>::Value(const float &value) {
        this->value = value;
        this->type = Type::FLOAT;
    }

    template <>
    Value<double>::Value(const double &value) {
        this->value = value;
        this->type = Type::DOUBLE;
    }

    template <>
    Value<std::string>::Value(const std::string &value) {
        this->value = value;
        this->type = Type::STRING;
    }

    template <typename T>
    const T &
    Value<T>::GetValue() const {
        return this->value;
    }

    template <typename T>
    void
    Value<T>::SetValue(const T &value) {
        this->value = value;
    }

    template <typename T>
    Type
    Value<T>::GetType() const {
        return this->type;
    }

    template class Value<int>;
    template class Value<float>;
    template class Value<double>;
    template class Value<std::string>;

}
