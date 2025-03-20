##
## EPITECH PROJECT, 2025
## make
## File description:
## make
##
BUILD_DIR	=	build

CMAKE	=	cmake

MAKE	=	make

all: configure

configure:
	$(CMAKE) -S . -B $(BUILD_DIR)
	$(CMAKE) --build $(BUILD_DIR) --config Release

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf arcade
	rm -rf lib/*.so

re: clean all

.PHONY: all configure build clean fclean re
