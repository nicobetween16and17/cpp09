NAME = PmergeMe

CC    = c++

CCFLAGS    = -Wall -Wextra -Werror -std=c++98

RESET    = \033[0m
BLACK    = \033[0;30m
RED    = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
WHITE     = \033[0;37m

BOLDBLACK    = \033[1m\033[30m
BOLDRED        = \033[1m\033[31m
BOLDGREEN = \033[1m\033[32m
BOLDYELLOW = \033[1m\033[33m
BOLDBLUE  = \033[1m\033[34m
BOLDMAGENTA    = \033[1m\033[35m
BOLDCYAN    = \033[1m\033[36m
BOLDWHITE    = \033[1m\033[37m

SRC = PmergeMe.cpp main.cpp 

OBJ = $(SRC:%.cpp=%.o)

BOBJS = $(BONUS:%.cpp=%.o)

#end of variable definitions

all:	$(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CCFLAGS) $(OBJ) -o $@
		@printf "\n[COMPILED]\n"

%.o: %.cpp
		@printf "$(GREEN).$(RESET)"
		@$(CC) $(CCFLAGS) -c $< -o $@

clean:
		@rm -f $(OBJ)
		@printf "$(RED)[CLEAN]\n$(RESET)"

fclean: clean
		@rm -f $(NAME)
		@printf "[FCLEAN]\n"

re: fclean all

test:
		echo "test $(RED)test"

.PHONY: test clean fclean all
