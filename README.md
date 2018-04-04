# HashTable
A hashing project I took on for my CS II for majors class.
I created a hash table in C++ using a HashTable class, wherein the hash table itself was a vector of type Struct (each bucket in the hash table is of type Struct). In my Struct, I had a string to contain the key (word being searched for) and a vector of type int, where I would store the line numbers that the key occured on. I implemented linear probing, quadratic probing, and double hashing. I used the famed "djb2" hash function. 
