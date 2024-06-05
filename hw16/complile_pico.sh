#!/bin/bash

# Check if at least one argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 folder1 [folder2 ...]"
    exit 1
fi

# Store the current directory as directory1
directory1=$(pwd)

# Check if the build directory exists in directory1, if not, create it
if [ ! -d "$directory1/build" ]; then
    mkdir "$directory1/build"
fi

# Loop through each argument provided to the script
for folder in "$@"; do
    # Define path to pico-examples directory
    pico_examples_dir=~/northwesternCourses/mech433/pico/pico-examples

    # Go to the pico-examples directory
    cd "$pico_examples_dir" || exit

    # Remove the final line from CMakeLists.txt
    sed -i '$ d' CMakeLists.txt

    # Append new line with add_subdirectory command
    echo "add_subdirectory($directory1/$folder $folder)" >> CMakeLists.txt

    # Run the cmake command
    cmake .

    # Move into the newly created folder
    cd "$folder"

    # Run the make command

    make

    # Move back to directory1
    cd "$directory1" || exit

    # Check if the target directory exists in the build directory, remove it if it does
    if [ -d "$directory1/build/$folder" ]; then
        rm -rf "$directory1/build/$folder"
    fi

    # Check if a folder with the current name exists in the pico-examples directory, then move it
    if [ -d "$pico_examples_dir/$folder" ]; then
        # Move the folder to the build directory, overwrite if necessary
        mv -f "$pico_examples_dir/$folder" "$directory1/build/"
    else
        echo "Folder $pico_examples_dir/$folder does not exist."
    fi
done

