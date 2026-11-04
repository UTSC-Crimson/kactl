# hash, Enter, paste code, Enter, Ctrl+D. Ignores whitespace
# and comments. Compare with the hash printed by the snippet.
hash() { cpp -dD -P -fpreprocessed | tr -d '[:space:]' \
	| md5sum | cut -c-6; }
