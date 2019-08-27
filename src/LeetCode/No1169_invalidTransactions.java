package LeetCode;

import java.util.ArrayList;
import java.util.List;

/**
 * 1169. 查询无效交易
 * 如果出现下述两种情况，交易 可能无效：
 *
 * 交易金额超过 ¥1000
 * 或者，它和[另一个城市]中[同名的]另一笔交易相隔不超过 60 分钟（包含 60 分钟整）
 * 每个交易字符串 transactions[i] 由一些用逗号分隔的值组成，这些值分别表示交易的名称，时间（以分钟计），金额以及城市。
 *
 * 给你一份交易清单 transactions，返回可能无效的交易列表。你可以按任何顺序返回答案。
 *
 *  
 *
 * 示例 1：
 *
 * 输入：transactions = ["alice,20,800,mtv","alice,50,100,beijing"]
 * 输出：["alice,20,800,mtv","alice,50,100,beijing"]
 * 解释：第一笔交易是无效的，因为第二笔交易和它间隔不超过 60 分钟、名称相同且发生在不同的城市。同样，第二笔交易也是无效的。
 * 示例 2：
 *
 * 输入：transactions = ["alice,20,800,mtv","alice,50,1200,mtv"]
 * 输出：["alice,50,1200,mtv"]
 * 示例 3：
 *
 * 输入：transactions = ["alice,20,800,mtv","bob,50,1200,mtv"]
 * 输出：["bob,50,1200,mtv"]
 *  
 *
 * 提示：
 *
 * transactions.length <= 1000
 * 每笔交易 transactions[i] 按 "{name},{time},{amount},{city}" 的格式进行记录
 * 每个交易名称 {name} 和城市 {city} 都由小写英文字母组成，长度在 1 到 10 之间
 * 每个交易时间 {time} 由一些数字组成，表示一个 0 到 1000 之间的整数
 * 每笔交易金额 {amount} 由一些数字组成，表示一个 0 到 2000 之间的整数
 *
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/invalid-transactions
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 *  coder:eisenhao
 *  Java
 *  20190827
 * */

public class No1169_invalidTransactions {
    static class Solution {
        /**
         * 交易信息 类
         */
        static class TransactionMSG {
            public String name;// 交易名称
            public int time;//交易时间, 0 到 1000 之间的整数
            public int amount;//交易金额, 0 到 2000 之间的整数
            public String city;//城市

            /**
             * 构造函数
             */
            public TransactionMSG(String transaction) {
                String[] MSG = transaction.split(",");
                this.name = MSG[0].trim();
                this.time = Integer.valueOf(MSG[1].trim());
                this.amount = Integer.valueOf(MSG[2].trim());
                this.city = MSG[3].trim();
            }

            /**
             * 自检函数
             *
             * @Return true 检测成功;  false 无效的交易记录
             */
            public boolean selfCheck() {
                return amount >= 0 && amount < 1001 &&
                        time >= 0 && time < 1001 &&
                        name.length() > 0 && name.length() < 11 &&
                        city.length() > 0 && city.length() < 11;
            }
        }

        /**
         * 解决函数
         */
        public List<String> invalidTransactions(String[] transactions) {
            if (null == transactions) return null;
            boolean[] invalidFLAG = new boolean[transactions.length];//记录每笔交易是否无效 false：表示有效，true:表示无效
            List<String> result = new ArrayList<>();
            List<TransactionMSG> transactionList = new ArrayList<TransactionMSG>();

            //填充到List
            for (int i = 0; i < transactions.length; ++i) {
                transactionList.add(new TransactionMSG(transactions[i]));
                invalidFLAG[i] = !transactionList.get(i).selfCheck();//自检是否无效
            }
            //判断同名不同城的时间间隔
            for (int i = 0; i < transactions.length - 1; ++i) {
                String name = transactionList.get(i).name;
                String city = transactionList.get(i).city;
                for (int j = i + 1; j < transactions.length; ++j) {
                    //若交易j与交易i非同名; 或城市名相同，跳过
                    if (!name.equals(transactionList.get(j).name) || city.equals(transactionList.get(j).city)) {
                        continue;
                    }
                    //若间隔不超过 60 分钟，两个交易都无效
                    int timeInterval = (transactionList.get(i).time > transactionList.get(j).time) ? transactionList.get(i).time - transactionList.get(j).time : transactionList.get(j).time - transactionList.get(i).time;
                    if (timeInterval <= 60) {
                        invalidFLAG[i] = true;
                        invalidFLAG[j] = true;
                    }
                }
            }
            //填充无效交易
            for (int i = 0; i < transactions.length; ++i) {
                if (invalidFLAG[i]) {
                    result.add(transactions[i]);
                }
            }
            return result;
        }
    }


    /**
    * Test
    * */
    public static void main(String[] args) {
        Solution solution = new Solution();
        String[] transactions = {"alice,20,800,mtv","alice,50,100,beijing"};
        List<String> result = solution.invalidTransactions(transactions);
        System.out.println("Output invalid transactions:");
        MyPrint.printArray(result);
    }
}
