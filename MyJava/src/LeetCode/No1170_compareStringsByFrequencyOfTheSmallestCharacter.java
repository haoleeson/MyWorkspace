package LeetCode;
import java.util.Arrays;

/**
 * 1170. 比较字符串最小字母出现频次
 *
 * 我们来定义一个函数 f(s)，其中传入参数 s 是一个非空字符串；该函数的功能是统计 s  中（按字典序比较）最小字母的出现频次。
 *
 * 例如，若 s = "dcce"，那么 f(s) = 2，因为最小的字母是 "c"，它出现了 2 次。
 *
 * 现在，给你两个字符串数组待查表 queries 和词汇表 words，请你返回一个整数数组 answer 作为答案，其中每个 answer[i] 是满足 f(queries[i]) < f(W) 的词的数目，W 是词汇表 words 中的词。
 *
 *  
 *
 * 示例 1：
 *
 * 输入：queries = ["cbd"], words = ["zaaaz"]
 * 输出：[1]
 * 解释：查询 f("cbd") = 1，而 f("zaaaz") = 3 所以 f("cbd") < f("zaaaz")。
 * 示例 2：
 *
 * 输入：queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
 * 输出：[1,2]
 * 解释：第一个查询 f("bbb") < f("aaaa")，第二个查询 f("aaa") 和 f("aaaa") 都 > f("cc")。
 *  
 *
 * 提示：
 *
 * 1 <= queries.length <= 2000
 * 1 <= words.length <= 2000
 * 1 <= queries[i].length, words[i].length <= 10
 * queries[i][j], words[i][j] 都是小写英文字母
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/compare-strings-by-frequency-of-the-smallest-character
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 * */


public class No1170_compareStringsByFrequencyOfTheSmallestCharacter {

    //方法1【64ms】. 普通方法
    static class Solution1 {
        /**
        * Function f(s), count the times of the smallest alphabet of s
        * @Return times
        * */
        public int f(String str) {
            int[] Alphabet = new int[26];//default value 0
            int times = 0;

            for (char ch : str.toCharArray()) {
                Alphabet[ch - 'a']++;
            }
            for (int i : Alphabet) {
                if (i > 0) {
                    times = i;
                break;
                }
            }
            return times;
        }
        /**
        * Function
        * @Input queries 待查表
        * @Input words 字典表
        * @Return answer 结果
        * */
        public int[] numSmallerByFrequency(String[] queries, String[] words) {
            if (null == queries || queries.length == 0 || null == words)
                return null;
            int length_Que = queries.length;
            int length_Wor = words.length;
            int[] answer = new int[length_Que];
            int[] f_words = new int[length_Wor];

            //calc f(words[i])
            for (int i=0; i<length_Wor; ++i) {
                f_words[i] = f(words[i]);
            }
            //sort f_words
            Arrays.sort(f_words);
            //calc queries
            for (int i =0; i<length_Que; i++) {
                int f_query_i = f(queries[i]);
                //compare f_words
                for (int j=0; j<length_Wor; j++) {
                    if (f_words[j] > f_query_i) {
                        answer[i] = length_Wor - j;
                        break;
                    }
                }
            }
            return answer;
        }
    }


    //方法2【23ms】. 移除 str.toCharArray() 方法
    static class Solution2 {
        /**
        * Function f(s), count the times of the smallest alphabet of s
        *
        * @Return times
        */
        public int f(String str) {
            int[] Alphabet = new int[26];//default value 0
            int iterator = 0;

            for (int i = 0; i < str.length(); i++) {
                Alphabet[str.charAt(i) - 'a']++;
            }
            while (Alphabet[iterator] == 0) {
                iterator++;
            }
            return Alphabet[iterator];
        }

        /**
        * Function
        *
        * @Input queries 待查表
        * @Input words 字典表
        * @Return answer 结果
        */
        public int[] numSmallerByFrequency(String[] queries, String[] words) {
//            //if error input
//            if (null == queries || queries.length == 0 || null == words)
//                return null;
//
//            int length_Que = queries.length;
//            int length_Wor = words.length;
            int[] answer = new int[queries.length];
            int[] f_words = new int[words.length];

            //count f(words[i])
            for (int i = 0; i < words.length; ++i) {
                f_words[i] = f(words[i]);
            }
            //sort f_words
            Arrays.sort(f_words);
            //count queries
            for (int i = 0; i < queries.length; i++) {
                int f_query_i = f(queries[i]);
                //compare f_words
                for (int j = 0; j < words.length; j++) {
                    if (f_words[j] > f_query_i) {
                        answer[i] = words.length - j;
                        break;
                    }
                }
            }
            return answer;
        }
    }


