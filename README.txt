When a system login manager has a password, the most basic way of storing it is just to check if the password is correct with an internal data structure. 
However this can easily be stolen and used for nefarious use. 
Instead most systems keep a  table that stores the encrypted password for each user. 
So when a user inputs their password, it is encrypted and then sees if the encrypted password is the same as the one that is stored in a login database.



This project aimed for us to be able to figure out a password given the symbol tables to encrypt the password.

The encrypter must be compiled using :
g++ -std=c++11 -DUSE_C_CHARS -o encrypt encrypt.cpp
with C being the number of characters in the password

We first had to create a brute force solution that tries every single possible combination that could work as a result of running the encrypted passwor through the symbol table.
This is achieved by taking the subset sum of the brute forced string and an entry in the symbol table and see if the key is equal to that of the password.
Of course this is really ineffecient as there are 32 million different combinations for a 5 character password that only uses the lowercase alphabet and the numbers 0-5.
 
 This brute force solution compiled is run by using:
 g++ -std=c++11 -O2 -DUSE_<C>_CHARS -o brute brute.cpp
 ./brute <encrypted> <table_filename>
 Note that C is the number of characters


In order to create a more efficient solution, I had to take a subset of the table given,compute all the possible subsets and then put those values into another symbol table which I would use to check all the possibilities with a small amount of lookups.

the efficient solution must be computed using:
g++ -std=c++11 -O2 -DUSE_C_CHARS -o symbol symbol.cpp
and run with:
./symbol <encrypted password> <table>
Note that C is the number of characters
