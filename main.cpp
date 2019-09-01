#include "Interpreter.h"

#include <string>
#include <fstream>

#include "Interpreter.h"

using namespace pLang;

int main(int argc, char** argv) {
    std::ifstream fs("test.piyo");
    std::string content((std::istreambuf_iterator<char>(fs)),
                       (std::istreambuf_iterator<char>()));

    Interpreter pLang;
    pLang.Parse(content);

    return 0;
}
