#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Process {
    std::string process_name;
    int arrival_time;
    int burst_time;
    int completion_time;
    int remaining;
};

// Functor for sorting processes by arrival time
struct ArrivalTimeComparator {
    bool operator()(const Process& a, const Process& b) const {
        return a.arrival_time < b.arrival_time;
    }
};

// Function to perform Round Robin scheduling for a given queue
void roundRobinScheduling(std::vector<Process>& processQueue, int quantum_time, int& total_query_time) {
    int n = processQueue.size();
    int time = 0; // Track the current time

    while (true) {
        bool allProcessesCompleted = true;

        for (int i = 0; i < n; i++) {
            if (processQueue[i].remaining > 0) {
                allProcessesCompleted = false;

                if (processQueue[i].remaining <= quantum_time) {
                    time += processQueue[i].remaining;
                    total_query_time += time - processQueue[i].arrival_time;
                    processQueue[i].completion_time = time;
                    processQueue[i].remaining = 0;
                } else {
                    time += quantum_time;
                    processQueue[i].remaining -= quantum_time;
                }
            }
        }

        if (allProcessesCompleted) {
            break;
        }
    }
}

int main() {
    int select_queue, no_of_process;
    int total_query_time = 0; // Variable to store total query time

    std::cout << "Please choose a queue to post your query:\n";
    std::cout << "1. FACULTY queue\n";
    std::cout << "2. STUDENT queue\n";
    std::cout << "> ";
    std::cin >> select_queue;

    std::vector<Process> processQueue;

    if (select_queue == 1) {
        std::cout << "Enter the number of processes for FACULTY queue: ";
        std::cin >> no_of_process;

        processQueue.resize(no_of_process);

        for (int i = 0; i < no_of_process; i++) {
            std::cout << "Enter the details of Process[" << i + 1 << "]\n";
            std::cout << "Process Name: ";
            std::cin >> processQueue[i].process_name;
            std::cout << "Arrival Time: ";
            std::cin >> processQueue[i].arrival_time;
            std::cout << "Burst Time: ";
            std::cin >> processQueue[i].burst_time;
            processQueue[i].remaining = processQueue[i].burst_time; // Initialize remaining time
        }

        // Sort processes by arrival time using the ArrivalTimeComparator functor
        std::sort(processQueue.begin(), processQueue.end(), ArrivalTimeComparator());
    } else if (select_queue == 2) {
        std::cout << "Enter the number of processes for STUDENT queue: ";
        std::cin >> no_of_process;

        processQueue.resize(no_of_process);

        for (int i = 0; i < no_of_process; i++) {
            std::cout << "Enter the details of Process[" << i + 1 << "]\n";
            std::cout << "Process Name: ";
            std::cin >> processQueue[i].process_name;
            std::cout << "Arrival Time: ";
            std::cin >> processQueue[i].arrival_time;
            std::cout << "Burst Time: ";
            std::cin >> processQueue[i].burst_time;
            processQueue[i].remaining = processQueue[i].burst_time; // Initialize remaining time
        }

        // Sort processes by arrival time using the ArrivalTimeComparator functor
        std::sort(processQueue.begin(), processQueue.end(), ArrivalTimeComparator());
    } else {
        std::cout << "Please select the correct option by running the program again.\n";
        return 1;  // Exit with an error code
    }

    int quantum_time;
    std::cout << "Enter the quantum time: ";
    std::cin >> quantum_time;

    // Perform Round Robin scheduling for the chosen queue
    roundRobinScheduling(processQueue, quantum_time, total_query_time);

    // Print the results
    std::cout << "\n\t\t\t********************************************\n";
    std::cout << "\t\t\t*****   ROUND ROBIN ALGORITHM OUTPUT   *****\n";
    std::cout << "\t\t\t********************************************\n";
    std::cout << "\n|\tProcess Name\t  |\tArrival Time\t  |\tBurst Time\t |\tCompletion Time  |\tWaiting Time\t |\tTurnaround Time\t |\n";

    for (int i = 0; i < processQueue.size(); i++) {
    	int waiting_time = processQueue[i].completion_time - processQueue[i].burst_time - processQueue[i].arrival_time;
    	if (waiting_time < 0) {
        waiting_time = 0; // Ensure waiting time is non-negative
    	}
    
    	int turnaround_time = processQueue[i].completion_time - processQueue[i].arrival_time;
    	std::cout << "|\t  " << processQueue[i].process_name << "\t    |\t  " << processQueue[i].arrival_time
              << "\t   |\t  " << processQueue[i].burst_time << "\t   |\t  " << processQueue[i].completion_time
              << "\t   |\t  " << waiting_time << "\t   |\t  " << turnaround_time << "\t   |\n";
	}



    // Calculate and print the average query time
    double average_query_time = static_cast<double>(total_query_time) / processQueue.size();
    std::cout << "\nAverage Query Time: " << average_query_time << std::endl;

    return 0;
}