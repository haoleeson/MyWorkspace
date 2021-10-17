/**
 * No834. 树中距离之和
 * 给定一个无向、连通的树。树中有 N 个标记为 0...N-1 的节点以及 N-1 条边 。
 * 第 i 条边连接节点 edges[i][0] 和 edges[i][1] 。
 * 返回一个表示节点 i 与其他所有节点距离之和的列表 ans。

示例 1:
输入: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
输出: [8,12,6,10,10,10]
解释: 
如下为给定的树的示意图：
  0
 / \
1   2
   /|\
  3 4 5

我们可以计算出 dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5) 
也就是 1 + 1 + 2 + 2 + 2 = 8。 因此，answer[0] = 8，以此类推。
说明: 1 <= N <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sum-of-distances-in-tree
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

class Solution {
public:
    vector<int> ans, sz, dp;
    vector<vector<int>> graph;

    /**
     * 计算以 u 为根节点，其他所有节点到 u 根节点的距离和 dp[u]
     * @param u
     * @param f
     */
    void dfs(int u, int f) {
        sz[u] = 1;
        dp[u] = 0;
        for (auto& v: graph[u]) {
            if (v == f) {
                continue;
            }
            dfs(v, u);
            dp[u] += dp[v] + sz[v];
            sz[u] += sz[v];
        }
    }

    /**
     * 换根计算其他节点作为根节点，计算距离和
     * @param u
     * @param f
     */
    void dfs2(int u, int f) {
        ans[u] = dp[u];
        for (auto& v: graph[u]) {
            if (v == f) {
                continue;
            }
            int pu = dp[u], pv = dp[v];
            int su = sz[u], sv = sz[v];

            dp[u] -= dp[v] + sz[v];
            sz[u] -= sz[v];
            dp[v] += dp[u] + sz[u];
            sz[v] += sz[u];

            dfs2(v, u);

            dp[u] = pu, dp[v] = pv;
            sz[u] = su, sz[v] = sv;
        }
    }

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        ans.resize(N, 0);
        sz.resize(N, 0);
        dp.resize(N, 0);
        // 构造图graph[u]{v1, v2, ... ,vn}
        graph.resize(N, {});
        for (auto& edge: edges) {
            int u = edge[0], v = edge[1];
            graph[u].emplace_back(v);
            graph[v].emplace_back(u);
        }
        dfs(0, -1);
        dfs2(0, -1);
        return ans;
    }
};

int main() {
    Solution solution;
    int N = 6;
    vector<vector<int>> edges;
    vector<int> edge(2, 0);
    edge[0] = 0;
    edge[1] = 1;
    edges.push_back(edge);
    edge[0] = 0;
    edge[1] = 2;
    edges.push_back(edge);
    edge[0] = 2;
    edge[1] = 3;
    edges.push_back(edge);
    edge[0] = 2;
    edge[1] = 4;
    edges.push_back(edge);
    edge[0] = 2;
    edge[1] = 5;
    edges.push_back(edge);

    vector<int> result = solution.sumOfDistancesInTree(N, edges);
    MyTools::printVec(result);
    return 0;
}
