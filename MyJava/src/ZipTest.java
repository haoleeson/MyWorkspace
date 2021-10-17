import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

/** 压缩文件类
 * coder:eisenhao
 * Java
 * 20190414*/
public class ZipTest {
    /**
     * 加壳压缩文件函数
     * 输入参数：zipFileName -- 压缩后的文件名，inputFile -- 待压缩文件
     * */
    public void zipFile(String zipFileName, File inputFile) throws Exception {
        File unzipFile = new File(zipFileName);//获取待压缩文件 对象
        String Base = inputFile.getName();//得到待压缩文件名
        ZipOutputStream out = new ZipOutputStream(new FileOutputStream(zipFileName));//新建ZipOutputStream对象
        zip(out, inputFile, Base); //相对目录进入点为空
        out.close();//关闭压缩流
    }
    /**
     * 压缩文件核心函数
     * 输入参数：zipout - 压缩流、file - 待压缩文件、base - 目录进入点
     * 若为单个文件 - 直接拷贝压缩，若为目录文件 - 递归调用自身
     * */
    private void zip(ZipOutputStream zipout, File file, String base) throws Exception {
        //判断文件是否为目录文件
        if (file.isDirectory()) {
            //若问文件夹，列出待压缩文件夹内所有文件
            File[] fl = file.listFiles();//获取路径数组
            //循环遍历待压缩文件夹内的所有文件(可能存在多级文件夹)
            for (int i = 0; i < fl.length; i++) {
                String tmpBase = base + "/" + fl[i].getName();//路径写入点为
                zip(zipout, fl[i], tmpBase);//递归调
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
        ZipTest zipTest = new ZipTest();
        //尝试压缩
        String zipFileName = "/Users/eisenhao/Downloads/Test.zip";//压缩后得到的文件名
        String inputFile = "/Users/eisenhao/Test/";//待压缩文件（可谓普通文件 或 目录文件）
        System.out.println("尝试压缩 " + inputFile + " 到 " + zipFileName + " ...");
        try {
            zipTest.zipFile(zipFileName, new File(inputFile));//调用加壳压缩文件函数
            System.out.println("压缩完成:)");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
