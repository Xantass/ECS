##
## EPITECH PROJECT, 2025
## R-Type
## File description:
## Makefile
##

BUILD_DIR := build
EXEC ?= $*

ifeq ($(OS),Windows_NT)
    CMAKE_GENERATOR := -G "MinGW Makefiles"
    MAKE_CMD := mingw32-make
else
    CMAKE_GENERATOR :=
    MAKE_CMD := make
endif

.PHONY: all run clean rebuild

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/%:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake $(CMAKE_GENERATOR) -DGAME=$* .. && $(MAKE_CMD)
	mv ./$(BUILD_DIR)/game/$*/$* .

run: all
	./$(BUILD_DIR)/$(EXEC)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

# Pour builder un autre jeu : make EXEC=spaceinvader
