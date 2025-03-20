#include <iostream>
#include <string>
#include "../lib/graphicals/IGraphics.hpp"

int handleOpen(char *lib)
{
    void *handle;
    handle = dlopen(lib, RTLD_NOW);

    if (!handle) {
        std::cerr << "Error handling lib " << dlerror() << std::endl;
        return 84;
    }

    arcade::IGraphics* (*entryPointFunc)() = (arcade::IGraphics* (*)())dlsym(handle, "entryPoint");

    if (!entryPointFunc) {
        std::cerr << "Erreur: " << dlerror() << std::endl;
        dlclose(handle);
        return 84;
    }

    arcade::IGraphics *get_start = entryPointFunc();
    get_start->Init();
    dlclose(handle);
    return 0;
}

int main(int ac, char **av)
{
    if (ac > 2)
        return 84;
    if (handleOpen(av[1]) == 84) {
        return 84;
    }
    return 0;
}
