#include <iostream>
#include <unistd.h>
#include "Sequence.h"
#include "Pipeline.h"
/**
 * SEQUENCE
 * Top-level class for an entered line in our shell.
 * Contains a list of pipelines to execute in order.
 */

/**
 * Destructor.
 */
Sequence::~Sequence() {
    for (Pipeline *p : pipelines)
        delete p;
}

/**
 * Executes a sequence, i.e. runs all pipelines and - depending if the ampersand
 * was used - waits for execution to be finished or not.
 */
void Sequence::execute() {

    pid_t pid;

    for (Pipeline *p : pipelines) {

        // Check for asynchronous pipeline
        if (p->isAsync()) {
            pid = fork();

            if (pid == 0) {
                p->execute();
            }
        } else p->execute();
    }
}
