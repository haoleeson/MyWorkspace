package LeetCode;

/** utf-8
 * Leetcode
 * 1010. 总持续时间可被 60 整除的歌曲
 * 示例 1：
 *
 * 输入：[30,20,150,100,40]
 * 输出：3
 * 解释：这三对的总持续时间可被 60 整数：
 * (time[0] = 30, time[2] = 150): 总持续时间 180
 * (time[1] = 20, time[3] = 100): 总持续时间 120
 * (time[1] = 20, time[4] = 40): 总持续时间 60
 * 示例 2：
 *
 * 输入：[60,60,60]
 * 输出：3
 * 解释：所有三对的总持续时间都是 120，可以被 60 整数。
 *
 *
 * 提示：
 *
 * 1 <= time.length <= 60000
 * 1 <= time[i] <= 500
 *
 * coder:eisenhao
 * Java
 * 20190405
 * */

public class No1010_pairsOfSongsWithTotalDurationsDivisibleBy60 {
    static class Solution {
        /**
         * combination
         * 特殊组合数 C(n, 2) = n * (n-1) / 2
         */
        public int C_n_2(int n) {
            if (n < 2) return 0;
            if (n == 2) return 1;
            return n * (n - 1) / 2;
        }

        public int numPairsDivisibleBy60(int[] time) {
            int len = time.length, matchNum = 0;//歌曲对数量
            int[] number = new int[60];//歌曲时长余数（求余 60）

            //统计 0 ～ 59 秒分布
            for (int i = 0; i < len; i++) {
                number[time[i] % 60]++;
            }
            //加上 0 的排列组合 C(m, 2)
            matchNum += C_n_2(number[0]);
            //加上 30 的排列组合 C(m, 2)
            matchNum += C_n_2(number[30]);
            //加上 1 ~ 29 与 对应的 59 ~ 31 数量的乘积
            for (int i = 1; i < 30; i++) {
                matchNum += number[i] * number[60 - i];
            }
            return matchNum;
        }
    }

    /**
     * Test
     * */
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] Input = {60,60,60};

        System.out.println(s.numPairsDivisibleBy60(Input));
    }
}
