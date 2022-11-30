BINARY_DIR = bin
OBJECT_DIR = objects
SOURCE_DIR = src
SETUP_DIR = setup
INCLUDE_DIR = src/include
LIBRARY_DIR = lib

all:  setup_map_sem client

client: libmap lib client.o
	@echo "Edition de liens de client.o et la lib..."
	gcc $(OBJECT_DIR)/client.o -lclient -lmap -L $(LIBRARY_DIR) -lpthread -o $(BINARY_DIR)/exe

client.o: $(SOURCE_DIR)/client.c $(INCLUDE_DIR)/types.h $(INCLUDE_DIR)/libclient.h
	@echo "Compilation du programme client..."
	gcc -c $(SOURCE_DIR)/client.c -o $(OBJECT_DIR)/client.o

libmap: $(SOURCE_DIR)/libmap.c $(INCLUDE_DIR)/types.h $(INCLUDE_DIR)/libmap.h
	@echo "Compiling map lib..."
	gcc -c $(SOURCE_DIR)/libmap.c -o $(OBJECT_DIR)/libmap.o
	ar rv $(LIBRARY_DIR)/libmap.a $(OBJECT_DIR)/libmap.o

lib: lib.o
	@echo "Création de l'archive..."
	ar rv $(LIBRARY_DIR)/libclient.a $(OBJECT_DIR)/lib.o 

lib.o: $(SOURCE_DIR)/lib.c $(INCLUDE_DIR)/libclient.h $(INCLUDE_DIR)/types.h
	@echo "Compilation de la librairie..."
	gcc -c $(SOURCE_DIR)/lib.c -o $(OBJECT_DIR)/lib.o 

setup_map_sem:
	gcc -o $(SETUP_DIR)/initialize $(SETUP_DIR)/initialize.c $(SOURCE_DIR)/libmap.c -pthread

clean:
	@echo "Suppression des binaires et fichiers objets..."
	rm -rf $(BINARY_DIR)/* $(OBJECT_DIR)/* $(LIBRARY_DIR)/* $(SETUP_DIR)/*