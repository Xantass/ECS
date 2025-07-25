##
## EPITECH PROJECT, 2025
## R-Type
## File description:
## Makefile
##

BUILD_DIR := build
EXEC ?= $*

.PHONY: all run clean rebuild

all: $(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/%:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake -DGAME=$* .. && make
	mv ./$(BUILD_DIR)/game/$(EXEC)/$(EXEC) .

run: all
	./$(BUILD_DIR)/$(EXEC)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all

# Pour builder un autre jeu : make EXEC=spaceinvader
