#include <bits/stdc++.h>
using namespace std;
/********************************************************
function to find the frame to be replaced with the new 
frame, it will return the position of the frame that has 
the minimum value in the time vector (minimum value 
represents the frame that entered long ago)
********************************************************/
int findLRU(vector<int> time, int no_of_frames)
{
    int minimum = time[0], position = 0;
    for (int i = 1; i < no_of_frames; i++)
    {
        if (time[i] < minimum)
        {
            minimum = time[i];
            position = i;
        }
    }
    return position;
}

int main()
{
    int no_of_frames, no_of_pages, count = 0, flag1, flag2, position, page_faults = 0;
    vector<int> frames(no_of_frames, -1), pages(no_of_pages), time(no_of_frames);
    cout << "Enter number of frames: "; //Input for number of frames
    cin >> no_of_frames;
    cout << "\nEnter number of pages: "; //Input for number of pages
    cin >> no_of_pages;
    cout << "\nEnter reference string: "; //Input for reference string
    for (int i = 0; i < no_of_pages; i++)
        cin >> pages[i];
    for (int i = 0; i < no_of_pages; i++)
    { //for every page in the reference string
        flag1 = flag2 = 0;
        for (int j = 0; j < no_of_frames; j++)
        { //if the current page is already present in the frame vector
            if (frames[j] == pages[i])
            {
                count++; //increment the count
                time[j] = count;
                flag1 = flag2 = 1;
                break;
            }
        }
        if (flag1 == 0)
        {
            for (int j = 0; j < no_of_frames; j++)
            { //if any frame is empty
                if (frames[j] == -1)
                {
                    count++;              //increment the count
                    page_faults++;        //increment the number of page faults
                    frames[j] = pages[i]; //insert the current page into the frame
                    time[j] = count;      //insert the count into time vector
                    flag2 = 1;
                    break;
                }
            }
        }
        if (flag2 == 0)
        {                                           //if the current page is not present in the frame vector
            position = findLRU(time, no_of_frames); //find the frame to be replaced with the new frame
            count++;                                //increment the count
            page_faults++;                          //increment the number of page counts
            frames[position] = pages[i];            //insert the current page into the frame
            time[position] = count;                 //insert the count into time vector
        }
        cout << endl;
        for (int j = 0; j < no_of_frames; j++)
        { //print the frame vector
            cout << frames[j] << " ";
        }
    }
    cout << "\n\nPage faults = " << page_faults << endl;
    cout << "Hits = " << no_of_pages - page_faults << endl;
    cout << "Hit ratio = " << (no_of_pages - page_faults) * 100 / no_of_pages << "%" << endl;
    return 0;
}