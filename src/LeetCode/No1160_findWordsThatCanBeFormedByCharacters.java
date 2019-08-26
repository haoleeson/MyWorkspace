package LeetCode;

/**
 * Leetcode
 *
 * 1160. 拼写单词
 *
 * 给你一份『词汇表』（字符串数组） words 和一张『字母表』（字符串） chars。
 *
 * 假如你可以用 chars 中的『字母』（字符）拼写出 words 中的某个『单词』（字符串），那么我们就认为你掌握了这个单词。
 *
 * 注意：每次拼写时，chars 中的每个字母都只能用一次。
 *
 * 返回词汇表 words 中你掌握的所有单词的 长度之和。
 *
 *  
 *
 * 示例 1：
 *
 * 输入：words = ["cat","bt","hat","tree"], chars = "atach"
 * 输出：6
 * 解释：
 * 可以形成字符串 "cat" 和 "hat"，所以答案是 3 + 3 = 6。
 * 示例 2：
 *
 * 输入：words = ["hello","world","leetcode"], chars = "welldonehoneyr"
 * 输出：10
 * 解释：
 * 可以形成字符串 "hello" 和 "world"，所以答案是 5 + 5 = 10。
 *  
 *
 * 提示：
 *
 * 1 <= words.length <= 1000
 * 1 <= words[i].length, chars.length <= 100
 * 所有字符串中都仅包含小写英文字母
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/find-words-that-can-be-formed-by-characters
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 * coder:eisenhao
 * Java
 * 20190818
 * */

public class No1160_findWordsThatCanBeFormedByCharacters {
    static class Solution {
        private static int chars_len;//chars字符串长度
        private static int[] chars_count = new int[26];//chars字符串中每个字母个数
        /**
         * 判断某字符串是否能被拼写出
         * Input:   string
         * return:  0(不能被拼出);  N(能被拼出，返回字符串长度)
         * */
        private int canBeSpell(String str) {
            if (null == str || chars_len < str.length()) {
                return 0;
            }
            int[] strCharCount = new int[26];
            //chars_count chars of str
            for (char ch : str.toCharArray()) {
                strCharCount[ch - 'a']++;
            }
            //compare
            for(int i=0; i<26; i++) {
                if (strCharCount[i] > chars_count[i]) {
                    return 0;
                }
            }
            return str.length();
        }

        /**
         * 计算能够被拼写出字符串字母总个数
         * */
        public int countCharacters(String[] words, String chars) {
            if (null == chars || chars.length() == 0) {
                return 0;
            }
            int result = 0;
            //Clear
            for (int i = 0; i < 26; i++) {
                chars_count[i] = 0;
            }
            chars_len = chars.length();
            //chars_count chars of chars
            for (char ch : chars.toCharArray()) {
                chars_count[ch - 'a']++;
            }
            //chars_count each str
            for(String str : words) {
                result += canBeSpell(str);
            }
            return result;
        }
    }

    /**
     * Test
     * */
    public static void main(String[] args) {
        Solution solution = new Solution();
        String[] words = {"hello","world","leetcode"};
        String chars = "welldonehoneyr";
        System.out.println(solution.countCharacters(words, chars));

    }
}
