TARGET = bin/output
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

run: clean default
			./$(TARGET) -f ./my_db.db -n
			./$(TARGET) -f ./my_db.db -a "Timmy H.,232 Hartford Ln,124"
			./$(TARGET) -f ./my_db.db -a "Simon.,265 Smoky Ln,890"
			./$(TARGET) -f ./my_db.db -a "Simeone,265 Smoky Ln,34"
#			./$(TARGET) -f ./my_db.db -a "Temon,Lion King,34"
			./$(TARGET) -f ./my_db.db -l
#			./$(TARGET) -f ./my_db.db -r "Timmy H."
			./$(TARGET) -f ./my_db.db -h "Simon.,100"
			./$(TARGET) -f ./my_db.db -h "Timmy H.,120"
			./$(TARGET) -f ./my_db.db -h "Simeone,123"
			./$(TARGET) -f ./my_db.db -l

default: $(TARGET)

clean: 
		rm -f obj/*.o
		rm -f bin/*
		rm -f *.db

$(TARGET):$(OBJ)
	gcc -o $@ $?

obj/%.o: src/%.c
	gcc -c $< -o $@ -Iinclude
