### Problem_2 Description

**Aim**: Learn basic file manipulation by creating a file-based database for storing and manipulating integers.

This folder contains the description and details for Problem 2. 
The problem consisted it creating a database mainly aimed at storing
integers and performing various operations on them.

This was done with the use of files to store the data persistently,
and various functions to manipulate and retrieve the data as needed.
The project also made used of in-memory loading as well as 
data structures like _hash tables_ to efficiently manage the integers in memory.

### Tasks Involved

The main tasks involved in this problem were:

1. **storing data**: Get a set of data from the user and store in a file.
2. **search data**: search for a specific piece of data in the file. 
	This was done by loading the data into memory and using a hash table for efficient searching.
	as search opertions could be frequent, are exact and as the scope of datais limited, this makes 
	this makes this method particularly effective.	
3. **Add data**: get a single piece of data from the user and add it to the file. The data 
    was also added to the in-memory hash table if already created, if not one was created.
4. **Read all data**: This action aimed at display all the content of the database file at a given instant.
	This was done by directly reading the file as this is the most efficient way to do so.

### Implementation Details

The project was implemented in C programming language, making use of standard file I/O operations,
and used functinons like `createDatabase` and `searchData` to create and search in the in-memory hash table respectively.
the type of hashing used was _multiplicative hashing_ to handle collisions effectively.