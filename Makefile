#To compile your code, do this command: make
# To produce a tar file, do this: make tar
# To clean up: make clean

# You are required to at least use -Wall for warnings.
# More -W flags are even better.

CXXFLAGS=-Wall -Wextra -Wfatal-errors
assignment=chat

$(assignment): $(assignment).o
	g++ $(CXXFLAGS) -o $@ $^

tar:
	tar -cv $(MAKEFILE_LIST) *.cc >$(assignment).tar

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch
