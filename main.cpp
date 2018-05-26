
#include <iostream>
#include <fstream>
#include<sstream>
#include <cstdlib>//exit
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct reserv{
    int stime;
    int ftime;
    int profit;
};


void printOrders(vector<int> &p, int &maxIdx)//PRINT ORDERS OF MAX
{
    int x = maxIdx;
    cout<<"Orders: ";
    for(int i =0; i < p.size();++i)//print orders
    {
        cout<<x+1<<", ";
        x = p[x];
        if(p[x] == -1)
        {
            cout <<x+1<<".";
            return;
        }
    }
}
int printMax(vector<int> &v)//PRINT THE MAXIMUM PROFIT
{
    int maximum = 0, maxIdx = 0;
    for(int i = 0; i < v.size(); ++i)
    {
        if(maximum < v[i])
        {
            maximum = v[i];
            maxIdx = i;
        }
    }
    cout<<"Max Profit = "<<maximum<<" Index = "<<maxIdx<<endl;
    return maxIdx;
}

void printStructVec(vector<reserv> &v)//PRINT VECTOR OF RESERVATIONS
{
    
    for( vector<reserv>::iterator it =v.begin();it!= v.end();++it)
        cout<<"List: "<<"(" << (*it).stime<<"," <<(*it).ftime<<") "<<" profit = " <<(*it).profit<<endl;
    cout<<endl;
}
void printVec(vector <int> &v) //PRINT INT VECTOR
{
    for(vector <int>::iterator it = v.begin(); it!= v.end(); ++it)
        cout<< *it <<" ";
    cout<<" " <<endl;
}


bool sortbyFtime(const reserv &a, const reserv &b) {return a.ftime < b.ftime;}//SORT STRUCTS BY FINISH TIME

void maxProfit(const vector<reserv> &v)
{
    if(v.size()== 1)//one order (base case)
    {
        cout<<"Only one Reservation:"<<" MaxValue: "<<v[0].profit<< "Order: 1";
        return;
    }
    vector <reserv> sortedbyFtime;
    vector <int> profit;//create a profit vector
    vector <int> R;//vector of results
    sortedbyFtime = v;//make a copy, we dont want to change v
    
    int size = int(v.size());
    
    //fill vector with -1 of size v
    vector <int> path(size, -1);
    
    //sorting by the finish time
    sort(sortedbyFtime.begin(), sortedbyFtime.end(),sortbyFtime);
    
    //vector of profits with corresponding indexes to vector sortedbyFtime
    for(vector <reserv> :: iterator it = sortedbyFtime.begin(); it != sortedbyFtime.end();++it)
        profit.push_back((*it).profit);
    
    // R is a vector of results that first will contain all the profits
    R = profit;
    
    int flag = 0, overlapCounter = 0;
    //------------Algorithm Start-----------------------
    for (int i=1; i < size; i++)
        for (int j = 0; j < i; j++)
            if(sortedbyFtime[i].stime >= sortedbyFtime[j].ftime)//not overlap check, important: BIGGER or EQUAL
            {
                overlapCounter++;
                flag =R[i];
                R[i] = max(R[j] + profit[i], R[i]);
                //cout<<i<< " "<< R[i]<<" "<<endl;
                if(R[i] > flag)//if the profit increased
                    path[i] = j;//write the index that increased profit
            }
    
    int maxIdx;
    if(overlapCounter == 0)//all the time overlaps
    {
        printMax(profit);
        return;
    }
    else
        maxIdx = printMax(R);
    //------------Algorithm End-------------------------

    printOrders(path,maxIdx);
    
}

void readFromFile(vector<reserv> &v, string filePath)
{
    ifstream myfile(filePath);
    if(myfile)
    {
        string line;
        int size;
        int a, b, c;
        char d;
        
        getline(myfile, line);//first line-size line
        istringstream iss(line);
        
        if (!(iss >> size))
            cerr <<"reading first number has failed"<<endl;
        //cout<<size<<endl;
        
        for(int i = 0; i <size; i++)
        {
            getline(myfile, line);
            istringstream iss(line);
            if (!(iss >> a >> d >> b >> d >> c))
                cerr <<"reading lines failed"<<endl;
            //cout<<a<< ","<<b<<","<<c<<endl; //TEST PURPOSES
            v.push_back({a,b,c});
        }
    }
    else
    {
        cerr << "orders.txt could not be opened for reading!";
        exit(1);
    }
    printStructVec(v);
}



//---------------------------------------------
int main(int argc, const char * argv[]) {
    
    vector <reserv> v;
    string filePath = "orders.txt";
    readFromFile(v, filePath);
//    v.push_back({7,9,2});
//    v.push_back({5,8,11});
//    v.push_back({6,7,4});
//    v.push_back({4,6,5});
//    v.push_back({2,5,6});
//    v.push_back({1,3,5});
    
    maxProfit(v);

  
 
   
    return 0;
}
