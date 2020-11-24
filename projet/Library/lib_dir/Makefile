# Fichier: Makefile
# Auteurs: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
# Date: November 1 2020
# Mis à jour: November 1 2020
# Description: Makefile qui génère la librairie

include ../Makefile_common.txt

$(LIB):$(OBJ) $(HEADERS)
	ar -rcs $(LIB) $(OBJ)
	make clean

%.o: %.cpp %.h
	$(CC)  $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	$(REMOVE) *.d *.o
#####                    EOF                   #####
