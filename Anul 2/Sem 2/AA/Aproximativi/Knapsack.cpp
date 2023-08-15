#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

// subpunctul a
int max_sum(int k, const vector<int>& numberList)
{
    int sum = 0;
    unordered_set<int> values; // ne asiguram ca luam fiecare element o singura data, le punem random in set
    values.insert(0); // fiecare operatie pe unordered_set are complexitate O(1)
    for(auto num: numberList) // O(n)
        for(auto val: values) // O(n)
            if(val + num <= k) // O(1)
            {
                sum = max(sum, val + num); // determin suma maxima
                values.insert(val + num); // inserez in set suma curenta (daca nu exista deja in set)
            }
    return sum;
}

// subpunctul b
int max_sum(ifstream &in)
{
    int k, aux, sum = 0;
    in>>k;
    while(in>>aux)
        if(aux + sum <= k)  sum += aux;
        else if(sum < aux)  sum = aux; 
    return sum;
}

int main()
{
    ifstream fin("C:\\Users\\bales\\OneDrive\\Facultate\\Anul 2\\Sem 2\\AA\\Aproximativi\\data.in");
    // subpunctul b
    cout<<max_sum(fin);
    // subpunctul a
//    int k, aux;
//    vector<int> S;
//    fin>>k;
//    while(fin>>aux)
//        S.emplace_back(aux);
//    cout<<max_sum(k, S);
    return 0;
}