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
	cp $(BUILD_DIR)/arcade .

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf arcade

re: clean all

.PHONY: all configure build clean fclean re
