#include <iostream>
#include <unistd.h>
#include "Pipeline.h"
#include "SimpleCommand.h"

#define READ_END 0
#define WRITE_END 1

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
    for (SimpleCommand *cmd : commands)
        delete cmd;
}

/**
 * Executes the commands on this pipeline.
 */
void Pipeline::execute() {
//
//    for (SimpleCommand *cmd : commands){
//        cmd->execute();
//    }

    int pipefd[2];

    // Create an unnamed pipe
    if (pipe(pipefd) == -1) {
        fprintf(stderr, "parent: Failed to create pipe\n");
    }

    for (int i = 0; i < commands.size(); i++) {

        // Fork a process to run
        int pid = fork();

        if (pid == -1) {
            fprintf(stderr, "parent: Could not fork process\n");
        } else if (pid == 0) {
            fprintf(stdout, "child: child will now run: %d\n", i);

            // Set fd[0] (stdin) to the read end of the pipe
            if (dup2(pipefd[READ_END], STDIN_FILENO) == -1) {
                fprintf(stderr, "child: read dup2 failed\n");
            }

            // Set fd[1] (stdout) to the write end of the pipe
            if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1) {
                fprintf(stderr, "child: write dup2 failed\n");
            }

            // Close the pipe now that we've duplicated it
            close(pipefd[READ_END]);
            close(pipefd[WRITE_END]);

            // Execute cmd
            commands[i]->execute();
        }
    }

    // Parent doesn't need the pipes
    close(pipefd[READ_END]);
    close(pipefd[WRITE_END]);

    // Wait for all children to finish
    while (wait(NULL) > 0);
}
