#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

/**
 * No332. 重新安排行程 (回溯 or Hierholzer 算法)
 * 给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员分别表示飞机出发和降落的机场地点，对该行程进行重新规划排序。所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。

说明:
如果存在多种有效的行程，你可以按字符自然排序返回最小的行程组合。例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前
所有的机场都用三个大写字母表示（机场代码）。
假定所有机票至少存在一种合理的行程。

 示例 1:
输入: [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
输出: ["JFK", "MUC", "LHR", "SFO", "SJC"]

 示例 2:
输入: [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
输出: ["JFK","ATL","JFK","SFO","ATL","SFO"]
解释: 另一种有效的行程是["JFK","SFO","ATL","JFK","ATL","SFO"]。但是它自然排序更大更靠后。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reconstruct-itinerary
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 力扣官解：Hierholzer 算法
 * 思路及算法
 * Hierholzer 算法用于在连通图中寻找欧拉路径，其流程如下：
 * 1. 从起点出发，进行深度优先搜索。
 * 2. 每次沿着某条边从某个顶点移动到另外一个顶点的时候，都需要删除这条边。
 * 3. 如果没有可移动的路径，则将所在节点加入到栈中，并返回。
 * 当我们顺序地考虑该问题时，我们也许很难解决该问题，因为我们无法判断当前节点的哪一个分支是「死胡同」分支。
 *
 * 不妨倒过来思考。我们注意到只有那个入度与出度差为 1 的节点会导致死胡同。而该节点必然是最后一个遍历到的节点。
 * 我们可以改变入栈的规则，当我们遍历完一个节点所连的所有节点后，我们才将该节点入栈（即逆序入栈）。
 * 对于当前节点而言，从它的每一个非「死胡同」分支出发进行深度优先搜索，都将会搜回到当前节点。而从它的「死胡同」分支出发进行
 * 深度优先搜索将不会搜回到当前节点。也就是说当前节点的死胡同分支将会优先于其他非「死胡同」分支入栈。
 * 这样就能保证我们可以「一笔画」地走完所有边，最终的栈中逆序地保存了「一笔画」的结果。我们只要将栈中的内容反转，即可得到答案。
 *
 */
class Solution1 {
public:
    // 这里用map，内部自动按照string升序排列了，所以先找到的一定是自然排序最小的路径
    typedef unordered_map<string, map<string, int>> adjacent;// 记录从from到to的机票数
    vector<string> min_path;
    bool dfs(adjacent &adj, string airport){
        // 无脑dfs遍历邻居，同时遍历过的边标记已遍历
        for(auto &[next, number] : adj[airport]){
            // 若从airport到next的机票没有了，则遍历下一个
            if(0 >= number)
                continue;
            --number;// 从airport到next的机票数减一
            dfs(adj, next);
        }
        // 终点是没有相邻边的点
        // 当删除终点后，终点前的点也没有相邻边了，变成新的终点
        // 运行到这里，当前airport一定没有可遍历的相邻边了，则它是此时的终点
        min_path.push_back(airport);
        return true;
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // 初始化邻接表，因为存在多张相同机票的情况，所以邻接表中还记录了从from到to的机票数
        adjacent adj;
        for(auto & t : tickets){
            adj[t[0]][t[1]]++;
        }
        // Hierholzer算法，dfs无脑遍历
        dfs(adj, "JFK");

        // Hierholzer算法得到结果为终点到起点的路径，需要反转才是题目所要求的结果
        std::reverse(min_path.begin(), min_path.end());
        return min_path;
    }
};

/**
 * 力扣大佬：回溯
 */
