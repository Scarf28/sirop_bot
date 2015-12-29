# Modèle de fichier Makefile, à adapter pour le TP

# options de compilation
CC = gcc
CCFLAGS = -Wall
LIBSDIR = #-L/usr/lib/x86_x64-linux-gnu
LIBS = -lm



# fichiers du projet
SRC = main.c
OBJ = $(SRC:.c=.o) 
EXEC =simu.out


# règle initiale
all: $(EXEC)

# dépendance des .h
#blackjack.o : robot_api.h

# règles de compilation
%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LIBSDIR)

# règles supplémentaires
clean:
	rm -f $(SRC:.c=.o)
mproper:
	rm -f $(EXEC) $(SRC:.c=.o)
