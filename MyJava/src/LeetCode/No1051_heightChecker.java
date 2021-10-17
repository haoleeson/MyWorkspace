package LeetCode;

import java.util.Arrays;

/**
 * Leetcode
 * 1051. 高度检查器
 * 学校在拍年度纪念照时，一般要求学生按照 非递减 的高度顺序排列。
 *
 * 请你返回至少有多少个学生没有站在正确位置数量。该人数指的是：能让所有学生以 非递减 高度排列的必要移动人数。
 *
 * 示例：
 *
 * 输入：[1,1,4,2,1,3]
 * 输出：3
 * 解释：
 * 高度为 4、3 和最后一个 1 的学生，没有站在正确的位置。
 *  
 *
 * 提示：
 *
 * 1 <= heights.length <= 100
 * 1 <= heights[i] <= 100
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/height-checker
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 * coder:eisenhao
 * Java
 * 20190818
 * */

public class No1051_heightChecker {
    static class Solution {
        public int heightChecker(int[] heights) {
            int result = 0;
            int length = 0;
            if (heights == null || (length = heights.length) < 2) {
                return 0;
            }
            int array[] = new int[length];
            for (int i = 0; i < length; i++) {
                array[i] = heights[i];
            }
            //sort
            Arrays.sort(array);
            //count diff
            for (int i = 0; i < length; i++) {
                if (array[i] != heights[i]) {
                    ++result;
                }
            }
            return result;
        }
    }

    /**
     * Test
     * */
    public static void main(String[] args) {
        int[] Input = {1,1,4,2,1,3};
        MyPrint.printArray("Input", Input);
        Solution s = new Solution();

        System.out.println(s.heightChecker(Input));
    }
}
