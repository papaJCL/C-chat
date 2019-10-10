# To compile your code, do this command: make
# To produce a tar file, do this: make tar
# To clean up: make clean

# You are required to at least use -Wall for warnings.
# More -W flags are even better.

CXXFLAGS=-Wall -Werror -Wextra -Wfatal-errors

$(chat): $(chat).o
	g++ $(CXXFLAGS) -o $@ $^

tar:
	tar -cv $(MAKEFILE_LIST) *.cc >$(chat).tar

clean:
	rm -f $(chat) $(chat).tar *.o *.gch
