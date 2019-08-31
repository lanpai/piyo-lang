#include "Interpreter.h"

#include <vector>
#include <string>

#include "Value.h"

using namespace pLang;

int main(int argc, char** argv) {
    Value a("test");
    std::printf("%d\n", a.GetInt());

    return 0;
}
