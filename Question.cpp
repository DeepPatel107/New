#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
using namespace std;

// #region agent log
static void dbgLog(const char* location, const char* message, const char* hypothesisId, int i, int n, int target) {
    ofstream f("debug-02d04b.log", ios::app);
    if (!f) return;
    auto ts = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
    f << "{\"sessionId\":\"02d04b\",\"runId\":\"post-fix\",\"hypothesisId\":\"" << hypothesisId
      << "\",\"location\":\"" << location << "\",\"message\":\"" << message
      << "\",\"data\":{\"i\":" << i << ",\"n\":" << n << ",\"target\":" << target
      << "},\"timestamp\":" << ts << "}\n";
}
// #endregion

class Solution {
public:
    void solve(vector<int>& candidates, int target,
               vector<vector<int>>& ans,
               vector<int>& temp,
               int start) {
        if (target == 0) {
            // #region agent log
            dbgLog("Question.cpp:solve:hit", "target reached zero", "H2", start, (int)candidates.size(), target);
            // #endregion
            ans.push_back(temp);
            return;
        }

        for (int i = start; i < (int)candidates.size(); i++) {
            if (i > start && candidates[i] == candidates[i - 1]) continue;
            if (candidates[i] > target) break;

            temp.push_back(candidates[i]);
            solve(candidates, target - candidates[i], ans, temp, i);
            temp.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> temp;
        solve(candidates, target, ans, temp, 0);
        return ans;
    }
};

int main() {
    Solution obj;

    auto runCase = [&](vector<int> candidates, int target, const char* label) {
        vector<vector<int>> result = obj.combinationSum(candidates, target);
        cout << "=== " << label << " ===" << endl;
        cout << "count=" << result.size() << endl;
        for (const auto& combination : result) {
            for (int num : combination) cout << num << " ";
            cout << endl;
        }
    };

    runCase({2, 3, 6, 7}, 7, "distinct target=7");
    runCase({2, 2, 3}, 7, "duplicates target=7");
    runCase({2}, 1, "edge: target smaller than min");

    return 0;
}
