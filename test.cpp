#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
using namespace std;

const int RANGE = 10e6;
const int DIM = 100;
// Make the dataset
void formData(vector<vector<int>> &v, vector<int> &q)
{
    // random_device rand_dev;
    // mt19937 gen(rand_dev());
    auto const seed = 51;
    mt19937 gen {seed};
    uniform_int_distribution<> dis(-100,100);

    for(auto i = v.begin(); i!= v.end(); i++)
    {
        for(auto j = i->begin(); j!=i->end(); j++)
        {
            *j = dis(gen);
        }
    }


    for(int i=0; i<q.size(); i++)
        q[i] = dis(gen);
    
}

int calculateD(int a, int b)
{
    return a << 1 + b << 1;
}

int findDistance(vector<int> &a, vector<int> &b)
{
    int d = 0;
    for(int i=0; i<a.size(); i++)
        d += calculateD(a[i],b[i]);

    return d;
}
int main()
{
    vector<vector<int>> v(RANGE, vector<int>(DIM));
    vector<int> q(DIM);
    formData(v,q);

    // Start measuring time
    clock_t start = clock();
    priority_queue<pair<int,int>> pq;
    int k = 0;
    while(k < 10)
    {
        int distance = findDistance(v[k], q);
        pq.push({distance,k});
        k++;
    }

    pair<int,int> p;
    while(k < RANGE)
    {
        p = pq.top();
        int d1 = p.first;
        int d2= findDistance(v[k], q);
        if(d2 < d1)
        {
            pq.push({d2,k});
            pq.pop();
        }
        k++;
    }

    // Stop time
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    
    printf("\nTime measured: %.3f seconds.\n", elapsed);

    cout << " \n Answers \n";
    while(!pq.empty())
    {
        p = pq.top();
        cout << p.second << " ";
        pq.pop();
    }
    return 0;
}