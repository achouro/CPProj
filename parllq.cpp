#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#include <iterator>
#include <functional>
#include <utility>

using namespace std;

class comparator{
  public:
    int operator()(const pair<int, long long> left, const pair<int,long long> right){
      if(left.second==right.second)
        return(left.first>right.first);
      else
        return(left.second>right.second);} };


class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }
  
  void assign_jobs(){
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());  

   priority_queue< pair<int,long long>, vector<pair<int,long long> >, comparator> job_finish_time;
   //jobs sorted by lenght time in ascending order priority to shortest
   for(int i=0;i<jobs_.size();++i){
     int duration=jobs_[i];
     int next_worker=0;
     
     pair<int,long long> next_free_time;

     if(job_finish_time.size()<num_workers_)
       next_free_time=make_pair(i,0);
     else{
       next_free_time=job_finish_time.top(); //collect floating maximum then remove it from pq
       job_finish_time.pop();}

     next_worker= next_free_time.first;

     assigned_workers_[i]=next_worker;
     start_times_[i]=next_free_time.second;
 
    job_finish_time.push(make_pair(next_worker,(next_free_time.second +duration)));}
}


/*
  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }
*/
 public:
  void Solve() {
    ReadData();
    assign_jobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}

