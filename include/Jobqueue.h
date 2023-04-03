#ifndef JOBQUEUE_H
#define JOBQUEUE_H

#include "Job.h"

class JobQueue
{
private:
  std::vector<Job> jobs;
  std::vector<std::pair<Job*, int>> ganttChart;
  int quantum = 2;
public:
  JobQueue() {}
  void addJob(Job job) { jobs.push_back(job); }
  void setQuantum(int q) { quantum = q; }
  void reset()
  {
    for (auto& job : jobs)
    {
      job.reset();
    }
    ganttChart.clear();
  }
  void prepare()
  {
    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) { return a.getArrivalTime() < b.getArrivalTime(); });
  }
  void displayGanttChart();
  void printDetails()
  {
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;
    int totalJobs = jobs.size();
    for (int i = 0; i < jobs.size(); i++)
    {
      totalWaitingTime += jobs[i].getWaitingTime();
      totalTurnAroundTime += jobs[i].getTurnAroundTime();
    }

    std::cout << std::endl << "START TIMES:\n";
    for(int i = 0; i < jobs.size(); i++)
    {
      std::cout << jobs[i].getId() << " : " << jobs[i].getStartTime() << "       ";
      if(jobs[i].getStartTime() > 9) std::cout << "\b";
    }
    std::cout << std::endl;

    std::cout << std::endl << "FINISH TIMES:\n";
    for(int i = 0; i < jobs.size(); i++)
    {
      std::cout << jobs[i].getId() << " : " << jobs[i].getCompleteTime() << "       ";
      if(jobs[i].getCompleteTime() > 9) std::cout << "\b";
    }
    std::cout << std::endl;

    std::cout << std::endl << "WAITING TIMES:\n";
    for(int i = 0; i < jobs.size(); i++)
    {
      std::cout << jobs[i].getId() << " : " << jobs[i].getWaitingTime() << "       ";
      if(jobs[i].getWaitingTime() > 9) std::cout << "\b";
    }
    std::cout << std::endl;

    std::cout << std::endl << "TURN AROUND TIMES:\n";
    for(int i = 0; i < jobs.size(); i++)
    {
      std::cout << jobs[i].getId() << " : " << jobs[i].getTurnAroundTime() << "       ";
      if(jobs[i].getTurnAroundTime() > 9) std::cout << "\b";
    }
    std::cout << std::endl;

    std::cout << std::endl << "AVERAGES: \n";

    std::cout << "Average waiting time: " << float(totalWaitingTime) / float(totalJobs) << std::endl;
    std::cout << "Average turn around time: " << float(totalTurnAroundTime) / float(totalJobs) << std::endl;
  }
  void FCFS(); // First Come First Serve
  void SJF(); // Shortest Job First
  void RR(); // Round Robin
  void SRJF(); // Shortest Remaining Job First
  void PP(); // Priority Preemptive
  void PNP(); // Priority Non-Preemptive
};
#endif