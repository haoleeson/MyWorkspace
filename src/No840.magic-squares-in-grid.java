/** utf-8
 * Leetcode
 * 840. 矩阵中的幻方
 * 3 x 3 的幻方是一个填充有从 1 到 9 的不同数字的 3 x 3 矩阵，其中每行，每列以及两条对角线上的各数之和都相等。
 *
 * 给定一个由整数组成的 grid，其中有多少个 3 × 3 的 “幻方” 子矩阵？（每个子矩阵都是连续的）。
 *
 *
 *
 * 示例：
 *
 * 输入: [[4,3,8,4],
 *       [9,5,1,9],
 *       [2,7,6,2]]
 * 输出: 1
 * 解释:
 * 下面的子矩阵是一个 3 x 3 的幻方：
 * 438
 * 951
 * 276
 *
 * 而这一个不是：
 * 384
 * 519
 * 762
 *
 * 总的来说，在本示例所给定的矩阵中只有一个 3 x 3 的幻方子矩阵。
 * 提示:
 *
 * 1 <= grid.length <= 10
 * 1 <= grid[0].length <= 10
 * 0 <= grid[i][j] <= 15
 *
 * coder:eisenhao
 * Java
 * 20190402
 * */


class Solution {
    /**
     * 利用了3阶（且取值为：1～9）幻方矩阵的某些数学特性
     * 1):  每行、每列、对角线的和必为 15 （1+...+9）/ 3 = 15
     * 2):  中间数num必为5  (包含中间行的：第2行+第2列+两条斜线的和 == (1+...+9)+ 3*num = 15*4, 故num=5)
     * 3):  取值 1～9
     * 4):  不存在重复数
     * */
    public int numMagicSquaresInside(int[][] grid) {
        int row=grid.length, column=grid[0].length, answer=0;

        //判断对角为 [i-2][j-2] ~ [i][j] 的3阶矩阵是否为幻方
        for (int i = 2; i < row; i++) {
            for (int j = 2; j < column; j++) {
                //若中间数不为 5， 跳过
                if (grid[i-1][j-1] != 5)
                    continue;
                //若行、列、斜线和 存在一个不为15， 则跳过
                if ((grid[i-2][j-2]+grid[i-2][j-1]+grid[i-2][j] != 15)
                    || (grid[i-1][j-2]+grid[i-1][j] != 10)
                    || (grid[i][j-2]+grid[i][j-1]+grid[i][j] != 15)

                    || (grid[i-2][j-2]+grid[i-1][j-2]+grid[i][j-2] != 15)
                    || (grid[i-2][j-1]+grid[i][j-1] != 10)
                    || (grid[i-2][j]+grid[i-1][j]+grid[i][j] != 15)

                    || (grid[i-2][j-2]+grid[i][j] != 10)
                    || (grid[i-2][j]+grid[i][j-2] != 10)
                )
                    continue;
                //若存在小于1的数直接跳过（若有不再1～9范围的数，必存在超过9的数和小于1的数）
                if (grid[i-2][j-2]<1 || grid[i-2][j-1]<1 || grid[i-2][j]<1
                    || grid[i-1][j-2]<1 || grid[i-1][j]<1
                    || grid[i][j-2]<1 || grid[i][j-1]<1 || grid[i][j]<1)
                    continue;
                //若存在重复数跳过（此处只可能全为 5）
                if (grid[i-2][j-2] == 5)
                    continue;
                //余下情况，满足幻方
                answer++;
            }
        }
        return answer;
    }
}

public class Main {
    public static void main(String[] args) {
        Solution s = new Solution();
        int Input[][] = {{4,3,8,4},{9,5,1,9},{2,7,6,2}};

        s.printArray(Input);
        System.out.println("Output = " + s.numMagicSquaresInside(Input));
    }
}

