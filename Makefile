TARGET = bin/output
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
			./$(TARGET) -f ./my_db.db -n
			./$(TARGET) -f ./my_db.db -a "Timmy H.,232 Hartford Ln,124"
			./$(TARGET) -f ./my_db.db -a "Meem,412 Noyatola,1217"

default: $(TARGET)

clean: 
		rm -f obj/*.o
		rm -f bin/*
		rm -f *.db

$(TARGET):$(OBJ)
	gcc -o $@ $?

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude
