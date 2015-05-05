# binaries
CC				= /usr/bin/clang
RM				= /bin/rm
MAKE			= /usr/bin/make
MKDIR			= /bin/mkdir
GIT				= /usr/bin/git
CMAKE			= $(HOME)/.brew/bin/cmake
BREW			= $(HOME)/.brew/bin/brew

# app name
NAME			= arkanoid

# dir
ROOT			= $(shell pwd)
GLFW_LIB_DIR	= $(ROOT)/openGLlib
LIBFTDIR		= $(ROOT)/libft
OBJDIR			= $(ROOT)/objs
SRCDIR			= $(ROOT)/srcs
INCDIR			= $(ROOT)/includes

# lib
LIBFT			= $(LIBFTDIR)/libft.a
LIBGLFW			= $(GLFW_LIB_DIR)/src/libglfw3.a

# compil flags
FRAMEWORK		= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework GLUT
LDFLAGS			= -L $(GLFW_LIB_DIR)/src -lglfw3 $(FRAMEWORK) -L libft -lft
CFLAGS			= -I $(INCDIR) -I $(LIBFTDIR)/includes/ -I $(GLFW_LIB_DIR)/include/GLFW -Wno-deprecated
NFLAGS			= # Wall -Wextra -Werror

# source files
SRCS			= main.c \
				glfw_handler.c \
				level_loader.c \
				collision.c \
				collision2.c \
				rebound.c \
				draw.c \
				draw_ui.c \
				level.c \
				ball.c \
				pad.c \
				keys.c \
				err.c

# obj
OBJS			= $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean fclean re

all: $(CMAKE) openGLlib/CMakeLists.txt $(LIBGLFW) $(LIBFT) $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ $(CC) $< -o $@ -c $(CFLAGS) $(NFLAGS)

$(OBJDIR):
	$(MKDIR) $@

$(BREW):
	/usr/local/bin/brew update

$(CMAKE):
	$(BREW) update
	$(BREW) install cmake

openGLlib/CMakeLists.txt:
	$(GIT) submodule init
	$(GIT) submodule update

$(LIBGLFW):
	cd $(GLFW_LIB_DIR) && \
	$(CMAKE) . && \
	$(MAKE)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
