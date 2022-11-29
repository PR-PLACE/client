#! /bin/bash

# This script is used to setup the environment for the PR-PLACE

echo "--------------------------------------------------------------------------------"
echo "Setting up the environment for PR-PLACE"
echo "--------------------------------------------------------------------------------"
echo "Compiling sources..."
cd ../ && make setup_map_shared && cd setup
echo 'Compiling done'
echo "--------------------------------------------------------------------------------"

#Create the reference file for shared memory
echo "Creating the reference file for shared memory..."
touch ../pr-place-map
echo "Reference file created"

# Running the script setup to create the white map and create the shared memory for clients
echo "Running setup script..."
./initialize
echo "Initial script done (Map and shared created)"
echo "--------------------------------------------------------------------------------"

echo "Setup script done"

echo "You can now use the exectuable ./bin/prplace to run the PR-PLACE"

