#include "Scope.h"

#include <stdexcept>

namespace pLang {

    Scope::Scope(Scope *parent) {
        this->parent = parent;
    }

    void
    Scope::AddVariable(const std::string &iden, const Value &value) {
        std::map<std::string, Value>::iterator it = this->variables.find(iden);
        if (it == this->variables.end())
            this->variables.insert(std::make_pair(iden, value));
        else
            throw std::logic_error("'" + iden +  "' is being redefined");
    }

    Value &
    Scope::GetVariable(const std::string &iden) {
        std::map<std::string, Value>::iterator it = this->variables.find(iden);
        if (it == this->variables.end()) {
            if (this->parent != nullptr)
                return this->parent->GetVariable(iden);
            throw std::logic_error("use of undeclared identifier '" + iden + "'");
        }
        else
            return it->second;
    }

}
