#include "Interpreter.h"

#include <vector>
#include <string>

#include "Standard/Value.h"

using namespace pLang;

int main(int argc, char** argv) {
    Value<int> a(5);
    Value<int> b(6);
    Value<int> c = a + b;
    std::printf("%d\n", c.GetValue());

    return 0;
}
