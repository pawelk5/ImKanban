#include "App/App.hpp"

int main() {
    try {
        App::Get().Run();
    } catch (std::exception except) {
        std::cerr << except.what() << std::endl;
        return -1;
    }
}