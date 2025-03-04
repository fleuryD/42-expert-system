# Nom de l'exécutable
TARGET = expert



# Détection de l'OS
ifeq ($(OS),Windows_NT)
    TARGET_OS := windows
else
    TARGET_OS := linux
endif

# Définition du compilateur
ifeq ($(TARGET_OS),windows)
    CXX = g++
    STD = -std=c++23
    RM = del /Q /F
else
    CXX = clang++
    STD = -std=c++2b
    RM = rm -rf
endif


# Options de compilation
CXXFLAGS = $(STD) -Wall -Wextra -Werror -O2

# Répertoire des fichiers objets
OBJ_DIR = obj

# Fichiers source
SRC = \
    src/App.cpp \
    src/main.cpp \
    src/Rule.cpp \
    src/utils_files.cpp \
    src/utils_print.cpp \
    src/utils_string.cpp \
    src/utils_tokens.cpp

# Gestion des fichiers objets
ifeq ($(TARGET_OS),windows)
    OBJ = $(SRC:.cpp=.o)
else
    OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC))
endif

# Compilation des fichiers objets
ifeq ($(TARGET_OS),windows)
    %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
else
    $(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/src
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif


# Règle par défaut : compile tout
all: $(TARGET)
	@echo " ---------------------------"
	@echo "|  Compilation terminée     |"
	@echo "|  Executez:                |"
	@echo "|     ./expert ./maps/...   |"
	@echo "|  Ou:                      |"
	@echo "|     ./expert -f [fileId]  |"
	@echo " ---------------------------"


# Compilation de l'exécutable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Nettoyage
clean:
#	@$(RM) $(OBJ_DIR)/*.o
#	@$(RM) $(OBJ_DIR)/src/*.o
	@$(RM) $(OBJ_DIR)
	@echo "Fichiers objets supprimés."

fclean: clean
	@$(RM) $(TARGET)
	@echo "Exécutable supprimé."

re: fclean all

# Cibles Make
.PHONY: all clean fclean re
