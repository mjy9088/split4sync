all:
	@make -C build all
clean:
	@make -C build clean
fclean:
	@make -C build fclean
re:
	@make -C build re
test:
	@make -C build test
.PHONY: all clean fclean re test
