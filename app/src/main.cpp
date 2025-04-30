#include "App/App.hpp"
#include "Test.hpp"

int main() {
    HelloWorld();
    try {
        App::Get().Run();
    } catch (std::exception except) {
        std::cerr << except.what() << std::endl;
        return -1;
    }
}