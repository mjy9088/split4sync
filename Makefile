CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS =
SRC_DIR = .
OBJ_DIR = build
TARGET = s4s
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJS = $(SRCS:.c=.o)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

all: $(TARGET)
clean:
	@rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
fclean: clean
	@rm -f $(TARGET)
re: fclean all
test: $(TARGET)
	@sh test/script.sh
.PHONY: all clean fclean re test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p -- $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(LDFLAGS)

$(TARGET): $(OBJECTS)
	@mkdir -p -- $(dir $@)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

-include $(DEPS)
