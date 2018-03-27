Runs a multithreaded program that accesses a shared variable with synced or unsynced threads

COMPILATION:
# Make the program into executeable
make 

# Make the program into executeable with synced threads 
make CPPFLAGS=-DPTHREAD_SYNC  

# Clean the directory of object files and binaries
make clean 

USAGE:
./multi_thread num_threads # Ex: ./multi_thread 4 runs the program with 4 threads
