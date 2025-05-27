#!/bin/bash

echo -n "Enter your name: "
IFS= read -r name
if [ -z "$name" ]; then
    echo "Hello, tmpuser?"
else
    echo "Hello, $name!"
fi