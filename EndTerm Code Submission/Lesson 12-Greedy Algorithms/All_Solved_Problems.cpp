#include <vector>
#include <algorithm>
using namespace std;


/*Problem 1: Schedule the maximum number of meetings in one room without overlaps*/
int maxMeetings(vector<int>& start, vector<int>& end) {
    vector<pair<int, int>> meetings;
    for (int i = 0; i < start.size(); i++) {
        meetings.push_back({end[i], start[i]});
    }
    sort(meetings.begin(), meetings.end());

    int count = 1;
    int lastEnd = meetings[0].first;
    for (int i = 1; i < meetings.size(); i++) {
        if (meetings[i].second > lastEnd) {
            count++;
            lastEnd = meetings[i].first;
        }
    }
    return count;
}



/*Problem 2: Determine if you can reach the last index of an array where each element represents the maximum jump length*/
bool canJump(vector<int>& nums) {
    int reachable = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (i > reachable) return false;
        reachable = max(reachable, i + nums[i]);
    }
    return true;
}



/*Problem 3: Maximize value in a knapsack by taking fractions of items*/
double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
    vector<pair<double, int>> ratios;
    for (int i = 0; i < val.size(); i++) {
        ratios.push_back({(double)val[i] / wt[i], i});
    }
    sort(ratios.rbegin(), ratios.rend());

    double totalValue = 0.0;
    for (auto& ratio : ratios) {
        int idx = ratio.second;
        if (wt[idx] <= capacity) {
            totalValue += val[idx];
            capacity -= wt[idx];
        } else {
            totalValue += capacity * ratio.first;
            break;
        }
    }
    return totalValue;
}



/*Problem 4: Check if you can provide correct change when customers pay with $5, $10, or $20 bills*/
bool lemonadeChange(vector<int>& bills) {
    int five = 0, ten = 0;
    for (int bill : bills) {
        if (bill == 5) five++;
        else if (bill == 10) {
            if (five == 0) return false;
            five--;
            ten++;
        } else {
            if (ten > 0 && five > 0) {
                ten--;
                five--;
            } else if (five >= 3) {
                five -= 3;
            } else return false;
        }
    }
    return true;
}



/*Problem 5: Schedule jobs to maximize profit before deadlines*/
vector<int> JobScheduling(vector<vector<int>>& jobs) {
    sort(jobs.begin(), jobs.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] > b[2];
    });

    int maxDeadline = 0;
    for (auto& job : jobs) {
        maxDeadline = max(maxDeadline, job[1]);
    }
    vector<int> schedule(maxDeadline + 1, -1);

    int count = 0, totalProfit = 0;
    for (auto& job : jobs) {
        int deadline = job[1];
        while (deadline > 0 && schedule[deadline] != -1) {
            deadline--;
        }
        if (deadline > 0) {
            schedule[deadline] = job[0];
            count++;
            totalProfit += job[2];
        }
    }
    return {count, totalProfit};
}