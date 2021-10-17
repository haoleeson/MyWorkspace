// UTF-8

import java.text.DecimalFormat;

/**
 * 经济学概念 ———— 复利，复利简单计算
 * */

public class CompoundInterest {
    private double annualizedInterestRate;  // 约定平均年化收益率
    private int monthlyInvestment;          // 每月投入
    private int years;                      // 持续投入年限

    private int cumulativeInput;            // 累计投入
    private double totalAmount;             // 总金额
    private double cumulativeIncome;        // 累计收益
    private double returnRatio;             // 累计回报比率

    /**
     * @param annualizedInterestRate    约定平均年化收益率 %
     * @param monthlyInvestment         每月投入
     * @param years                     持续投入年限
     */
    public CompoundInterest(double annualizedInterestRate, int monthlyInvestment, int years) {
        this.annualizedInterestRate = annualizedInterestRate;
        this.monthlyInvestment = monthlyInvestment;
        this.years = years;
        cumulativeInput = 0;
        totalAmount = 0;
        cumulativeIncome = 0;
        returnRatio = 0;
    }
    /**
     * 显示每年复利情况
     * */
    public void calcFunc() {
        System.out.println("经济学概念 ———— 复利（钱生钱）\n    如果每月投入闲钱" + monthlyInvestment + "元，" +
                "约定平均年化收益率为" + annualizedInterestRate + "%，" +
                "坚持投入" + years + "年，利息不取出继续投入，那么：");
        cumulativeInput = 0;
        totalAmount = 0;
        cumulativeIncome = 0;
        returnRatio = 0;
        DecimalFormat decimalFormat = new DecimalFormat("###,###");
        // 按年计算
        for (int i = 1; i <= years; i++) {
            // 计算今年当年投入金额
            int investmentThisyear = 12 * monthlyInvestment;
            // 计算今年收益（之前累计 + 今年投入）* 回报率
            double incomeThisYear = (totalAmount + investmentThisyear) * annualizedInterestRate / 100;
            // 更新累计收益
            cumulativeIncome += incomeThisYear;
            // 更新总金额
            totalAmount += investmentThisyear + incomeThisYear;
            // 更新累计投入(不计算每年复利投入)
            cumulativeInput += investmentThisyear;
            // 计算累计回报比率%（累计收益/累计投入）
            returnRatio = cumulativeIncome / cumulativeInput * 100;

            // 显示信息
            System.out.println("\n第" + i + "年" +
                    "\n累计投入 / 总金额：\n" + decimalFormat.format(cumulativeInput) + " / " + decimalFormat.format(totalAmount) + " (" + String.format("%.0f", returnRatio) + "%)");
        }
    }
    /**
     * 需要多少年成为百万富翁
     * */
    public int yearsRequired() {
        cumulativeInput = 0;
        totalAmount = 0;
        cumulativeIncome = 0;
        returnRatio = 0;
        // 按年计算
        for (int i = 1; ; i++) {
            // 计算今年当年投入金额
            int investmentThisyear = 12 * monthlyInvestment;
            // 计算今年收益（之前累计 + 今年投入）* 回报率
            double incomeThisYear = (totalAmount + investmentThisyear) * annualizedInterestRate / 100;
            // 更新累计收益
            cumulativeIncome += incomeThisYear;
            // 更新总金额
            totalAmount += investmentThisyear + incomeThisYear;
            // 更新累计投入(不计算每年复利投入)
            cumulativeInput += investmentThisyear;
            // 计算累计回报比率%（累计收益/累计投入）
            returnRatio = cumulativeIncome / cumulativeInput * 100;
            // 如果总金额大于100万，跳出
            if (totalAmount > 1000000) {
                return i;
            }
        }
    }

    public static void main(String[] args) {
        CompoundInterest compoundInterest = new CompoundInterest(10, 1000, 23);
        compoundInterest.calcFunc();
        System.out.println("\n\n》》》 成为百万富翁需要：" + compoundInterest.yearsRequired() + " 年《《《");
    }
}
