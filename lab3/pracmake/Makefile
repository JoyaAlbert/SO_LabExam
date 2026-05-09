GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

.PHONY: all clean

all: factorial
	@echo -e "$(GREEN)Build completado: factorial$(RESET)"

factorial: factorial.o factprint.o factfun.o
	gcc factorial.o factprint.o factfun.o -o factorial

factorial.o: factorial.c factprint.h
	@echo -e "$(BLUE)Compilando factorial.c...$(RESET)"
	gcc -Wall -Wextra -Werror -c factorial.c

factprint.o: factprint.c factfun.h
	@echo -e "$(BLUE)Compilando factprint.c...$(RESET)"
	gcc -Wall -Wextra -Werror -c factprint.c

factfun.o: factfun.c factfun.h
	@echo -e "$(BLUE)Compilando factfun.c...$(RESET)"
	gcc -Wall -Wextra -Werror -c factfun.c

clean:
	@echo -e "$(YELLOW)Limpiando objetos...$(RESET)"
	rm -f factorial.o factprint.o factfun.o
	@echo -e "$(GREEN)Objetos eliminados.$(RESET)"
