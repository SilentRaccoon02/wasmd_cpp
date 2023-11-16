#include <emscripten.h>
#include <iostream>

extern "C" {
EMSCRIPTEN_KEEPALIVE
float add(float x, float y) { return x + y; }

// extern void f(int a);
// extern int g(int a, int b);
}

typedef void js();

void callJs(int p) { ((js *)p)(); } // NOLINT

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Incorrect main call" << std::endl;
        return 0;
    }

    int p = std::stoi(std::string(argv[1]));
    callJs(p);

    // f(7);
    // std::cout << "Function g returned " << g(2, 5) << std::endl;
    return 0;
}
