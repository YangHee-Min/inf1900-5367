include ../Makefile_common.txt

$(LIB):$(OBJ) $(HEADERS)
	ar -rcs $(LIB) $(OBJ)
	$(REMOVE) *.d *.o

%.o: %.cpp %.h
	$(CC)  $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	$(REMOVE) *.d *.o 
