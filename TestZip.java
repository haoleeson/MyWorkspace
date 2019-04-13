import java.io.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipOutputStream;

/** utf-8
 * Leetcode
 * 714. 买卖股票的最佳时机含手续费
 * 给定一个整数数组 prices，其中第 i 个元素代表了第 i 天的股票价格 ；非负整数 fee 代表了交易股票的手续费用。
 *
 * 你可以无限次地完成交易，但是你每次交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
 *
 * 返回获得利润的最大值。
 *
 * 示例 1:
 *
 * 输入: prices = [1, 3, 2, 8, 4, 9], fee = 2
 * 输出: 8
 * 解释: 能够达到的最大利润:
 * 在此处买入 prices[0] = 1
 * 在此处卖出 prices[3] = 8
 * 在此处买入 prices[4] = 4
 * 在此处卖出 prices[5] = 9
 * 总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
 * 注意:
 *
 * 0 < prices.length <= 50000.
 * 0 < prices[i] < 50000.
 * 0 <= fee < 50000.
 *
 * coder:eisenhao
 * Java
 * 20190412
 * */


/** 压缩文件类*/
class TestZip {
    /**
     * 加壳压缩文件函数
     * 输入参数：zipFileName -- 压缩后的文件名，inputFile -- 待压缩文件
     * */
    public void zipFile(String zipFileName, File inputFile) throws Exception{
        ZipOutputStream out = new ZipOutputStream(new FileOutputStream(zipFileName));
        zip(out, inputFile, ""); //相对目录进入点为空
        out.close();//关闭压缩流
    }
    /**
     * 压缩文件核心函数
     * 输入参数：zipout - 压缩流、file - 待压缩文件、base - 目录进入点
     * 若为单个文件 - 直接拷贝压缩，若为目录文件 - 递归调用自身
     * */
    private void zip(ZipOutputStream zipout, File file, String base) throws Exception{
        //判断文件是否为目录文件
        if (file.isDirectory()) {
            //若问文件夹，列出待压缩文件夹内所有文件
            File[] fl = file.listFiles();//获取路径数组
            if (base.length() != 0) {
                zipout.putNextEntry(new ZipEntry(base + "/"));//写入此目录的entry（目录树）
            }
            //循环遍历待压缩文件夹内的所有文件(可能存在多级文件夹)
            for (int i = 0; i < fl.length; i++) {
                zip(zipout, fl[i], base + fl[i]);//递归调
            }
        }
        //若为单个文件，直接拷贝压缩
        else {
            zipout.putNextEntry(new ZipEntry(base));//创建新的进入点
            //创建FileInputStream写出流对象
            FileInputStream in = new FileInputStream(file);
            int ch;
            System.out.println("压缩 " + base + " 位置的 " + file.getName() + " 文件 ...");//打印当前目录进入点
            //逐一字节拷贝压缩
            while ((ch = in.read()) != -1) {
                zipout.write(ch);//将字节写入当前ZIP条目
            }
            in.close();//关闭读取流
        }
    }

    public static void main(String[] args) {
        TestZip testZip = new TestZip();
        //尝试压缩
        String zipFileName = "/Users/eisenhao/Downloads/Test.zip";//压缩后得到的文件名
        String inputFile = "/Users/eisenhao/Test/";//待压缩文件（可谓普通文件 或 目录文件）
        System.out.println("尝试压缩 " + inputFile + " 到 " + zipFileName + " ...");
        try {
            testZip.zipFile(zipFileName, new File(inputFile));//调用加壳压缩文件函数
            System.out.println("压缩完成:)");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
