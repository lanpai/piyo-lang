#include "Interpreter.h"

#include <vector>
#include <string>

#include "Value.h"

using namespace pLang;

int main(int argc, char** argv) {
    Value a(10);
    Value b("test");
    b += a;
    std::printf("%s\n", b.GetString().c_str());

    return 0;
}
