#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

/*******************PRIORITY NON PREEMPTIVE***********************/

void JobQueue::PNP()
{
    int time = 0;
    bool jobdone = false;

    Job* currentJob = nullptr;
    Job* prevJob = currentJob;
  
    std::vector<Job*> currentlyArrivedJobs;

    while(true)
    {
        for(int i = 0; i < jobs.size(); i++) jobs[i].step(time);
        if(currentJob)
        {
            jobdone = false;
            if(currentJob->isJobCompleted())
            {
                currentJob = nullptr;
                jobdone = true;
            }
            if(!jobdone)
            {
                time++;
                continue;
            }
        }
        currentlyArrivedJobs.clear();
        for(int i = 0; i < jobs.size(); i++)
        {
            if(jobs[i].isJobArrived() && !jobs[i].isJobCompleted())
            {
                currentlyArrivedJobs.push_back(&jobs[i]);
            }
        }
        std::sort(currentlyArrivedJobs.begin(), currentlyArrivedJobs.end(), [](const Job* a, const Job* b) { return a->getPriority() < b->getPriority(); });
        if(currentlyArrivedJobs.size() > 0) currentJob = currentlyArrivedJobs[0];
        if(currentJob) ganttChart.push_back(std::make_pair(currentJob, time));
        if(currentJob) currentJob->runJob();
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