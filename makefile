BINARY_DIR = bin
OBJECT_DIR = objects
SOURCE_DIR = src
SETUP_DIR = setup
INCLUDE_DIR = src/include
LIBRARY_DIR = lib

all:  setup_map_sem

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

setup_map_sem:
	gcc -o $(SETUP_DIR)/initialize $(SETUP_DIR)/initialize.c $(SOURCE_DIR)/libmap.c -pthread

clean:
	@echo "Suppression des binaires et fichiers objets..."
	rm -rf $(BINARY_DIR)/* $(OBJECT_DIR)/* $(LIBRARY_DIR)/* $(SETUP_DIR)/*




