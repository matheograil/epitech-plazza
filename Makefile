##
## Project: ThePlazza
## File: Makefile
##

SOURCES = Main.cpp \
	./Sources/Classes/Reception/Init.cpp \
	./Sources/Classes/Reception/Run.cpp \
	./Sources/Classes/Reception/Balancing.cpp \
	./Sources/Classes/Reception/Utils.cpp \
	./Sources/Classes/Child.cpp \
	./Sources/Classes/Utils.cpp \
	./Sources/Classes/Queue.cpp \
	./Sources/Classes/Kitchen/Utils.cpp \
	./Sources/Classes/Kitchen/Cook.cpp \
	./Sources/Classes/Kitchen/Init.cpp \
	./Sources/Classes/Kitchen/Run.cpp \
	./Sources/Classes/Parsing.cpp

FLAGS = -std=c++11 -Wall -Wextra -Werror -I ./Includes/

BINARY_NAME = plazza

$(BINARY_NAME):
	g++ $(FLAGS) $(SOURCES) -o $(BINARY_NAME)

all: $(BINARY_NAME)

clean:
	rm -f $(BINARY_NAME)

fclean: clean

re: fclean all
