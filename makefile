BINARY_DIR = bin
OBJECT_DIR = objects
SOURCE_DIR = src
INCLUDE_DIR = src/include
LIBRARY_DIR = lib

all: client setup

client: lib client.o
	@echo "Edition de liens de client.o et la lib..."
	gcc $(OBJECT_DIR)/client.o -lclient -L $(LIBRARY_DIR) -lpthread -o $(BINARY_DIR)/exe

client.o: $(SOURCE_DIR)/client.c $(INCLUDE_DIR)/lib.h
	@echo "Compilation du programme client..."
	gcc -c $(SOURCE_DIR)/client.c -o $(OBJECT_DIR)/client.o

lib: lib.o
	@echo "Création de l'archive..."
	ar rv $(LIBRARY_DIR)/libclient.a $(OBJECT_DIR)/lib.o 

lib.o: $(SOURCE_DIR)/lib.c $(INCLUDE_DIR)/lib.h
	@echo "Compilation de la librairie..."
	gcc -c $(SOURCE_DIR)/lib.c -o $(OBJECT_DIR)/lib.o 

setup:
	gcc -o bin/setup setup.c lib/libmap.c

clean:
	@echo "Suppression des binaires et fichiers objets..."
	rm -rf $(BINARY_DIR)/* $(OBJECT_DIR)/* $(LIBRARY_DIR)/*




