#include "Interpreter.h"

#include <vector>
#include <string>

#include "Standard/Value.h"

int main(int argc, char** argv) {
    std::vector<pLANG::IValue *> test;

    pLANG::Value<int> a(5);
    pLANG::Value<int> b(6);
    pLANG::Value<int> c = a + b;
    std::printf("%d\n", c.GetValue());

    return 0;
}
