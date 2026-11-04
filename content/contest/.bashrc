alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++20 \
	-fsanitize=undefined,address -DLOCAL'
# hash A.cpp 12 40: hash of lines 12-40, ignoring whitespace
# and comments. Compare with the hash printed by each snippet.
hash() { sed -n "$2,$3p" "$1" | cpp -dD -P -fpreprocessed \
	| tr -d '[:space:]' | md5sum | cut -c-6; }
