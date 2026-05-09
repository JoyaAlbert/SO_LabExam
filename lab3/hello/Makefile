GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

.PHONY: all clean fclean re pato

all: hello hola
	@echo -e "$(GREEN)Build completado: hello y hola$(RESET)"

hello: hello.o imprime_en.o
	gcc hello.o imprime_en.o -o hello

hola: hello.o imprime_es.o
	gcc hello.o imprime_es.o -o hola

hello.o: hello.c imprime.h
	@echo -e "$(BLUE)Compilando hello.c...$(RESET)"
	gcc -Wall -Wextra -Werror -c hello.c

imprime_en.o: imprime_en.c imprime.h
	@echo -e "$(BLUE)Compilando imprime_en.c...$(RESET)"
	gcc -Wall -Wextra -Werror -c imprime_en.c

imprime_es.o: imprime_es.c imprime.h
	@echo -e "$(BLUE)Compilando imprime_es.c...$(RESET)"
	gcc -Wall -Wextra -Werror -c imprime_es.c

pato:
	@clear || true
	@echo -e "$(YELLOW)   __"
	@echo -e "<(o )___"
	@echo -e " ( ._> /"
	@echo -e "  \`---'$(RESET)"

clean: pato
	@echo -e "$(YELLOW)Limpiando objetos...$(RESET)"
	rm -f hello.o imprime_en.o imprime_es.o
	@echo -e "$(GREEN)Objetos eliminados.$(RESET)"

fclean: clean
	@echo -e "$(YELLOW)Eliminando ejecutable...$(RESET)"
	rm -f hello hola
	@echo -e "$(GREEN)Ejecutable eliminado.$(RESET)"

re: fclean all
	@echo -e "$(GREEN)Rebuild completo.$(RESET)"
