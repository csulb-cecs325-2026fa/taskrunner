#include <iostream>
#include "tasks.h"
#include "taskparser.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: taskrunner TASK_FILENAME JOB [TASK_NAME]" << std::endl;
        return 9;
    }

    std::string taskFileName{argv[1]};
    std::string job{argv[2]};

    std::vector<Task> allTasks{};
    try {
        allTasks = parseTaskFile(taskFileName);
    }
    catch (std::exception& e) {
        std::cerr << "Error while reading task file: " << e.what() << std::endl;
        return 1; // Could not open task file.
    }

    // TODO: implement the list, run, and all jobs here.
    if (job == "list") {

    }
    // ...
}
