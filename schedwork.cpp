#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;



bool sched_helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& worker_shift_cnt, size_t loc);
bool find_if_worker_already_scheduled(const DailySchedule& sched, int day, int w, int curr_slot);

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched)
{
  if(avail.size() == 0U){
      return false;
  }
  sched.clear();
  size_t num_days = avail.size();
  sched.resize(num_days);
  for(int i = 0; i < avail.size(); i++){
    sched[i].resize(dailyNeed);
  }

  size_t num_workers = avail[0].size();
  vector<size_t> worker_shift_cnt(num_workers, 0);
  
  return sched_helper(avail, dailyNeed, maxShifts, sched, worker_shift_cnt, 0);
}

bool sched_helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& worker_shift_cnt, size_t loc){
  int num_days = avail.size();
  int num_workers = avail[0].size();
  size_t total_loc = num_days * dailyNeed;

  if(loc == total_loc){
    return true;
  }

  int day = loc/dailyNeed;
  int slt = loc%dailyNeed;
  for(int w = 0; w < num_workers; w++){
    if(worker_shift_cnt[w] >= maxShifts){
      continue;
    }
    else if(avail[day][w] == false){
      continue;
    }
    else if(find_if_worker_already_scheduled(sched, day, w, slt)){
      continue;
    }
    sched[day][slt] = w;
    worker_shift_cnt[w]++;

    if(sched_helper(avail, dailyNeed, maxShifts, sched, worker_shift_cnt, loc+1)){
      return true;
    }
    worker_shift_cnt[w]--;
  }
  return false;
}

bool find_if_worker_already_scheduled(const DailySchedule& sched, int day, int w, int curr_slot){
  for(int i = 0; i < curr_slot; i++){
    if(sched[day][i] == w){
      return true;
    }
  }
  return false;
}



