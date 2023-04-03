class Job
{
private:
  int arrivalTime = 0;
  int burstTime = 0;
  int leftTime = 0;
  int priority;
  int waitingTime = 0;
  int turnAroundTime;
  int completeTime = 0;
  int startTime = -1;
  bool isCompleted = false;
  bool isRunning = false;
  bool isArrived = false;
  char id;
public:
  Job(int arrivalTime, int burstTime, int priority, char id) : arrivalTime(arrivalTime), burstTime(burstTime), priority(priority), leftTime(burstTime), id(id) {}
  int getArrivalTime() const { return arrivalTime; }
  int getBurstTime() const { return burstTime; }
  int getPriority() const { return priority; }
  int getWaitingTime() const { return waitingTime; }
  int getTurnAroundTime() const { return turnAroundTime; }
  int getLeftTime() const { return leftTime; }
  int getCompleteTime() const { return completeTime; }
  int getStartTime() const { return startTime; }
  char getId() const { return id; }
  bool isJobCompleted() const { return isCompleted; }
  bool isJobRunning() const { return isRunning; }
  bool isJobArrived() const { return isArrived; }
  void runJob() { isRunning = true; isArrived = true; }
  void pauseJob() { isRunning = false; }
  void reset()
  {
    isCompleted = false;
    isRunning = false;
    isArrived = false;
    leftTime = burstTime;
    waitingTime = 0;
    turnAroundTime = 0;
  }
  void step(int t)
  {
    if (isJobCompleted())
    {
      isRunning = false;
      return;
    }
    if (isJobRunning())
    {
      leftTime--;
      if(startTime < 0) startTime = t - 1;
      if (leftTime == 0)
      {
        isCompleted = true;
        completeTime = t;
        turnAroundTime = t - arrivalTime;
      }
    }
    else
    {
      if (isJobArrived())
      {
        waitingTime++;
      }
      else
      {
        if (arrivalTime == t)
        {
          isArrived = true;
        }
      }
    }
  }
};