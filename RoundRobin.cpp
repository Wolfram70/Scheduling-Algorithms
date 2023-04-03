#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

/*************************ROUND ROBIN**************************/

void JobQueue::RR()
{
  int time = 0;
  bool alreadyInQueue = false;
  while(true)
  {
    for(int i = 0; i < jobs.size(); i++) jobs[i].step(time);
    std::vector<Job*> currentlyArrivedJobs;
    for(int i = 0; i < jobs.size(); i++)
    {
      if(jobs[i].isJobArrived() && !jobs[i].isJobCompleted())
      {
        currentlyArrivedJobs.push_back(&jobs[i]);
      }
    }
    Job* job = nullptr;
    while(!currentlyArrivedJobs.empty())
    {
      job = currentlyArrivedJobs[0];
      job->runJob();
      ganttChart.push_back(std::make_pair(job, time));
      for(int j = 0; j < quantum; j++)
      {
        time++;
        for(int k = 0; k < jobs.size(); k++) jobs[k].step(time);
        if(job->isJobCompleted())
        {
          break;
        }
      }
      if(job->isJobCompleted())
      {
        for(int i = 0; i < jobs.size(); i++)
        {
          alreadyInQueue = false;
          for(int j = 0; j < currentlyArrivedJobs.size(); j++)
          {
            if(&jobs[i] == currentlyArrivedJobs[j])
            {
              alreadyInQueue = true;
              break;
            }
          }
          if(alreadyInQueue) continue;
          if(jobs[i].isJobArrived() && !jobs[i].isJobCompleted() && &jobs[i] != job)
          {
            currentlyArrivedJobs.push_back(&jobs[i]);
          }
        }
        currentlyArrivedJobs.erase(currentlyArrivedJobs.begin());
        continue;
      }
      job->pauseJob();
      for(int i = 0; i < jobs.size(); i++)
      {
        alreadyInQueue = false;
        for(int j = 0; j < currentlyArrivedJobs.size(); j++)
        {
          if(&jobs[i] == currentlyArrivedJobs[j])
          {
            alreadyInQueue = true;
            break;
          }
        }
        if(alreadyInQueue)
          continue;
        if(jobs[i].isJobArrived() && !jobs[i].isJobCompleted())
        {
          currentlyArrivedJobs.push_back(&jobs[i]);
        }
      }
      currentlyArrivedJobs.push_back(job);
      currentlyArrivedJobs.erase(currentlyArrivedJobs.begin());
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
    time++;
  }
  printDetails();
}