include ../variables.mk
-include ../variables.local.mk

CFLAGS := -O3
CFLAGS += -Weverything -Wno-poison-system-directories -Werror -pedantic
LDFLAGS :=
SRC_DIR = ..
OBJ_DIR = .
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJS = $(SRCS:.c=.o)
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS = $(OBJECTS:.o=.d)

all: $(TARGET)
clean:
	@rm -f $(OBJ_DIR)/*.o $(OBJ_DIR)/*.d
fclean: clean
	@rm -f $(SRC_DIR)/$(TARGET)
re: fclean all
test: $(TARGET)
	@sh ../test/script.sh
	@sh -c "cd ../debug/address && make re test"
	@sh -c "cd ../debug/memory && make re test"
	@sh -c "cd ../debug/thread && make re test"
	@sh -c "cd ../debug/undefined && make re test"
$(TARGET): $(SRC_DIR)/$(TARGET)
.PHONY: all clean fclean re test $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p -- $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ -MMD $(LDFLAGS)

$(SRC_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p -- $(dir $@)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

-include $(DEPS)
