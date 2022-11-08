/*
Program: 24 Game Solver
Description: Solves the 24 Game, where the player is given 4 numbers and must return a sequence of arithmetic functions 
            with all 4 of the numbers to get the result of 24.
Made By: Steven Han
*/
#include <bits/stdc++.h>
using namespace std;

string duplicateRemover(string& orig)
{
    int ptr = 0;
    unordered_set<string> strings;
    for(int i = 0; i < orig.size(); i++)
    {
        if(orig[i] == '\n')
        {
            strings.insert(orig.substr(ptr, i - ptr));
            ptr = i + 1;
        }
    }
    string ans = "";
    for(const string& str : strings)
    {
        ans += str + '\n';
    }
    return ans;
}

string solver(vector<pair<double,string>>& nums) 
{
    if(nums[0].first == 24 && nums.size() == 1)
    {
        return (nums[0].second + "\n");
    }
    else if(nums.size() == 1)
    {
        return "";
    }
    else
    {
        string combinations = "";
        for(int i = 0; i < nums.size() - 1; i++)
        {
            for(int j = i + 1; j < nums.size(); j++)
            {
            
            vector<pair<double,string>> newNums = nums;
            // +
            newNums[i].first = newNums[i].first + newNums[j].first;
            newNums[i].second = "(" + newNums[i].second + "+" +  newNums[j].second + ")";
            newNums.erase(newNums.begin()+j);
            combinations += solver(newNums);

            // - (l - r)
            newNums = nums;
            newNums[i].first = newNums[i].first - newNums[j].first;
            newNums[i].second = "(" + newNums[i].second + "-" + newNums[j].second + ")";
            newNums.erase(newNums.begin()+j);
            combinations += solver(newNums);

            // *
            newNums = nums;
            newNums[i].first = newNums[i].first * newNums[j].first;
            newNums[i].second = "(" + newNums[i].second + "*" + newNums[j].second + ")";
            newNums.erase(newNums.begin()+j);
            combinations += solver(newNums);

            // / (l / r)
            newNums = nums;
            newNums[i].first = newNums[i].first / newNums[j].first;
            newNums[i].second = "(" + newNums[i].second + "/" + newNums[j].second + ")";
            newNums.erase(newNums.begin()+j);
            combinations += solver(newNums);

            // - (r - l)
            newNums = nums;
            newNums[i].first = newNums[j].first - newNums[i].first;
            newNums[i].second = "(" + newNums[j].second + "-" + newNums[i].second + ")";
            newNums.erase(newNums.begin()+j);
            combinations += solver(newNums);

            // / (r / l)
            newNums = nums;
            newNums[i].first = newNums[j].first + newNums[i].first;
            newNums[i].second = "(" + newNums[j].second + "/" + newNums[i].second + ")";
            newNums.erase(newNums.begin()+j);
            combinations += solver(newNums);
            }
        }
        return combinations;
    }
}


int main() 
{
    cout << "Please enter your numbers: ";
    double input[4];
    for (int i = 0; i < 4; i++) 
    {
        // Reading User Input value Based on index
        cin >> input[i];
    }
    vector<pair<double,string>> toSolve;
    for(double num : input)
    {
        toSolve.push_back(make_pair(num, to_string(int(num))));
    }
    string solved = solver(toSolve);
    cout << (solved == "" ? "There is not a solution" : "There is at least one solution")<< endl;
    if(solved != "")
    {
        cout << "Reveal solution(s)? (y/n): ";
        string resp;
        cin >> resp;
        if(resp == "y")
        {
            cout << duplicateRemover(solved) << endl;
        }
    }
}