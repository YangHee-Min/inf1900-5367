

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Nom du compilateur
CC=avr-gcc

# Inclusions additionnels (ex: -I/path/to/mydir)
INC=

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Nom de base de la librairie
BASENAME=lib

# Nom du fichier source de la librairie
SRC=$(BASENAME).cpp

# Pour chaque objet .cpp produit, produitre un objet .o
OBJ=$(SRC:.cpp=.o)

# Nom de la librairie
LIB=lib$(BASENAME).a

CFLAGS=-I. -I/usr/include/simavr  -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

REMOVE= rm -f

$(LIB):$(OBJ)
	ar -rc $(LIB) $(OBJ)
	$(REMOVE) *.d *.o 

%.o: %.cpp
	@echo "attempting to compile file $(%.c)"
	$(CC)  $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	$(REMOVE) *.d *.o *.a