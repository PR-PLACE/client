#! /bin/bash

# This script is used to setup the environment for the PR-PLACE

semaphore_file="sem.PR_PLACE"
map_file="map.bin"

shared_memory_file="pr-place.shm"

player_username="player"
player_password="prs2223"

echo "--------------------------------------------------------------------------------"
echo "Setting up the environment for PR-PLACE"
echo "--------------------------------------------------------------------------------"
echo "Compiling sources..."
mkdir -p ../bin ../objects ../lib ../maps ../logs
cd ../ && make && cd setup
chmod 4555 ../bin/exe 
echo 'Compiling done'
echo "--------------------------------------------------------------------------------"


#Create the reference file for shared memory
echo "Creating the reference file for shared memory..."
touch ../$shared_memory_file
echo "Reference file created"
echo "--------------------------------------------------------------------------------"

# Running the script setup to create the white map and create the named semaphore for the map
#test if the map already exists
if [ -f ../maps/$map_file ] && [ -f /dev/shm/$semaphore_file ]; then
    echo "Map and semaphore already exist"
else
    echo "Running setup script..."
    echo "Creating the map and the semaphore..."
    ./initialize
    echo "Initial script done (Map and sem created)"
    
fi
echo "--------------------------------------------------------------------------------"

#Create the user player
echo "Creating the player user"
egrep "^player" /etc/passwd >/dev/null
if [ $? -eq 0 ]; then   
    echo "User player already exist"
else
    password=$(perl -e 'print crypt($ARGV[0], "password")' $player_password)
    useradd -m -p "$password" "$player_username"
    if [ $? -ne 0 ]; then
        echo "Player account created"
    fi
    ln -s ../bin/exe /home/player/PR-PLACE
    sed -i 's/:\/home\/player:\/bin\/sh/:\/home\/player:\/bin\/bash/g' /etc/passwd
fi
echo "--------------------------------------------------------------------------------"

echo "Setup script done"

echo "You can now use the exectuable ./bin/prplace to run the PR-PLACE"

