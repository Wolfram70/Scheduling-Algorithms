#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

/*******************SHORTEST JOB FIRST***********************/

void JobQueue::SJF()
{
  int time = 0;

  Job* currentJob = nullptr;
  
  while(true)
  {
    for(int i = 0; i < jobs.size(); i++) jobs[i].step(time);
    if(currentJob != nullptr)
    {
      if(!currentJob->isJobCompleted())
      {
        time++;
        continue;
      }
      else
      {
        currentJob = nullptr;
      }
    }
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

    int minBurstTime = -1, minBurstTimeIndex;
    for(int i = 0; i < jobs.size(); i++)
    {
      if(jobs[i].isJobCompleted())
        continue;
      if(!jobs[i].isJobArrived())
        continue;
      minBurstTime = jobs[i].getBurstTime();
      minBurstTimeIndex = i;
      break;
    }
    if(minBurstTime == -1)
    {
      for(int i = 0; i < jobs.size(); i++)
      {
        jobs[i].step(time);
      }
      time++;
      continue;
    }
    for(int i = 0; i < jobs.size(); i++)
    {
      if(jobs[i].isJobCompleted())
        continue;
      if(!jobs[i].isJobArrived())
        continue;
      if(jobs[i].getBurstTime() < minBurstTime)
      {
        minBurstTime = jobs[i].getBurstTime();
        minBurstTimeIndex = i;
      }
    }
    currentJob = &jobs[minBurstTimeIndex];
    currentJob->runJob();
    ganttChart.push_back(std::make_pair(currentJob, time));
    time++;
  }
  printDetails();
}