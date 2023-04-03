#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

/*******************SHORTEST REMAINING JOB FIRST***********************/

void JobQueue::SRJF()
{
    int time = 0;

    Job* currentJob = nullptr;
    Job* prevJob = currentJob;
  
    std::vector<Job*> currentlyArrivedJobs;

    while(true)
    {
        for(int i = 0; i < jobs.size(); i++) jobs[i].step(time);
        currentlyArrivedJobs.clear();
        for(int i = 0; i < jobs.size(); i++)
        {
            if(jobs[i].isJobArrived() && !jobs[i].isJobCompleted())
            {
                currentlyArrivedJobs.push_back(&jobs[i]);
            }
        }
        std::sort(currentlyArrivedJobs.begin(), currentlyArrivedJobs.end(), [](const Job* a, const Job* b) { return a->getLeftTime() < b->getLeftTime(); });
        prevJob = currentJob;
        if(currentJob)
        {
            if(!currentJob->isJobCompleted()) currentJob->pauseJob();
        }
        currentJob = currentlyArrivedJobs[0];
        if(currentJob != prevJob)
        {
            ganttChart.push_back(std::make_pair(currentJob, time));
        }
        currentJob->runJob();
        time++;
        bool allJobsCompleted = true;
        for(int i = 0; i < jobs.size(); i++)
        {
            if(!jobs[i].isJobCompleted())
            {
                allJobsCompleted = false;
                break;
            }
        }
        if(allJobsCompleted) break;
    }
    printDetails();
}