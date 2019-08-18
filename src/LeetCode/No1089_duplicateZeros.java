package LeetCode;

/**
 * Leetcode
 * 1089. 复写零
 * 给你一个长度固定的整数数组 arr，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。
 *
 * 注意：请不要在超过该数组长度的位置写入元素。
 *
 * 要求：请对输入的数组 就地 进行上述修改，不要从函数返回任何东西。
 *
 *  
 *
 * 示例 1：
 *
 * 输入：[1,0,2,3,0,4,5,0]
 * 输出：null
 * 解释：调用函数后，输入的数组将被修改为：[1,0,0,2,3,0,0,4]
 * 示例 2：
 *
 * 输入：[1,2,3]
 * 输出：null
 * 解释：调用函数后，输入的数组将被修改为：[1,2,3]
 *  
 *
 * 提示：
 *
 * 1 <= arr.length <= 10000
 * 0 <= arr[i] <= 9
 *
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/duplicate-zeros
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 * coder:eisenhao
 * Java
 * 20190818
 * */

public class No1089_duplicateZeros {
    static class Solution {
        public void duplicateZeros(int[] arr) {
            int length = 0;
            int zeroCount = 0;
            int iterator = -1;

            if (null == arr || (length = arr.length) < 2) {
                return;
            }
            //count zero
            do {
                ++iterator;
                if (arr[iterator] == 0) {
                    ++zeroCount;
                }
            } while (iterator + zeroCount < length - 1);
            //no zero just return
            if (0 == zeroCount) {
                return;
            }

            int i = length - 1;
            //超过数组本身，最后一个0仅拷贝，但不复写
            if (iterator + zeroCount == length) {
                arr[i--] = arr[iterator--];
            }
            while (i > 0) {
                //遇到0复写
                if (arr[iterator] == 0) {
                    arr[i--] = 0;
                }
                arr[i--] = arr[iterator--];
            }
        }
    }

    /**
     * Test
     * */
    public static void main(String[] args) {
        int[] Input = {1,5,2,0,6,8,0,6,0};
        System.out.println("Input:");
        MyPrint.printArray(Input);
        Solution s = new Solution();
        s.duplicateZeros(Input);
        System.out.println("Result:");
        MyPrint.printArray(Input);
    }
}