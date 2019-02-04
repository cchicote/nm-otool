#!/bin/bash
for filename in files_test/$1/*; do
	./script.sh "$filename"
done
