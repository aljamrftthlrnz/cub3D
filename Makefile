# Variables
CC = cc
CFLAGS = -Wall -Wextra -I./include
MLXFLG = -lmlx -L /usr/lib -lXext -lX11 -lm -lbsd -lz 
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
NAME = $(BINDIR)/myprogram

SRCS = $(SRCDIR)/experimenting.c
OBJS = $($(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Default NAME
all: directories $(NAME)

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

#$(OBJDIR)/%.o: $(SRCDIR)/%.c
#	$(CC) $(CFLAGS) $(SRCS) -c $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLXFLG) $(OBJS) -o $(NAME)

$(OBJ):	$(SRC) 
	$(CC) $(CFLAGS) $(SRC) -I/usr/include -Imlx -O3 -c 

clean:
	rm -rf $(OBJDIR)/*.o $(BINDIR)

.PHONY: all directories clean
