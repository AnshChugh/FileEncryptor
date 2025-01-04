#!/bin/bash
# script to generate test directory with random messages

create_test_directory() {
    local directory_name=$1
    local num_files=$2

    if [ ! -d "$directory_name" ]; then
        mkdir -p "$directory_name"
    fi

    for ((i=1; i<=num_files; i++)); do
        file_name="file_$i.txt"
        file_path="$directory_name/$file_name"
        tr -dc 'A-Za-z0-9' < /dev/urandom | head -c 150 > "$file_path"
    done
}

create_test_directory "test" 60