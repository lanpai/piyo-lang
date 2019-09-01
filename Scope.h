#ifndef __SCOPE_H
#define __SCOPE_H

#include <map>
#include <string>
#include <vector>

#include "Value.h"

namespace pLang {

    class Scope {
        public:
            Scope(Scope *parent = nullptr);

            void AddVariable(const std::string &iden, const Value &value);
            Value &GetVariable(const std::string &iden);

        private:
            Scope *parent;
            std::map<std::string, Value> variables;
    };

}

#endif
