SRCS			=   main.cpp
OBJS			= $(SRCS:.cpp=.o)

CXX				= c++

CXXFLAGS		=  -I includes/ -std=c++98 -g

NAME			= test

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)



.PHONY:			all clean fclean re test