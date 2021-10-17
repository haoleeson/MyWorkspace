/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#include <iostream>
#include <vector>
using namespace std;
//用贪心求工作时序安排
void schedulGreedy(int jobs[], int num){
    vector<int> jobSchedule(num, 0);
    for(int i=0; i<num; i++){
        jobSchedule[i] = i+1;
    }
    for(int i=0; i<num-1; i++){
        for(int j=i; j<num; j++){
            if(jobs[i] > jobs[j]){
                int temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
                temp = jobSchedule[i];
                jobSchedule[i] = jobSchedule[j];
                jobSchedule[j] = temp;
            }
        }
    }
    cout << "job schedule is:" << endl;
    for(int i=0; i<num; i++){
        cout << "j" << jobSchedule[i];
        if(i!=num-1){
            cout << " -> ";
        }
    }
}
int main(void) {
    int jobs[4] = {15, 8, 3, 10};
    schedulGreedy(jobs, 4);
    return 0;
}