    //方法3【8ms】. 利用二分查找
    static class Solution3 {
        /**
        * Function f(s), count the times of the smallest alphabet of s
        *
        * @Return times
        */
        public int f(String str) {
            int[] Alphabet = new int[26];//default value 0
            int iterator = 0;

            for (int i = 0; i < str.length(); i++) {
                Alphabet[str.charAt(i) - 'a']++;
            }
            while (Alphabet[iterator] == 0) {
                iterator++;
            }
            return Alphabet[iterator];
        }

        /**
        * 统计nums数组中大于target的数字个数（二分查找）
        * f_words已正序（非递减）排序
        * @Return 返回nums中大于target的数字个数
        * */
        public int countTheBiggerNums(int[] nums, int target) {
            if (nums[0] > target)
                return nums.length;
            if (nums[nums.length-1] <= target)
                return 0;
            int mid;
            int left = 0;
            int right = nums.length-1;

            while (right > left) {
                mid = (left + right) / 2;
                if (nums[mid] <= target)
                    left = mid + 1;
                if (nums[mid] > target)
                    right = mid - 1;
            }
            while (nums[right] <= target) {
                right++;
            }
            return nums.length - right;
        }

        /**
        * Function
        *
        * @Input queries 待查表
        * @Input words 字典表
        * @Return answer 结果
        */
        public int[] numSmallerByFrequency(String[] queries, String[] words) {
//            //if error input
//            if (null == queries || queries.length == 0 || null == words)
//                return null;

            int[] answer = new int[queries.length];
            int[] f_words = new int[words.length];

            //count f(words[i])
            for (int i = 0; i < words.length; ++i) {
                f_words[i] = f(words[i]);
            }
            //sort f_words
            Arrays.sort(f_words);
            //count queries
            for (int i = 0; i < queries.length; i++) {
                int f_query_i = f(queries[i]);
                answer[i] = countTheBiggerNums(f_words, f_query_i);
            }
            return answer;
        }
    }


    //方法4【3ms】.Leetcode 大牛（学习）
    static class Solution {
        /**
         * 分析
         * 先找出最小出现的字符，再统计该字符出现次数
         * 利用了： 读数据的时间消耗 远小于 写数据 （尽量减少写操作）
         */
        public int getLength(String s) {
            char k = 'z';
            int count = 0;
            for (int i = 0; i < s.length(); i++) {
                if (k > s.charAt(i)) {
                    k = s.charAt(i);
                }
            }
            for (int i = 0; i < s.length(); i++) {
                if (k == s.charAt(i)) {
                    count++;
                }
            }
            return count;
        }

        /**
         * Function
         *
         * @Input queries 待查表
         * @Input words 字典表
         * @Return answer 结果
         */
        public int[] numSmallerByFrequency(String[] queries, String[] words) {
            int[] count = new int[words.length];
            for (int i = 0; i < words.length; i++) {
                count[i] = getLength(words[i]);
            }
            int[] amount= new int[12];
            for (int i = 0; i < count.length; i++) {
                amount[count[i]]++;
            }
            getCount(amount);
            int[] res = new int[queries.length];
            for (int i = 0; i < queries.length; i++) {
                int ks = getLength(queries[i]);
                res[i] = amount[ks+1];
            }
            return res;

        }

        /**分析：
         * 从后至前，累加当前项的值到前一项，方便快速得到 > f(queries[i])的个数。
         * 若queries[i]为1，则count[2]的值即是words2～12的总个数
         *
         * 利用了： 1 <= queries[i].length, words[i].length <= 10 和 简化不必要的重复计算
         * */
        public void getCount(int[] count) {
            int c = 0;
            for (int i = count.length -2; i >= 0; i--) {
                count[i] += count[i+1];
            }
        }
    }

    /**
    * Test
    * */
    public static void main(String[] args) {
        Solution3 solution = new Solution3();
        String[] queries = {"bbb","cc"};
        String[] words = {"a","aa","aaa","aaaa"};
        int[] answer = solution.numSmallerByFrequency(queries, words);
        MyPrint.printArray("answer", answer);
    }
}