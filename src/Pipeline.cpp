#include <iostream>
#include "Pipeline.h"
#include "SimpleCommand.h"

/**
 * PIPELINE
 * A pipeline, i.e. a set of simple commands of which the output of each previous
 * command is fed as the input to the next.
 * Note that you can have a pipeline with just a single command in which case it
 * is simply executed as is.
 */

/**
 * Destructor.
 */
Pipeline::~Pipeline() {
	for( SimpleCommand *cmd : commands )
		delete cmd;
}

/**
 * Executes the commands on this pipeline.
 */
void Pipeline::execute() {
	std::cout << "FIXME: You should change Pipeline::execute()" << std::endl;

	for( SimpleCommand *cmd : commands ) {
		// FIXME: Probably need to set up some pipe here?
        // Initialize pipe, this can simply be done by creating an array
        int pipe1[2];
        // Create the pipe, pipe() is a Linux command
        pipe(pipe1);

        // Create the child process (this copies the parents process file descriptor table to the child process's descriptor table)
        int returnValue = fork();

        if (returnValue == 0)
            // Execute child process


        // Note: Dup2 is een handige linux functie,
        // Simpele betekenis: dup2(a,b) = zorg ervoor dat b ook verbonden is met hetgene waar A mee verbonden is
        // Hiermee kan de output van een programma bijv verbonden worden met de input van een pipe


        // Maybe check for async and do something?

		cmd->execute();
	}
}