class Solution2 {
private:
// unordered_map<出发城市, map<到达城市, 航班次数>> targets
    unordered_map<string, map<string, int>> targets;
    /**
     * 回溯
     * @param ticketNum
     * @param leftTickets
     * @param path 已走路径
     * @return
     */
    bool backtracking(int leftTickets, vector<string>& path) {
        if (leftTickets == 0) {
            return true;
        }

        // 遍历当前城市(已走路径的最后一个城市)，所有可能的目的城市
        for (pair<const string, int>& target : targets[path[path.size() - 1]]) {
            // 若还未走过
            if (target.second > 0) { // 使用int字段来记录到达城市是否使用过了
                path.push_back(target.first);
                target.second--;
                if (backtracking(leftTickets - 1, path)) return true;
                path.pop_back();
                target.second++;
            }
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> path;// 路径
        for (const vector<string>& vec : tickets) {
            // 记录映射关系，每个出发 --> 目的城市的 数量（出发城市可能重复，目的城市有可能多个）
            // targets[vec[0]] -- 指 unordered_map的出发城市，[vec[1]] -- 指目的城市
            targets[vec[0]][vec[1]]++;
        }
        path.push_back("JFK");
        backtracking(tickets.size(), path);
        return path;
    }
};

/**
 * 自己考虑用深度优先搜索，顺序地考虑很难解决死胡同问题
 */
class Solution0 {
    string START_AIRPORT = "JFK";
    vector<vector<string>> m_allAns;
    vector<string> m_tmpAns;
    bool* m_choseFlag;
    int m_size = 0;
public:

    void dfs(string& endPort, int leftTickets, vector<vector<string>>& tickets) {
        if (leftTickets == 0) {
            m_allAns.push_back(m_tmpAns);
            return;
        }

        // 遍历找到起点为上一个endport的点
        for (int i = 0; i < m_size; ++i) {
            // 未被选 且 与上一结束站点相同，则选择该点
            if (!m_choseFlag[i] && tickets[i][0] == endPort) {
                m_choseFlag[i] = true;
                m_tmpAns.push_back(tickets[i][1]);
                dfs(tickets[i][1], leftTickets - 1, tickets);
                m_choseFlag[i] = false;// 遍历过后清除已选
                m_tmpAns.pop_back();
            }
        }
        // 待处理 死胡同 问题，终止条件不好确定


    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        m_size = tickets.size();
        m_choseFlag = new bool[m_size]{false};
        m_tmpAns.push_back(START_AIRPORT);

        dfs(START_AIRPORT, m_size, tickets);

        delete []m_choseFlag;
        return m_tmpAns;
    }
};

template<typename T>
void printVec(vector<T>& vec) {
    int size = vec.size();
    if (size == 0) {
        cout << "[]" << endl;
        return;
    }
    cout << "[";
    for (int i = 0; i < vec.size() - 1; ++i) {
        cout << vec[i] << " ";
    }
    cout << vec[vec.size() - 1] << "]" << endl;
}

int main() {
    Solution2 solution;
    vector<vector<string>> tickets1;
    vector<string> tmp(2);
//    tmp[0] = "MUC"; tmp[1] = "LHR";
//    tickets1.push_back(tmp);
//    tmp[0] = "JFK"; tmp[1] = "MUC";
//    tickets1.push_back(tmp);
//    tmp[0] = "SFO"; tmp[1] = "SJC";
//    tickets1.push_back(tmp);
//    tmp[0] = "LHR"; tmp[1] = "SFO";
//    tickets1.push_back(tmp);
//    vector<string> result1 = solution.findItinerary(tickets1);
//    printVec(result1);

    vector<vector<string>> tickets2;
    tmp[0] = "JFK"; tmp[1] = "SFO";
    tickets2.push_back(tmp);
    tmp[0] = "JFK"; tmp[1] = "ATL";
    tickets2.push_back(tmp);
    tmp[0] = "SFO"; tmp[1] = "ATL";
    tickets2.push_back(tmp);
    tmp[0] = "ATL"; tmp[1] = "JFK";
    tickets2.push_back(tmp);
    tmp[0] = "ATL"; tmp[1] = "SFO";
    tickets2.push_back(tmp);
    vector<string> result2 = solution.findItinerary(tickets2);
    printVec(result2);

    return 0;
}
