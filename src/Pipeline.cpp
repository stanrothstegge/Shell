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

	for( SimpleCommand *cmd : commands ) {

        cmd->execute();

	}
}
