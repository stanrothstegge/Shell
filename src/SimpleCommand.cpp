#include <iostream>
#include "SimpleCommand.h"

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
	std::cout << "FIXME: You should change SimpleCommand::execute()" << std::endl;
	// The given command is accessible as a std::string named command
	// Switch through the possible commands looking for our given command

        // CASE: <The given command>
        // Check the validity of the given arguments

        // Check the validity of the given redirects

        // Execute the required function and redirect its result

    // End of switch
}
