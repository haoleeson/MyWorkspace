import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;

/** 解压缩类
 * coder:eisenhao
 * Java
 * 20190414*/
public class UnzipTest {
    /**
     * 解压缩文件方法，解压到当前目录
     * 参数：unZipFileName -- 待解压缩文件名（含路径）
     * */
    void Unzip(String unZipFileName) throws Exception {
        File unzipFile = new File(unZipFileName);//获取待压缩文件 对象
        String finalPath = unzipFile.getParentFile() + "/";//得到待解压缩文件的绝对路径
        ZipFile zipFile = new ZipFile(unzipFile);//创建Zip压缩文件 对象
        ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(unzipFile));//实例化解压缩ZipInputStream对象
        ZipEntry entry;

        //迭代解压缩所有目录树上的文件（包括目录文件）
        while ((entry=zipInputStream.getNextEntry())!=null && !entry.isDirectory()) {
            File tmp = new File(finalPath + entry.getName());//解压出的文件路径
            //如果文件不存在
            if (!tmp.exists()) {
                tmp.getParentFile().mkdirs();//创建父类文件夹路径
                OutputStream writeStream = new FileOutputStream(tmp);//将文件目录中的文件放入输出流
                System.out.println("解压缩 " + tmp.getAbsolutePath() + " 文件 ...");
                //用输入流读取压缩文件中制定目录中的文件
                InputStream readStream = zipFile.getInputStream(entry);
                int ch = 0;
                while ((ch = readStream.read()) != -1) {
                    writeStream.write(ch);
                }
                writeStream.close();//关闭写文件流
                readStream.close();//关闭读文件流
            }
            zipInputStream.closeEntry();//关闭当前Entry
        }
        zipInputStream.close();//关闭解压缩流
        System.out.println("解压缩已完成:)");
    }

    public static void main(String[] args) {
        UnzipTest unzipTest = new UnzipTest();
        String unzipFileName = "/Users/eisenhao/Downloads/Test.zip";//待解压缩文件名（含路径）
        try {
            unzipTest.Unzip(unzipFileName);//尝试解压缩
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
