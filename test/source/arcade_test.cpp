#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "arcade" ? 0 : 1;
}
