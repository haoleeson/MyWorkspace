/**
 * Leetcode
 * 766. 托普利茨矩阵
 * 如果一个矩阵的每一方向由左上到右下的对角线上具有相同元素，那么这个矩阵是托普利茨矩阵。
 *
 * 给定一个 M x N 的矩阵，当且仅当它是托普利茨矩阵时返回 True。
 *
 * 示例 1:
 * 输入:
 * matrix = [
 *   [1,2,3,4],
 *   [5,1,2,3],
 *   [9,5,1,2]
 * ]
 * 输出: True
 * 解释:
 * 在上述矩阵中, 其对角线为:
 * "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]"。
 * 各条对角线上的所有元素均相同, 因此答案是True。
 *
 * 示例 2:
 * 输入:
 * matrix = [
 *   [1,2],
 *   [2,2]
 * ]
 * 输出: False
 * 解释:
 * 对角线"[1, 2]"上的元素不同。
 *
 * 说明:
 *  matrix 是一个包含整数的二维数组。
 * matrix 的行数和列数均在 [1, 20]范围内。
 * matrix[i][j] 包含的整数在 [0, 99]范围内。
 *
 * 进阶:
 * 如果矩阵存储在磁盘上，并且磁盘内存是有限的，因此一次最多只能将一行矩阵加载到内存中，该怎么办？
 * 如果矩阵太大以至于只能一次将部分行加载到内存中，该怎么办？
 *
 * coder:eisenhao
 * Java
 * 20190402
 * */


class Solution {
    /**方法1： 斜向比较*/
    public boolean isToeplitzMatrix(int[][] matrix) {
        int row=matrix.length, column = matrix[0].length;

        if (matrix.length == 0) return false;
        //按列比较
        for (int k=0; k < column-1; k++) {
            for (int i=1, j=k+1; i<row && j<column; i++, j++) {
                if (matrix[0][k] != matrix[i][j])
                    return false;
            }
        }
        //按行比较
        for (int k=1; k < row-1; k++) {
            for (int i=k+1, j=1; i<row && j<column; i++, j++) {
                if (matrix[k][0] != matrix[i][j])
                    return false;
            }
        }
        return true;
    }

    /**方法2： 下一行错位与上一行比较*/
    public boolean isToeplitzMatrix2(int[][] matrix) {
        int row=matrix.length, column = matrix[0].length;
        if (matrix.length == 0) return false;

        for (int k = 1; k < row; k++) {
            for (int i = 1; i < column; i++) {
                if (matrix[k-1][i-1] != matrix[k][i])
                    return false;
            }
        }
        return true;
    }
}

public class Main {
    public static void main(String[] args) {
        Solution s = new Solution();
        int matrix[][] = {{1,2,3,4}, {5,1,2,3}, {9,5,1,2}};
        System.out.println("Input = [");
        for (int i = 0; i < matrix.length; i++) {
            System.out.print("[");
            for (int j = 0; j < matrix[0].length-1; j++) {
                System.out.print("" + matrix[i][j] + ", ");
            }
            System.out.println("" + matrix[i][matrix[0].length-1] + "]");
        }
        System.out.println("]");

        System.out.println("Output = " + s.isToeplitzMatrix(matrix));
    }
}

