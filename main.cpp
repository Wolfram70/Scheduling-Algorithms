#include <iostream>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

void takeInputs(std::vector<Job> &jobs)
{
  int n;
  std::cout << std::endl << "Enter the number of jobs: ";
  std::cin >> n;
  std::cout << std::endl;
  std::cout << "Enter the jobs in the following format: " << std::endl;
  std::cout << "Job ID, Arrival Time, Burst Time, Priority\nNOTE: Lower number is higher priority" << std::endl << std::endl;
  for (int i = 0; i < n; i++)
  {
    int arrivalTime, burstTime, priority;
    char jobId;
    std::cin >> jobId >> arrivalTime >> burstTime >> priority;
    jobs.push_back(Job(arrivalTime, burstTime, priority, jobId));
  }
}


int main()
{
  //choose the algorithm
  int choice;
  std::cout << "Enter the choice of algorithm: " << std::endl;
  std::cout << "1. First Come First Served" << std::endl;
  std::cout << "2. Shortest Job First" << std::endl;
  std::cout << "3. Round Robin" << std::endl;
  std::cout << "4. Shortest Remaining Job First" << std::endl;
  std::cout << "5. Priority (Preemptive)" << std::endl;
  std::cout << "6. Priority (Non Preemptive)" << std::endl;
  std::cin >> choice;
  std::vector<Job> jobs;
  takeInputs(jobs);
  JobQueue jobQueue;
  //add all jobs
  for(int i = 0; i < jobs.size(); i++)
  {
    jobQueue.addJob(jobs[i]);
  }
  std::cout << std::endl;
  switch(choice)
  {
    case 1:
      jobQueue.FCFS();
      break;
    case 2:
      jobQueue.SJF();
      break;
    case 3:
      std::cout << "Enter the quantum size: ";
      int quantum;
      std::cin >> quantum;
      jobQueue.setQuantum(quantum);
      std::cout << std::endl;
      jobQueue.RR();
      break;
    case 4:
      jobQueue.SRJF();
      break;
    case 5:
      jobQueue.PP();
      break;
    case 6:
      jobQueue.PNP();
      break;
    default:
      std::cout << "Invalid choice" << std::endl;
  }
  jobQueue.displayGanttChart();
  return 0;
}
