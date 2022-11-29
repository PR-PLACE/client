#! /bin/bash

# This script is used to setup the environment for the PR-PLACE

echo "Setting up the environment for PR-PLACE"

echo "Compiling sources..."
make
echo 'Compiling done'

# Running the script setup to create the white map and create the shared memory for clients
echo "Running setup script..."
./bin/initialize
echo "Initial script done (Map and shared created)"

echo "Setup script done"

echo "You can now use the exectuable ./bin/prplace to run the PR-PLACE"

