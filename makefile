LPC_DIR = grafoDir
CFLAGS = -Wall -Wextra -Werror -O3 -I$(LPC_DIR)

MY_LIBS = $(wildcard $(LPC_DIR)/*)
TARGET = main.cpp
OUTPUT = grafos

all: $(OUTPUT) run

$(OUTPUT): $(TARGET) $(MY_LIBS)
	@g++ $(CFLAGS) -o $(OUTPUT) $(TARGET) 

run: $(OUTPUT)
	@./$(OUTPUT)



.PHONY: $(OUTPUT) run