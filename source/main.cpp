#include <iostream>
#include <string>
#include "../lib/graphicals/IGraphics.hpp"

int handleOpen(char **lib)
{
    void *handle;
    handle = dlopen(lib[1], RTLD_NOW);

    if (!handle) {
        std::cerr << "Error handling lib " << dlerror() << std::endl;
    }

    arcade::IGraphics* (*entryPointFunc)() = (arcade::IGraphics* (*)())dlsym(handle, "entryPoint");

    if (entryPointFunc) {
        std::cerr << "Erreur: " << dlerror() << std::endl;
        dlclose(handle);
    }
    dlclose(handle);
    return 0;
}

int main(int ac, char **av)
{
    if (ac > 2)
        return 84;
    handleOpen(av);
    return 0;
}
