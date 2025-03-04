#include <iostream>
#include <string>
#include <vector> //Works like arrays, but can be resized
#include <array> //Works like arrays, but can't be resized
struct Task {
    std::string descr;
    int loc;
    bool completed;
};

// Display the current state of the kanban board.

Task addTask(std::array<std::vector<Task>, 4> &kanbanBoard)//, bool completed=false) 
    //const tells the compiler that the function will not modify the string
    //& is a reference to the string, which is more efficient than passing the string by value
    //std means an object or function is part of the standard library
{
    Task newTask;
    std::cout << "Enter task description: ";
    //std::cin >> newTask.descr;
    std::cin.ignore();
    std::getline(std::cin, newTask.descr);
    //newTask.descr = descr; //Assign the description
    //newTask.loc = loc; //Assign the location backlog
    //newTask.completed = completed; //Assign the completion status
    kanbanBoard[0].push_back(newTask); //Add the task to the kanban board
    return newTask;
}

void completeTask(std::array<std::vector<Task>, 4> &kanbanBoard)
{
    int stage;
    std::cout << "Enter stage number:\n";
    std::cout << "1. Backlog\n";
    std::cout << "2. Doing\n";
    std::cout << "3. Review\n";
    std::cout << "4. Done\n";
    std::cin >> stage;

    stage = stage - 1; //Adjust for 0-based index

    if (kanbanBoard[stage].empty())
    {
        std::cout <<"There are no tasks in this stage.\n" << std::endl;
    }
    else 
    {
        std::cout <<"Tasks in the selected stage:\n";
        for (size_t i = 0; i < kanbanBoard[stage].size(); i++)
            //size_t is an unsigned integer type used to represent the size of objects or indices in containers.
        {
            std::cout << i << ". " << kanbanBoard[stage][i].descr << std::endl;
        }
    }

    //Choose a task to complete
    int taskIndex;
    std::cout <<"Enter the task number to complete: ";
    std::cin >> taskIndex;

    //Remove the task from the selected stage
    Task task = std::move(kanbanBoard[stage][taskIndex]);
            //This line creates a new Task object named task by "moving" the task located at kanbanBoard[stage][taskIndex].
            //std::move: It signals that the contents of kanbanBoard[stage][taskIndex] can be transferred to the new task without copying. 
            //This is more efficient, especially if Task has resource-intensive members.
            //The task is now held in task and is ready to be manipulated independently.
    kanbanBoard[stage].erase(kanbanBoard[stage].begin() + taskIndex);
            //This line removes the task from the kanban board by erasing the element at the specified index.
            //The task is no longer in the kanban board but is still accessible through the task variable.

    //Add the task to the next stage if not already in the last stage
    if (stage < static_cast<int>(kanbanBoard.size()-1))
    {
        task.loc = stage + 1;
        kanbanBoard[stage + 1].push_back(task);
        std::cout <<"Task moved to stage " << task.loc << std::endl;
    }
    else
    {
        std::cout <<"Task is done and removed.\n";
    }
}

void deleteTask(std::array<std::vector<Task>, 4> &kanbanBoard)
{
    int stage;
    std::cout << "Enter stage number:\n";
    std::cout << "1. Backlog\n";
    std::cout << "2. Doing\n";
    std::cout << "3. Review\n";
    std::cout << "4. Done\n";
    std::cin >> stage;

    stage = stage - 1; //Adjust for 0-based index

    if (kanbanBoard[stage].empty())
    {
        std::cout <<"There are no tasks in this stage.\n" << std::endl;
    }
    else 
    {
        std::cout <<"Tasks in the selected stage:\n";
        for (size_t i = 0; i < kanbanBoard[stage].size(); i++)
        {
            std::cout << i  << ". " << kanbanBoard[stage][i].descr << std::endl;
        }
    }

    //Choose a task to delete
    int taskIndex;
    std::cout <<"Enter the task number to delete: ";
    std::cin >> taskIndex;

    //Remove the task from the selected stage
    kanbanBoard[stage].erase(kanbanBoard[stage].begin() + taskIndex);
    std::cout <<"Task deleted.\n";
}

int main() {
    //Create an array of 4 vectors to hold tasks for each location.
    //The array is immutable, but the vectors can be resized. This means we will always have 4 stages/vectors.
    //The vectors can be resized to hold as many tasks as needed.
    std::array<std::vector<Task>, 4> kanbanBoard;

    std::cout << "Welcome to your To-Do list" << std::endl;
    int choice;

    do {
        std::cout << "\nTo-Do List Menu\n";
        std::cout << "1. Display Kanban Board\n";
        std::cout << "2. Add Task\n";
        //std::cout << "3. Edit Task\n";
        std::cout << "3. Complete Task\n";
        std::cout << "4. Delete Task\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        

        switch (choice) {
            case 1:
                displayKanbanBoard(kanbanBoard);
                break;
            case 2:
                addTask(kanbanBoard);
                break;
            case 3:
                completeTask(kanbanBoard);
                break;
            case 4:
                deleteTask(kanbanBoard);
                break;
            case 5:
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);
    
    return 0;
}

//parallels@ubuntu-linux-2404:~/Softwareudvikling/To-Do_list$ g++ main.cpp -o main
//parallels@ubuntu-linux-2404:~/Softwareudvikling/To-Do_list$ ./main