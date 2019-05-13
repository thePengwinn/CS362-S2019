Random tester tests the testme function using a random testing technique.  In theory it will run the function approximately 2,000,000 times before reaching an error.  Using the make all command will put all iterations into testmeiterations.out instead of printing to console which will greatly speed up the process.

Makefile commands

make all //will compile and run testme output goes it testmeiterations.out (more efficient then running in console)

make testme //will compile testme.c without running

make runtest // compile testme.c and run with console output (slower than using make all)

make coverage //must be run AFTER testme has been run- will show gcov and produce testmeresults.out with full gcov information

make clean //will delete all files that Makefile makes