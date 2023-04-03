#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "include/Jobqueue.h"

/******************************DISPLAY GANTT CHART******************************/

void JobQueue::displayGanttChart()
{
    std::cout << std::endl << "GANTT CHART" << std::endl;
    //print the top bar
    std::cout << " ";
    for(int i = 0; i < ganttChart[ganttChart.size() - 1].first->getCompleteTime(); i++)
    {
        std::cout << "--";
    }
    std::cout << "\b \n|";

    //print the process ids
    int cursor = 0;
    std::vector<std::pair<int, bool>> numLoc;
    numLoc.push_back(std::make_pair(cursor, true));
    cursor++;
    for(int i = 0; i < ganttChart.size(); i++)
    {
        Job job = *ganttChart[i].first;
        int start = ganttChart[i].second;
        int end = (i == ganttChart.size() - 1 ? job.getCompleteTime() : ganttChart[i + 1].second);
        int lengthC = end - start;
        bool emptyspace = false;
        if(end > job.getCompleteTime())
        {
            end = job.getCompleteTime();
            emptyspace = true;
        }
        int length = end - start;
        int space = length - 1;
        for(int j = 0; j < space; j++)
        {
            std::cout << " ";
            cursor++;
        }
        std::cout << job.getId();
        cursor++;
        for(int j = 0; j < space; j++)
        {
            std::cout << " ";
            cursor++;
        }
        std::cout << "|";
        if(emptyspace) numLoc.push_back(std::make_pair(cursor, false));
        else numLoc.push_back(std::make_pair(cursor, true));
        cursor++;

        if(emptyspace)
        {
            int space = 2 * (lengthC - length - 1);
            for(int j = 0; j < space; j++)
            {
                std::cout << "/";
                cursor++;
            }
            std::cout << "|";
            numLoc.push_back(std::make_pair(cursor, true));
            cursor++;
        }
    }

    //print the bottom bar
    std::cout << "\n ";
    for(int i = 0; i < ganttChart[ganttChart.size() - 1].first->getCompleteTime(); i++)
    {
        std::cout << "--";
    }
    std::cout << "\b \n";

    //print timeline
    int idx = 0;
    int run = 0;
    int prev = -1;
    for(int i = 0; i < numLoc.size(); i++)
    {
        while(run != numLoc[i].first)
        {
            std::cout << " ";
            run++;
        }
        if(prev > 9) std::cout << "\b";
        if(!numLoc[i].second)
        {
            if(idx > 0) prev = ganttChart[idx - 1].first->getCompleteTime();
            if(idx > 0) std::cout << prev;
            run++;
            continue;
        }
        if(idx < ganttChart.size()) prev = ganttChart[idx].second;
        if(idx < ganttChart.size()) std::cout << prev;
        idx++;
        run++;
    }
    std::cout << ganttChart[ganttChart.size() - 1].first->getCompleteTime();
    std::cout << std::endl;
}