#include <iostream>
#include <vector>
using namespace std;
/**
 * No733. 图像渲染
 * 有一幅以二维整数数组表示的图画，每一个整数表示该图画的像素值大小，数值在 0 到 65535 之间。

给你一个坐标(sr, sc)表示图像渲染开始的像素值（行 ，列）和一个新的颜色值newColor，让你重新上色这幅图像。

为了完成上色工作，从初始坐标开始，记录初始坐标的上下左右四个方向上像素值与初始坐标相同的相连像素点，接着再记录这四个方向上符合条件的像素点与他们对应四个方向上像素值与初始坐标相同的相连像素点，……，重复该过程。将所有有记录的像素点的颜色值改为新的颜色值。

最后返回经过上色渲染后的图像。

示例 1:

输入: 
image = [
            [1,1,1],
            [1,1,0],
            [1,0,1]
        ]
sr = 1, sc = 1, newColor = 2

输出:   [
            [2,2,2],
            [2,2,0],
            [2,0,1]
        ]
解析: 
在图像的正中间，(坐标(sr,sc)=(1,1)),
在路径上所有符合条件的像素点的颜色都被更改成2。
注意，右下角的像素没有更改为2，
因为它不是在上下左右四个方向上与初始点相连的像素点。
注意:

image 和 image[0]的长度在范围[1, 50] 内。
给出的初始点将满足0 <= sr < image.length 和0 <= sc < image[0].length。
image[i][j] 和newColor表示的颜色值在范围[0, 65535]内。

*/

/**
 * 解题思路：广度优先搜索
 */
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        originColor = image[sr][sc];
        maxRow = image.size() - 1;
        maxColumn = image[0].size() - 1;
        if (originColor == newColor) {
            return image;
        }

        dfs(image, sr, sc, newColor);
        return image;
    }

private:
    int originColor = 0, maxRow = 0, maxColumn = 0;
//    bool visitedFlag[10000] = {false};

    void dfs(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if (sr < 0 || sc < 0 || sr > maxRow || sc > maxColumn  ||
            image[sr][sc] != originColor) {
            return;
        }
//        visitedFlag[sr * 100 + sc] = true;
        image[sr][sc] = newColor;
        dfs(image, sr - 1, sc, newColor);
        dfs(image, sr + 1, sc, newColor);
        dfs(image, sr, sc - 1, newColor);
        dfs(image, sr, sc + 1, newColor);
    }
};

void print2dVec(vector<vector<int>>image) {
    for (int i = 0; i < image.size(); ++i) {
       cout << "[";
        for (int j = 0; j < image[i].size() - 1; ++j) {
            cout << "\t" << image[i][j] << ", ";
        }
        cout << "\t" << image[i][image[i].size() - 1] << "]" << endl;
    }
}

int main() {
    Solution solution;
    int array[3][3] = { {1,1,1},
                        {1,1,0},
                        {1,0,1}};
    vector<vector<int>>image;
    for (int i = 0; i < 3; ++i) {
        vector<int>tmp(array[i], array[i] + 3);
        image.push_back(tmp);
    }

    solution.floodFill(image, 1, 1, 2);

    print2dVec(image);

    return 0;
}
