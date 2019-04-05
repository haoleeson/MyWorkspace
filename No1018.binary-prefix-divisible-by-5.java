import java.util.ArrayList;
import java.util.List;

/** utf-8
 * Leetcode
 * 1018. 可被 5 整除的二进制前缀
 * 给定由若干 0 和 1 组成的数组 A。我们定义 N_i：从 A[0] 到 A[i] 的第 i 个子数组被解释为一个二进制数（从最高有效位到最低有效位）。
 *
 * 返回布尔值列表 answer，只有当 N_i 可以被 5 整除时，答案 answer[i] 为 true，否则为 false。
 *
 * 示例 1：
 *
 * 输入：[0,1,1]
 * 输出：[true,false,false]
 * 解释：
 * 输入数字为 0, 01, 011；也就是十进制中的 0, 1, 3 。只有第一个数可以被 5 整除，因此 answer[0] 为真。
 * 示例 2：
 *
 * 输入：[1,1,1]
 * 输出：[false,false,false]
 * 示例 3：
 *
 * 输入：[0,1,1,1,1,1]
 * 输出：[true,false,false,false,true,false]
 * 示例 4：
 *
 * 输入：[1,1,1,0,1]
 * 输出：[false,false,false,false,false]
 *
 *
 * 提示：
 *
 * 1 <= A.length <= 30000
 * A[i] 为 0 或 1
 *
 * coder:eisenhao
 * Java
 * 20190405
 * */


class Solution {
    /**
     * 利用 (A + B) % 5 = ((A % 5) + (B % 5)) % 5
     * 实际 sum % 5 = ( sum' * 2 % 5  + A[i] % 5) % 5
     * 化简 sum % 5 = ( sum' * 2 + A[i]) % 5
     * 利用中间值，每次对5球余
     * */
    public List<Boolean> prefixesDivBy5(int[] A) {
        int len=A.length, sum=0;
        List<Boolean> answer = new ArrayList<Boolean>();

        for (int i=0; i<len; i++) {
            sum = (sum * 2 + A[i]) % 5;
            answer.add(sum == 0);
        }
        return answer;
    }

    /**
     * 思路：http://www.dewen.net.cn/q/1827?sort=active
     *
     * 535的二进制1000010111，可以被5整除。
     * 1：摘取535的偶数位置的二进制数：00111,奇数位置的数字10001
     * 2：交替给予符号+-进行加和
     * 偶数位置为+0-0+1-1+1 = 1
     * 奇数位置为+1-0+0-0+1 = 2
     * 3：计算奇数位置加和的2倍加上偶数位置的加和，2×2+1=5,这个结果可以被5整除，则原数535可以被5整除，否则就不能被5整除。
     * */
    public List<Boolean> prefixesDivBy5_1(int[] A) {
        int len=A.length, jiSize=0, jiSum=0, ouSize=0, ouSum=0;//奇数位个数及二进制的计算和，偶数位个数及二进制的计算和
        List<Boolean> answer = new ArrayList<Boolean>();

        for (int i=0; i<len; i++) {
            //奇数位置时（偶数下标）
            if ((i&1)==0) {
                ++jiSize;//奇数位二进制数个数加一
                jiSum += (jiSize&1)==1 ? A[i] : -A[i];//(交替加减)
            }
            //偶数位置时（奇数下标）
            else {
                ++ouSize;//偶数位二进制数个数加一
                ouSum += (ouSize&1)==1 ? A[i] : -A[i];//(交替加减)
            }
            answer.add((jiSum * 2 + ouSize) % 5 == 0);
        }
        return answer;
    }

    /**初始方法：超出int大小限制（溢出错误）*/
    public List<Boolean> prefixesDivBy5_0(int[] A) {
        int len=A.length, num=0;
        List<Boolean> answer = new ArrayList<Boolean>();

        for (int i=0; i<len; i++) {
            num = A[i] + (num<<1);
            answer.add(num % 5 == 0);
        }
        return answer;
    }
}

public class Main {
    public static void main(String[] args) {
        Solution s = new Solution();
        int[] Input = {1,0,0,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,0,0,1,1,0,1,0,0,0,1};
        System.out.println(s.prefixesDivBy5(Input));
    }
}
