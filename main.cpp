#include "Interpreter.h"

#include <string>
#include <fstream>

#include "Interpreter.h"

using namespace pLang;

int main(int argc, char** argv) {
    if (argc > 1) {
        std::ifstream fs(argv[1]);

        std::string content((std::istreambuf_iterator<char>(fs)),
                           (std::istreambuf_iterator<char>()));

        Interpreter pLang;
        pLang.Parse(content);
    }
    else {
        std::printf("no file provided in argument!\n");
    }

    return 0;
}
