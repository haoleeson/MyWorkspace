#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

// 官解 O(NlogN)动态规划
// 链接：https://leetcode.cn/problems/contain-virus/solution/ge-chi-bing-du-by-leetcode-solution-vn9m/
class Solution {
private:
    // 上下左右四个扩散方向
    static constexpr int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    int containVirus(vector<vector<int>>& isInfected) {
        auto pair_hash = [fn = hash<int>()](const pair<int, int>& o) { return (fn(o.first) << 16) ^ fn(o.second); };

        int m = isInfected.size(), n = isInfected[0].size();
        int ans = 0;

        while (true) {
            vector<unordered_set<pair<int, int>, decltype(pair_hash)>> neighbors;
            vector<int> firewalls;

            // 遍历矩阵标记病毒坐标 (i,j)
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    // 广度优先搜索，找到一块连续感染区域
                    if (isInfected[i][j] == 1) {
                        queue<pair<int, int>> q;
                        unordered_set<pair<int, int>, decltype(pair_hash)> neighbor(0, pair_hash);
                        int firewall = 0, idx = neighbors.size() + 1;
                        q.emplace(i, j);
                        isInfected[i][j] = -idx;

                        while (!q.empty()) {
                            auto [x, y] = q.front();
                            q.pop();
                            // 向四个方向尝试查找感染区域
                            for (int d = 0; d < 4; ++d) {
                                int nx = x + dirs[d][0];
                                int ny = y + dirs[d][1];
                                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                                    if (isInfected[nx][ny] == 1) {
                                        q.emplace(nx, ny);
                                        isInfected[nx][ny] = -idx;
                                    } else if (isInfected[nx][ny] == 0) {
                                        ++firewall;
                                        neighbor.emplace(nx, ny);
                                    }
                                }
                            }
                        }
                        neighbors.push_back(move(neighbor));
                        firewalls.push_back(firewall);
                    }
                }
            }

            if (neighbors.empty()) {
                break;
            }

            int idx = max_element(neighbors.begin(), neighbors.end(),
                                  [](const auto& v0, const auto& v1) { return v0.size() < v1.size(); }) -
                      neighbors.begin();
            ans += firewalls[idx];
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] < 0) {
                        if (isInfected[i][j] != -idx - 1) {
                            isInfected[i][j] = 1;
                        } else {
                            isInfected[i][j] = 2;
                        }
                    }
                }
            }
            for (int i = 0; i < neighbors.size(); ++i) {
                if (i != idx) {
                    for (const auto& [x, y] : neighbors[i]) {
                        isInfected[x][y] = 1;
                    }
                }
            }
            if (neighbors.size() == 1) {
                break;
            }
        }
        return ans;
    }
};

int main(void) {
    Solution solution;
    int arr1[][8] = {
        {0, 1, 0, 0, 0, 0, 0, 1}, {0, 1, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0}};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    vector<vector<int>> isInfected1;
    for (int i = 0; i < len1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        isInfected1.push_back(tmp);
    }
    int res1 = solution.containVirus(isInfected1);
    cout << res1 << endl;

    int arr2[][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    vector<vector<int>> isInfected2;
    for (int i = 0; i < len2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        isInfected2.push_back(tmp);
    }
    int res2 = solution.containVirus(isInfected2);
    cout << res2 << endl;

    int arr3[][9] = {{1, 1, 1, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 0, 0, 0, 0, 0, 0}};
    int len3 = sizeof(arr3) / sizeof(arr3[0]);
    vector<vector<int>> isInfected3;
    for (int i = 0; i < len3; ++i) {
        vector<int> tmp(arr3[i], arr3[i] + sizeof(arr3[i]) / sizeof(int));
        isInfected3.push_back(tmp);
    }
    int res3 = solution.containVirus(isInfected3);
    cout << res3 << endl;

    return 0;
}
