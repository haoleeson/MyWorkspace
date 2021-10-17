package LeetCode;

import java.util.Arrays;

/** utf-8
 * Leetcode
 * 914. 卡牌分组
 * 给定一副牌，每张牌上都写着一个整数。
 *
 * 此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：
 *
 * 每组都有 X 张牌。
 * 组内所有的牌上都写着相同的整数。
 * 仅当你可选的 X >= 2 时返回 true。
 *
 *
 *
 * 示例 1：
 *
 * 输入：[1,2,3,4,4,3,2,1]
 * 输出：true
 * 解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
 * 示例 2：
 *
 * 输入：[1,1,1,2,2,2,3,3]
 * 输出：false
 * 解释：没有满足要求的分组。
 * 示例 3：
 *
 * 输入：[1]
 * 输出：false
 * 解释：没有满足要求的分组。
 * 示例 4：
 *
 * 输入：[1,1]
 * 输出：true
 * 解释：可行的分组是 [1,1]
 * 示例 5：
 *
 * 输入：[1,1,2,2,2,2]
 * 输出：true
 * 解释：可行的分组是 [1,1]，[2,2]，[2,2]
 *
 * coder:eisenhao
 * Java
 * 20190404
 * */

public class No914_xOfAKindInADeckOfCards {
    static class Solution {
        public boolean hasGroupsSizeX(int[] deck) {
            int len = deck.length, appearTimes = 1, timesSize = 0, minMUL;//重复次数，不重复整数的多少，最小重复次数;
//        ArrayList<Integer> times = new ArrayList<Integer>();//整数重复次数统计数组
//        int[] times = new int[len];

            //特殊值
            if (len < 2)
                return false;
            //排序
            Arrays.sort(deck);
            //统计重复次数
            for (int i = 1, lastNum = deck[0]; i < len; i++) {
                if (lastNum == deck[i]) {
                    appearTimes++;
                } else {
                    lastNum = deck[i];
//                times.add(appearTimes);
                    deck[timesSize++] = appearTimes;
                    appearTimes = 1;
                }
            }
//        times.add(appearTimes);//添加末尾重复次数
//        timesSize = times.size();
            deck[timesSize++] = appearTimes;//添加末尾重复次数

            // 找到重复次数数组内 最小值（对应整数的最小重复次数）
            minMUL = deck[0];
            for (int i = 0; i < timesSize; i++) {
                if (deck[i] < minMUL) {
                    minMUL = deck[i];
                }
            }
            //找到是否存在这样的组内元素个数 X，都能被每个整数的重复次数整除
            for (int x = 2, i = 0; x <= minMUL; x++) {
                i = 0;
                for (; i < timesSize; i++) {
                    if (deck[i] % x != 0)
                        break;
                }
                //是否找到所有重复次数都能整除 x
                if (i == timesSize) {
                    return true;
                }
            }
            return false;
        }
    }


    static void printArray(int Input[]) {
        for (int i = 0; i < Input.length; i++) {
            System.out.print(Input[i] + ", ");
        }
        System.out.println();
    }

    /**
     * Test
     * */
    public static void main(String[] args) {
        Solution s = new Solution();
        int Input[] = {1,1,2,2,3,2,2,1,1,3};

        System.out.println("Input = ");
        printArray(Input);
        System.out.println("Output = " );
        System.out.println(s.hasGroupsSizeX(Input));
        System.out.println("Input = ");
        printArray(Input);
    }
}
