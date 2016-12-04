Rafael Takasu - rgt2108
COMS W4187 HW3
File Name Restrictions

INSTALLATION
make:
	to build
make clean:
	to clean

EXECUTION:
	$ sudo ./rgt2108.3 -c <config_file>
	run the program using 'sudo', since the program runs chroot and chroot requires root.
	the -c config_file is optional. If no config_file is given, the program uses the default config file. 

THE PROGRAM
This program reads in a series of lines, each containing two filenames. The first filename is an input file and the second is an output filename. The program copies the contents of the first file into the second file.

The program verifies that the input and output files are located in permitted areas. To specify to the program where the input and output areas are, you can pass in a config_file in the format:

DocumentRoot directory-name
OutputArea directory-name
Alias /name/ directory-name

To pass in the config file into the program, run the program with -c <config-file>.

The program first reads in the config file and parses it to save the input and output locations. It then prompts the user for the input and output file names in a loop. At each iteration of the loop, the program first checks if the input file is valid. It processes the file to replace any aliases specified in the config_file and any /../. If the resulting file path is inside the document_root or in one of the aliases' scopes, it is valid. Else, it is invalid. 

After validating the input file path and retrieving the contents of the input file, the program then calls another program to open the output file. The other program, /copyfile, simply takes in a file name and a string, and copies the string into the output file. The main program calls the /copyfile with 'chroot /copyfile <arguments' so that the /copyfile program runs in a chroot jail. This way, we know for sure that the output file will be inside the output area, since all other places are inaccessible to the program.  
