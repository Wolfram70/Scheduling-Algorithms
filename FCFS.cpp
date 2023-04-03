#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

/*******************FIRST COME FIRST SERVE*********************/

void JobQueue::FCFS()
{
  int time = 0;
  while (true)
  {
    for(int i = 0; i < jobs.size(); i++) jobs[i].step(time);
    bool isAllJobsCompleted = true;
    for (int i = 0; i < jobs.size(); i++)
    {
      if (!jobs[i].isJobCompleted())
      {
        isAllJobsCompleted = false;
        break;
      }
    }
    if (isAllJobsCompleted)
      break;
    for (int i = 0; i < jobs.size(); i++)
    {
      if(jobs[i].isJobCompleted())
        continue;
      if (jobs[i].isJobRunning())
        break;
      if ((jobs[i].getArrivalTime() <= time) && (!jobs[i].isJobCompleted()))
      {
        jobs[i].runJob();
        ganttChart.push_back(std::make_pair(&jobs[i], time));
        break;
      }
    }
    time++;
  }
  printDetails();
}