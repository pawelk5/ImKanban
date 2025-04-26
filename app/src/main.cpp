#include "App/App.hpp"
#include "Test.hpp"

int main() {
    HelloWorld();
    try {
        App::Get().Run();
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
}