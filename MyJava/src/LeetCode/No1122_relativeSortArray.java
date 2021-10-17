package LeetCode;

import java.util.Arrays;

/**
 * Leetcode
 *
 * 1122. 数组的相对排序
 *
 * 给你两个数组，arr1 和 arr2，
 *
 * arr2 中的元素各不相同
 * arr2 中的每个元素都出现在 arr1 中
 * 对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。
 *
 *
 * 示例：
 *
 * 输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
 * 输出：[2,2,2,1,4,3,3,9,6,7,19]
 *  
 *
 * 提示：
 *
 * arr1.length, arr2.length <= 1000
 * 0 <= arr1[i], arr2[i] <= 1000
 * arr2 中的元素 arr2[i] 各不相同
 * arr2 中的每个元素 arr2[i] 都出现在 arr1 中
 *
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/relative-sort-array
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 * coder:eisenhao
 * Java
 * 20190818
 * */

public class No1122_relativeSortArray {
    static class Solution {
        static final int RANGE = 1001;
        public int[] relativeSortArray(int[] arr1, int[] arr2) {
            //if arr2 is empty
            if (null == arr2 || arr2.length == 0) {
                if (null != arr1 && arr1.length > 1) {
                    Arrays.sort(arr1);
                }
                return arr1;
            }
            int length1 = arr1.length;
            int count[] = new int[RANGE];//default is 0
            int result[] = new int[length1];
            int iterator = 0;

            //count the occur-time of element of arr1
            for (int i: arr1) {
                count[i]++;
            }
            //push the final ordered elements of arr2 into result-array firstly
            for (int num: arr2) {
                for (int i = 0; i < count[num]; i++) {
                    result[iterator++] = num;
                }
                count[num] = 0;
            }
            //push the remain nums
            for (int i = 0; i < RANGE; i++) {
                if (count[i] > 0) {
                    for (int j = 0; j < count[i]; j++) {
                        result[iterator++] = i;
                    }
                }
            }
            return result;
        }
    }

    /**
     * Test
     * */
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] Input1 = {2,3,1,3,2,4,6,7,9,2,19};
        int[] Input2 = {2,1,4,3,9,6};
        int[] res = s.relativeSortArray(Input1, Input2);
        System.out.println("Input1:");
        MyPrint.printArray("Input1", Input1);
        System.out.println("Input2:");
        MyPrint.printArray("Input2", Input2);
        System.out.println("Result:");
        MyPrint.printArray("Result", res);
    }
}
