package LeetCode;


import java.util.HashMap;

/**
 * 560. 和为K的子数组
 *
 * 给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。
 *
 * 示例 1 :
 *
 * 输入:nums = [1,1,1], k = 2
 * 输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
 * 说明 :
 *
 * 数组的长度为 [1, 20,000]。
 * 数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/subarray-sum-equals-k
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 *  coder:eisenhao
 *  Java
 *  20190901
 * */

public class No560_subarraySumEqualsK {
    /**
     * 常规解法1  先累加减少计算
     * o(n^2 + n)
     * 执行用时 : 543 ms
     * 内存消耗 : 43.3 MB
     * */
    static class Solution1 {
        public int subarraySum(int[] nums, int k) {
            //error input
            if (null == nums || nums.length < 1)
                return 0;
            int ans = 0;
            int[] accAdd = new int[nums.length];

            accAdd[0] = nums[0];
            for (int i = 1; i < nums.length; i++) {
                accAdd[i] = accAdd[i-1] + nums[i];
            }

            //以i为子数组尾部
            for (int i = 0; i < nums.length; i++) {
                if (k == accAdd[i])
                    ans++;
                for (int j = 0; j < i; j++) {
                    if (k == (accAdd[i] - accAdd[j]))
                        ans++;
                }
            }
            return ans;
        }
    }

    /**
     * 常规解法1_p； 去掉累加
     * o(n^2)
     * 执行用时 : 481 ms
     * 内存消耗 : 43.2 MB
     * */
    static class Solution1_p {
        public int subarraySum(int[] nums, int k) {
            //error input
            if (null == nums || nums.length < 1)
                return 0;
            int ans = 0, subSum = 0;

            //以i为子数组尾部
            for (int i = 0; i < nums.length; i++) {
                subSum = nums[i];
                if (k == subSum)
                    ans++;
                for (int j = i-1; j >= 0; j--) {
                    subSum += nums[j];
                    if (k == subSum)
                        ans++;
                }
            }
            return ans;
        }
    }

    /**
     * 常规解法1_2p；  去掉一个if判断
     * o(n^2)
     * 执行用时 : 472 ms
     * 内存消耗 : 42.9 MB
     * */
    static class Solution1_2p {
        public int subarraySum(int[] nums, int k) {
            //error input
            if (null == nums || nums.length < 1)
                return 0;
            int ans = 0, subSum = 0, j;

            //以i为子数组尾部
            for (int i = 0; i < nums.length; i++) {
                subSum = 0;
                j = i;
                while (j > -1) {
                    subSum += nums[j];
                    if (k == subSum)
                        ans++;
                    j--;
                }
            }
            return ans;
        }
    }

    /**
     * Leetcode大牛解法2：Dp  HashMap
     * o(n)
     *
     * 思路：
     * // 表示[0,0)的值和计数，使用到这个值表示子树组从0开始
     *      * // sum-k的值存在的话，假设为j，则[0,j)是sum-k而[0,i)是sum，所以[j,i)就是k
     *      * // j是可能有多个取值的，造成计数值不同，而j为0的时候命中我们赋给的边界（初始）值
     *
     * 执行用时 : 41 ms
     * 内存消耗 : 49.3 MB
     * */
    static class Solution2 {
        public int subarraySum(int[] nums, int k) {
            // 连续但是长度不固定，n*n很容易，能否优化
            int count = 0, sum = 0;

            // 不排序，使用hash
            HashMap<Integer, Integer> map = new HashMap();
            map.put(0, 1);//表示 如果当前值： sum - k 为0的话， 则value为1（初始值，该值就是k）
            for (int i = 0; i < nums.length; ++i) {
                sum += nums[i];
                count += map.getOrDefault(sum - k, 0);//若在hash表找不到 key对应的value，就返回默认值 0
                // 把当前值入hash，如果已经存在的话就累加计数
                map.put(sum, 1 + map.getOrDefault(sum, 0));
            }
            return count;
        }
    }


    /**
     * Leetcode大牛解法3_p[优化, 条件写count]：Dp  HashMap o(n)
     *
     * 思路：
     * // 表示[0,0)的值和计数，使用到这个值表示子树组从0开始
     * // sum-k的值存在的话，假设为j，则[0,j)是sum-k而[0,i)是sum，所以[j,i)就是k
     * // j是可能有多个取值的，造成计数值不同，而j为0的时候命中我们赋给的边界（初始）值
     *
     * 执行用时 : 38 ms
     * 内存消耗 : 50 MB
     * */
    static class Solution {
        public int subarraySum(int[] nums, int k) {
            HashMap<Integer, Integer> map = new HashMap();
            map.put(0, 1);//表示 如果当前值： sum - k 为0的话， 则value为1（初始值，该值就是k）
            int count = 0, sum = 0;

            for (int i = 0; i < nums.length; ++i) {
                sum += nums[i];
                if (map.containsKey(sum - k))
                    count += map.get(sum - k);
                // 把当前值入hash，如果已经存在的话就累加计数
                map.put(sum, 1 + map.getOrDefault(sum, 0));//初始值为1，表示后面能找到此刻的sum（即后手的sum-k），则加value值 1
            }
            return count;
        }
    }


    /**
     * Test
     * */
    public static void main(String[] args) {
        Solution solution = new Solution();
        int[] nums = {1,1,1};
        int k = 2;

        System.out.println("result = " + solution.subarraySum(nums, k));
    }
}
