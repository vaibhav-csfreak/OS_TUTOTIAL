// C++ program to implement Shortest Job first with Arrival Time
#include <bits/stdc++.h>
using namespace std;
int SJF_array[10][6];
//Function to sort in ascending order of arrival time
void arrangeArrival(int num, int SJF_array[][6])
{
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < num - i - 1; j++)
        {
            if (SJF_array[j][1] > SJF_array[j + 1][1])
            {
                for (int k = 0; k < 3; k++)
                {
                    swap(SJF_array[j][k], SJF_array[j + 1][k]);
                }
            }
        }
    }
}
//Function to calculate Completion Time, Turn Around Time and Burst Time
//4th column is Completion Time
//5th column is Turn Around Time
//6th column is Waiting Time
void completionTime(int num, int SJF_array[][6])
{
    int temp, val;
    SJF_array[0][3] = SJF_array[0][1] + SJF_array[0][2]; //Completion Time of a process
    SJF_array[0][5] = SJF_array[0][3] - SJF_array[0][1]; //Turn Around Time of a process
    SJF_array[0][4] = SJF_array[0][5] - SJF_array[0][2]; //Waiting Time of a process

    for (int i = 1; i < num; i++)
    {
        temp = SJF_array[i - 1][3]; //Completion Time of previous process
        int low = SJF_array[i][2];  //Burst Time of current process
        /*******************************************************************
        Check if any of the next process has arrived before completetion of 
        any current process and has lower burst time than current process
        *******************************************************************/
        for (int j = i; j < num; j++)
        {
            if (temp >= SJF_array[j][1] && low >= SJF_array[j][2])
            {
                low = SJF_array[j][2];
                val = j;
            }
        }
        //update the process details with next lowest burst time
        SJF_array[val][3] = temp + SJF_array[val][2];
        SJF_array[val][5] = SJF_array[val][3] - SJF_array[val][1];
        SJF_array[val][4] = SJF_array[val][5] - SJF_array[val][2];
        for (int k = 0; k < 6; k++)
            swap(SJF_array[val][k], SJF_array[i][k]); //Swapping based on execution of process
    }
}

int main()
{
    int num, temp, total_TAT = 0, total_WT = 0;

    cout << "Enter number of Process: "; //Input of number of processes
    cin >> num;

    cout << "...Enter the process ID...\n"; //Input of process ID
    for (int i = 0; i < num; i++)
    {
        cout << "...Process " << i + 1 << "...\n";
        cout << "Enter Process Id: ";
        cin >> SJF_array[i][0];
        cout << "Enter Arrival Time: ";
        cin >> SJF_array[i][1];
        cout << "Enter Burst Time: ";
        cin >> SJF_array[i][2];
    }
    cout << "Before Arrange...\n";
    //Display Processes with Arrival Time and Burst Time before arrangement
    cout << "Process ID\tArrival Time\tBurst Time\n";
    for (int i = 0; i < num; i++)
    {
        cout << SJF_array[i][0] << "\t\t" << SJF_array[i][1] << "\t\t"
             << SJF_array[i][2] << "\n";
    }
    //Sorting Processes based on ascending order of arrival time
    arrangeArrival(num, SJF_array);
    //Calculate the Completetion Time, Turn Around Time and Waiting Time
    completionTime(num, SJF_array);
    cout << "Final Result...\n";
    cout << "Process ID\tArrival Time\tBurst Time\tWaiting "
            "Time\tTurnaround Time\n";
    //Display the table after all the calculations
    for (int i = 0; i < num; i++)
    {
        cout << SJF_array[i][0] << "\t\t" << SJF_array[i][1] << "\t\t"
             << SJF_array[i][2] << "\t\t" << SJF_array[i][4] << "\t\t"
             << SJF_array[i][5] << "\n";
    }
    for (int i = 0; i < num; i++)
    {
        total_TAT += SJF_array[i][4];
        total_WT += SJF_array[i][5];
    }
    //Display Average Turn Around Time
    cout << "Average Turn Around Time = " << total_TAT / (float)num << " ms" << endl;
    //Display Average Waiting Time
    cout << "Average Waiting Time = " << total_WT / (float)num << " ms" << endl;
    return 0;
}
