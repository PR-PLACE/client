BINARY_DIR = bin
OBJECT_DIR = objects
SOURCE_DIR = src
SETUP_DIR = setup
INCLUDE_DIR = src/include
LIBRARY_DIR = lib
FLAGS = -Wall

all: setup_map_sem client


client: libmap libclient client.o
	@echo "Link libs and client"
	gcc $(FLAGS) $(OBJECT_DIR)/client.o -lclient -lmap -L $(LIBRARY_DIR) -lpthread -o $(BINARY_DIR)/exe

client.o: $(SOURCE_DIR)/client.c $(INCLUDE_DIR)/types.h $(INCLUDE_DIR)/libclient.h
	@echo "Compiling client program..."
	gcc -c $(FLAGS) $(SOURCE_DIR)/client.c -o $(OBJECT_DIR)/client.o

libmap: $(SOURCE_DIR)/libmap.c $(INCLUDE_DIR)/types.h $(INCLUDE_DIR)/libmap.h
	@echo "Compiling map lib..."
	gcc -c $(FLAGS) $(SOURCE_DIR)/libmap.c -o $(OBJECT_DIR)/libmap.o
	ar rv $(LIBRARY_DIR)/libmap.a $(OBJECT_DIR)/libmap.o

libclient: $(SOURCE_DIR)/libclient.c $(INCLUDE_DIR)/libclient.h $(INCLUDE_DIR)/types.h
	@echo "Compiling client lib..."
	gcc -c $(FLAGS) $(SOURCE_DIR)/libclient.c -o $(OBJECT_DIR)/libclient.o 
	ar rv $(LIBRARY_DIR)/libclient.a $(OBJECT_DIR)/libclient.o 

setup_map_sem:
	gcc -o $(SETUP_DIR)/initialize $(SETUP_DIR)/initialize.c $(SOURCE_DIR)/libmap.c -pthread

clean:
	@echo "Deleting all binaries, objects files and lib..."
	rm -rf $(BINARY_DIR)/* $(OBJECT_DIR)/* $(LIBRARY_DIR)/* $(SETUP_DIR)/initialize
