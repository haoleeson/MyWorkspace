
/** utf-8
 * Leetcode
 * 977. 有序数组的平方
 * 给定一个按非递减顺序排序的整数数组 A，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。
 *
 *
 *
 * 示例 1：
 *
 * 输入：[-4,-1,0,3,10]
 * 输出：[0,1,9,16,100]
 * 示例 2：
 *
 * 输入：[-7,-3,2,3,11]
 * 输出：[4,9,9,49,121]
 *
 *
 * 提示：
 *
 * 1 <= A.length <= 10000
 * -10000 <= A[i] <= 10000
 * A 已按非递减顺序排序。
 *
 * coder:eisenhao
 * Java
 * 20190404
 * */


class Solution {
    public int[] sortedSquares(int[] A) {
        int len=A.length, NegativeNum=0;
        int[] result = new int[len];

        //找到小于0的部分
        while (NegativeNum<len && A[NegativeNum]<0) {
            NegativeNum++;
        }
        //将负数取绝对值(再平方)插入有序result数组
        int tmp, j=len-1, iterator=len-1;
        for (int i = 0; i < NegativeNum; i++) {
            tmp = ~A[i] + 1;//负数取正
            while (tmp <= A[j]) {
                result[iterator--] = A[j] * A[j];//大于abs(该负数)的正数（取平方）逆序填充
                j--;
            }
            result[iterator--] = tmp * tmp;
        }
        //原数组余下部分原样逆序填充
        while (j >= NegativeNum) {
            result[iterator--] = A[j] * A[j];
            j--;
        }
        return result;
    }
}

public class Main {
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] Input = {-7,-3,4,4,4,5,11};

        System.out.print("\nInput = \n [");
        for (int i = 0; i < Input.length-1; i++) {
            System.out.print(Input[i] + ", ");
        }
        System.out.println(Input[Input.length-1] + "]");


        int[] r = s.sortedSquares(Input);
        System.out.print("\nSquar = \n [");
        for (int i = 0; i < r.length-1; i++) {
            System.out.print(r[i] + ", ");
        }
        System.out.println(r[r.length-1] + "]");
    }
}
