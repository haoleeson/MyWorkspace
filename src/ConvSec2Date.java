import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

/**
 long型秒数与日期互转
 author:eisenhao
 */
public class ConvSec2Date {
    private static final String DEF_PATTEN = "yyyy-MM-dd HH:MM:ss";
    private static final String DEF_PATTEN_DAY = "yyyy-MM-dd";
    private static final String MIN_FINDING_DATE = "1970-01-01";
    private static final String MAX_FINDING_DATE = "3000-01-01";
    private static final long MAX_FINDING_UTC_VALUE = 32503680000001L;// 支持寻找的最大时间

    /**
     * 毫秒数转日期时间
     * @param millisecond 毫秒数
     */
    public static String millisecond2Date(final long millisecond) {
        Calendar calendar = Calendar.getInstance();
        calendar.setTimeInMillis(millisecond);
        Date date = calendar.getTime();
        SimpleDateFormat sdf = new SimpleDateFormat(DEF_PATTEN);
        return sdf.format(date);
    }

    private static String millisecond2Day(final long millisecond) {
        Calendar calendar = Calendar.getInstance();
        calendar.setTimeInMillis(millisecond);
        Date date = calendar.getTime();
        SimpleDateFormat sdf = new SimpleDateFormat(DEF_PATTEN_DAY);
        return sdf.format(date);
    }

    // 获取当前毫秒数
    public static long getCurrTime() {
        Date date = new Date();
        long sec = date.getTime();
        return sec;
    }

    /**
     * 二分查找目标日期对应的的毫秒数（精确到天）
     * @param targetDateStr 输入日期 eg. 2050-01-01, 范围[1970-01-01 ~ 2100-01-01]
     */
    public static long dateStr2Millisecond(final String targetDateStr) {
        if (null == targetDateStr || targetDateStr.length() != DEF_PATTEN_DAY.length()) {
            System.out.println("[ERROR] invalid targetDateStr!");
            return 0L;
        }
        if (targetDateStr.compareTo(MIN_FINDING_DATE) < 0) {
            System.out.println("[ERROR] targetDateStr cannot earlier than " + MIN_FINDING_DATE);
            return 0L;
        }
        if (targetDateStr.compareTo(MAX_FINDING_DATE) > 0) {
            System.out.println("[ERROR] targetDateStr cannot over than " + MAX_FINDING_DATE);
            return 0L;
        }

        long left = 0;
        long right = MAX_FINDING_UTC_VALUE;// 2100-01-01 08:00:00
        long mid;
        String tmpDateSubStr = null;

        // 加速
        {
            long currentMillisecond = ConvSec2Date.getCurrTime();
            tmpDateSubStr = ConvSec2Date.millisecond2Day(currentMillisecond);
            if (targetDateStr.compareTo(tmpDateSubStr) > 0) {
                left = currentMillisecond;
            } else {
                right = currentMillisecond;
            }
        }

        // 二分查找
        while (true) {
            mid = (left + right) / 2;
            tmpDateSubStr = ConvSec2Date.millisecond2Day(mid);
            if (tmpDateSubStr.startsWith(targetDateStr)) {
                break;
            }
            if (tmpDateSubStr.compareTo(targetDateStr) > 0) {
                right = mid;
            } else {
                left = mid;
            }
        }
        // 抹去尾数，只精确到天
// mid -= mid % 86400000; // 一天的毫秒数为86400000
        System.out.println("find success, millisecond = " + mid + ", date = " + ConvSec2Date.millisecond2Date(mid));
        return mid;
    }

    public static void main(String[] args) {
        long currentTime = ConvSec2Date.getCurrTime();
        System.out.println("currentTime = " + currentTime);// 获取当前时间（毫秒值）
        long findTime = ConvSec2Date.dateStr2Millisecond("2050-01-01");// 日期转秒数
        System.out.println(ConvSec2Date.millisecond2Date(currentTime));// 秒数转日期
    }
}