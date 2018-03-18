#include <iostream>
#include <unistd.h>
#include <fstream>
#include "SimpleCommand.h"

char *cwd() {
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

    for (int j = 0; j < redirects.size(); j++) {
        IORedirect red = redirects[j];

        if (red.getNewFile() == "&1") {
            dup2(STDERR_FILENO, STDOUT_FILENO);
        } // else ... TODO
    }

    // TODO: Redirect function result

    if (command == "exit") {
        exit(0);
    } else if (command == "pwd") {
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
        std::cout << "exit        : Exit the shell" << std::endl;
        std::cout << "\n- - - - - - - -[ End of file ]- - - - - - - -\n" << std::endl;
    } else {
        char *cmd = (char *) command.c_str();
        char *argv[arguments.size() + 2];

        // Set up argv array
        argv[0] = cmd;
        for (int i = 1; i < arguments.size() + 1; i++) {
            argv[i] = (char *) arguments[i - 1].c_str();
        }
        argv[arguments.size() + 1] = NULL;

        pid_t pid;
        int status;

        // Create new process for the command and wait for it to finish
        if ((pid = fork()) < 0) {
            std::cerr << "Forking child failed" << std::endl;
        } else if (pid == 0) {
            if (execvp(cmd, argv) < 0) {
                std::cout << "Command not found! Try \'help\' or \'?\'" << std::endl;
            }
        } else while (wait(&status) != pid);
    }
}