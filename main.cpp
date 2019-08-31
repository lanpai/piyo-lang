#include "Interpreter.h"

#include <vector>
#include <string>

#include "Value.h"

using namespace pLang;

int main(int argc, char** argv) {
    Value<std::string> a("test");
    Value<int> b(6);
    Value<std::string> c = a + b;
    std::printf("%s, %d\n", c.GetValue().c_str(), c.GetType());

    return 0;
}
