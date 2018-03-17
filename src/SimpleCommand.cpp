#include <iostream>
#include <unistd.h>
#include "SimpleCommand.h"

char* cwd() {
	char cwd[5012];
	//Prints the current working directory
	return getcwd(cwd, sizeof(cwd));
}
/**
 * SIMPLECOMMAND
 * A command that is part of a pipeline.
 * Commands can be builtin (like cd or exit) or programs that should be executed.
 *
 * All streams (stdout, stdin, stderr) of the command can be redirected to either
 * another stream or a file. For example, input can be taken from a file instead
 * of the keyboard, or errors from stderr can be written to a file instead of the
 * console.
 * IORedirections are always executed in order, from left to right.
 */
void SimpleCommand::execute() {
	// The given command is accessible as a std::string named command
	// Switch through the possible commands looking for our given command
	if (command == "pwd") {
		char *path = cwd();
		if (!path) {
			std::cerr << strerror(errno) << std::endl;
		} else {
			std::cout << "Your current working directory is: " << path << std::endl;
		}
	} else if (command == "cd") {
		unsigned long arg_size = arguments.size();
		if (arg_size > 1) {
			std::cerr << strerror(errno) << std::endl;
		} else if (arg_size == 0) {
			if (chdir(getenv("HOME")) == EXIT_FAILURE) {
				std::cerr << strerror(errno) << std::endl;
			}
		} else {
			std::cout << arguments[0].c_str() << std::endl;
			if (chdir(arguments[0].c_str()) == EXIT_FAILURE) {
				std::cerr << strerror(errno) << std::endl;
			}
		}
	} else if (command == "help" || command == "?") {
		std::cout << "\n- - - - - - - -[ Bash Assist ]- - - - - - - -" << std::endl;
		std::cout << "Authors:\n\t- Marnick van der Arend\n\t- Roel Kolkhuis Tanke\n" << std::endl;
		std::cout << "Bash sequence syntax:\n\tCOMMAND (| COMMAND)* (; SEQUENCE | &)" << std::endl;
		std::cout << "\nBuiltin commands:" << std::endl;
		std::cout << "pwd         : print current working directory" << std::endl;
		std::cout << "cd [to_dir] : change working directory" << std::endl;
		std::cout << "help | ?    : you\'re in it ;)" << std::endl;
		std::cout << "\n- - - - - - - -[ End of file ]- - - - - - - -\n" << std::endl;
	} else {
		std::cout << "Unknown command! Type \'help\' for available commands" << std::endl;
	}
	// CASE: <The given command>
	// Check the validity of the given arguments
	// Check the validity of the given redirects
	// Execute the required function and redirect its result
	// End of switch

}
