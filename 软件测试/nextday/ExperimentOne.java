package nextday;

import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.Assert.*;

/**
 * 实验一测试类
 * @author 梁芮槐-2019302789
 */
public class ExperimentOne {
    @Rule
    public ExpectedException thrown = ExpectedException.none();

    private PrintStream console = null;
    private ByteArrayOutputStream bytes = null;

    /**
     * ***** NextDay *****
     * NextDay测试
     */
    @Test
    public void initNextDay() {
        Date date10_30_2021 = new Date(10, 30, 2021);
        String expected = "10/31/2021";
        Nextday nextday = new Nextday();

        assertEquals(expected, nextday.nextDay(date10_30_2021).toString());
    }

    /**
     * ***** Date *****
     * 初始化Date 包括错误日期、错误月份、错误年份、全部正确
     */
    @Test
    public void initDate() {
        Date date10_30_2021 = new Date(10, 30, 2021);

        try{
            Date date10_33_2021 = new Date(10, 33, 2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid day")); }

        try{
            Date date13_30_2021 = new Date(13, 30, 2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid month")); }

        try{
            Date date10_30_0 = new Date(10, 30, 0);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid year")); }
    }

    /**
     * ***** Date *****
     * 测试日期的加一 包括月份最后一天、年份最后一天、普通一天
     */
    @Test
    public void incrementDate() {
        Date date10_30_2021 = new Date(10, 30, 2021);
        Date date10_31_2021 = new Date(10, 31, 2021);
        Date date12_31_2021 = new Date(12, 31, 2021);

        date10_30_2021.increment();
        date10_31_2021.increment();
        date12_31_2021.increment();
        assertEquals("10/31/2021", date10_30_2021.toString());
        assertEquals("11/1/2021", date10_31_2021.toString());
        assertEquals("1/1/2022", date12_31_2021.toString());
    }

    /**
     * 测试前的操作
     * 为了测是printDate() 重定向输出到bytes并进行输出内容检查
     */
    @Before
    public void setUp() {
        bytes = new ByteArrayOutputStream(); //把标准输出指定到ByteArrayOutputStream中
        console = System.out; // 获取System.out 输出流的句柄
        System.setOut(new PrintStream(bytes)); //将原本输出到控制台Console的字符流重定向到bytes
    }

    /**
     * ***** Date *****
     * 测试日期字符串输出
     */
    @Test
    public void printDate() {
        Date date10_30_2021 = new Date(10, 30, 2021);
        String expected = "10/30/2021";
        date10_30_2021.printDate();
        assertEquals(expected, bytes.toString().trim().replace("\r",""));
    }

    /**
     * 测试后的操作
     * 重新把输出定向到终端
     */
    @After
    public void tearDown() {
        System.setOut(console);
    }

    /**
     * ***** Date *****
     * 测试日期单元信息获取
     */
    @Test
    public void getSomethingFromDate() {
        Date date10_30_2021 = new Date(10, 30, 2021);
        assertEquals(30, date10_30_2021.getDay().getDay());
        assertEquals(10, date10_30_2021.getMonth().getMonth());
        assertEquals(2021, date10_30_2021.getYear().getYear());
    }

    /**
     * ***** Date *****
     * 测试equals()
     */
    @Test
    public void testEqualsDate() {
        Date date10_30_2021 = new Date(10, 30, 2021);
        Date date10_d30_2021 = new Date(10, 30, 2021);
        Date date10_29_2021 = new Date(10, 29, 2021);
        Date date11_30_2021 = new Date(11, 30, 2021);
        Date date10_30_2022 = new Date(10, 30, 2022);
        assertTrue(date10_30_2021.equals(date10_d30_2021));
        assertFalse(date10_30_2021.equals(date10_29_2021));
        assertFalse(date10_30_2021.equals(date11_30_2021));
        assertFalse(date10_30_2021.equals(date10_30_2022));
    }

    /**
     * ***** Date *****
     * 测试Date转字符串
     */
    @Test
    public void testToStringDate() {
        Date date10_30_2021 = new Date(10, 30, 2021);
        String expected = "10/30/2021";
        assertEquals(expected, date10_30_2021.toString());
    }

    /**
     * ***** Day *****
     * 测试Day初始化 包括正确、日期错误、月份错误、年份错误
     */
    @Test
    public void initDay() {
        Year year2021 = new Year(2021);
        Month month10_y2021 = new Month(10, year2021);
        Day day30_m10_y2021 = new Day(30, month10_y2021);

        try{
            Day day33_m10_y2021 = new Day(33, month10_y2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid day")); }

        try{
            Day day0_m10_y2021 = new Day(0, month10_y2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid day")); }

        try{
            Day day33_m10_y2021 = new Day(33, new Month(13, year2021));
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid month")); }

        try{
            Year year0 = new Year(0);
            Day day33_m10_y2021 = new Day(33, new Month(10, year0));
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid year")); }
    }

    /**
     * ***** Day *****
     * 测试Day加一 包括最后一天加一的正当性验证
     */
    @Test
    public void dayIncrementWithUnpredictableInit() {
        Year year2021 = new Year(2021);
        Month month10_y2021 = new Month(10, year2021);
        Day day30_m10_y2021 = new Day(30, month10_y2021);
        Day day31_m10_y2021 = new Day(31, month10_y2021);
        assertTrue(day30_m10_y2021.increment());
        assertFalse(day31_m10_y2021.increment());
    }

    /**
     * ***** Day *****
     * 测试获取当前日期
     */
    @Test
    public void getDay() {
        Year year2021 = new Year(2021);
        Month month10_y2021 = new Month(10, year2021);
        Day day30_m10_y2021 = new Day(30, month10_y2021);
        assertEquals(30, day30_m10_y2021.getDay());
        day30_m10_y2021.increment();
        assertEquals(31, day30_m10_y2021.getDay());
    }

    /**
     * ***** Day *****
     * 测试Equals()
     */
    @Test
    public void testEqualsDay() {
        int c = 10;
        Year year2021 = new Year(2021);
        Month month10_y2021 = new Month(10, year2021);
        Day day10_m10_y2021 = new Day(10, month10_y2021);
        Day day11_m10_y2021 = new Day(11, month10_y2021);
        assertFalse(day10_m10_y2021.equals(day11_m10_y2021));
        assertFalse(day10_m10_y2021.equals(c));
        day10_m10_y2021.increment();
        assertTrue(day10_m10_y2021.equals(day11_m10_y2021));
    }

    /**
     * ***** Month *****
     * 初始化Month 月份输错与输对
     */
    @Test
    public void setMonthWithUnpredictableMonth() {
        Year year2021 = new Year(2021);
        Month month10 = new Month(10, year2021);
        try {
            Month month13 = new Month(13, year2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid month")); }

        try {
            Month month0 = new Month(0, year2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid month")); }
    }

    /**
     * ***** Month *****
     * 初始化Month 年份输错与输对 年份月份都输错
     */
    @Test
    public void setMonthWithUnpredictableYear() {
        Year year2021 = new Year(2021);
        Year year_2021 = new Year(-2021);

        Month month10 = new Month(10, year2021);
        try {
            Month month10_y2021 = new Month(10, year_2021);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid month")); }

        try {
            Month month10_y0 = new Month(10, new Year(0));
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid year")); }
    }

    /**
     * ***** Month *****
     * 测试获取当前月份 以及获取当前月份的天数 包括闰年与非闰年
     */
    @Test
    public void getMonthAndMonthSize() {
        Year year2021 = new Year(2021);
        Year year2020 = new Year(2020);

        Month month1_y2021 = new Month(1, year2021);
        Month month2_y2021 = new Month(2, year2021);
        Month month3_y2021 = new Month(3, year2021);
        Month month4_y2021 = new Month(4, year2021);
        Month month5_y2021 = new Month(5, year2021);
        Month month6_y2021 = new Month(6, year2021);
        Month month7_y2021 = new Month(7, year2021);
        Month month8_y2021 = new Month(8, year2021);
        Month month9_y2021 = new Month(9, year2021);
        Month month10_y2021 = new Month(10, year2021);
        Month month11_y2021 = new Month(11, year2021);
        Month month12_y2021 = new Month(12, year2021);

        Month month1_y2020 = new Month(1, year2020);
        Month month2_y2020 = new Month(2, year2020);
        Month month3_y2020 = new Month(3, year2020);
        Month month4_y2020 = new Month(4, year2020);
        Month month5_y2020 = new Month(5, year2020);
        Month month6_y2020 = new Month(6, year2020);
        Month month7_y2020 = new Month(7, year2020);
        Month month8_y2020 = new Month(8, year2020);
        Month month9_y2020 = new Month(9, year2020);
        Month month10_y2020 = new Month(10, year2020);
        Month month11_y2020 = new Month(11, year2020);
        Month month12_y2020 = new Month(12, year2020);

        assertEquals(10, month10_y2021.getMonth());

        assertEquals(31, month1_y2021.getMonthSize());
        assertEquals(28, month2_y2021.getMonthSize());
        assertEquals(31, month3_y2021.getMonthSize());
        assertEquals(30, month4_y2021.getMonthSize());
        assertEquals(31, month5_y2021.getMonthSize());
        assertEquals(30, month6_y2021.getMonthSize());
        assertEquals(31, month7_y2021.getMonthSize());
        assertEquals(31, month8_y2021.getMonthSize());
        assertEquals(30, month9_y2021.getMonthSize());
        assertEquals(31, month10_y2021.getMonthSize());
        assertEquals(30, month11_y2021.getMonthSize());
        assertEquals(31, month12_y2021.getMonthSize());

        assertEquals(31, month1_y2020.getMonthSize());
        assertEquals(29, month2_y2020.getMonthSize());
        assertEquals(31, month3_y2020.getMonthSize());
        assertEquals(30, month4_y2020.getMonthSize());
        assertEquals(31, month5_y2020.getMonthSize());
        assertEquals(30, month6_y2020.getMonthSize());
        assertEquals(31, month7_y2020.getMonthSize());
        assertEquals(31, month8_y2020.getMonthSize());
        assertEquals(30, month9_y2020.getMonthSize());
        assertEquals(31, month10_y2020.getMonthSize());
        assertEquals(30, month11_y2020.getMonthSize());
        assertEquals(31, month12_y2020.getMonthSize());

    }

    /**
     * ***** Month *****
     * 测试月份加一 包括12加一及其正当性
     */
    @Test
    public void monthIncrement() {
        Year year2021 = new Year(2021);
        Month month10_y2021 = new Month(10, year2021);
        Month month12_y2021 = new Month(12, year2021);
        assertTrue(month10_y2021.increment());
        assertEquals(11, month10_y2021.getMonth());
        assertFalse(month12_y2021.increment());
    }

    /**
     * ***** Month *****
     * 测试Equals()
     */
    @Test
    public void testEqualsMonth() {
        int c = 10;
        Year year2021 = new Year(2021);
        Month month10_y2021 = new Month(10, year2021);
        Month month11_y2021 = new Month(11, year2021);
        assertFalse(month10_y2021.equals(month11_y2021));
        assertFalse(month10_y2021.equals(c));
        month10_y2021.increment();
        assertTrue(month10_y2021.equals(month11_y2021));
    }

    /**
     * ***** Year *****
     * 测试初始化为0的异常抛出
     */
    @Test
    public void setYearZero() {
        try{
            Year year0 = new Year(0);
        } catch (IllegalArgumentException e) { assertTrue(e.getMessage().equals("Not a valid year")); }
    }

    /**
     * ***** Year *****
     * 测试getCurrentPos() setCurrentPos()内部函数
     */
    @Test
    public void checkInsideFunc() {
        Year year2021 = new Year(2021);
        assertEquals(2021, year2021.getCurrentPos());
        year2021.setYear(2022);
        assertEquals(2022, year2021.getCurrentPos());
    }

    /**
     * ***** Year *****
     * 测试getYear
     */
    @Test
    public void getYearNormalWithGet() {
        Year year1 = new Year(2021);
        assertEquals(2021, year1.getYear());
    }

    /**
     * ***** Year *****
     * 测试-1年份加一次后的有效性
     */
    @Test
    public void incrementOnMinusOne() {
        Year year3 = new Year(-1);
        year3.increment();
        assertEquals(1, year3.getYear());
        assertTrue(year3.isValid());
    }

    /**
     * ***** Year *****
     * 测试正常初始值的加一
     */
    @Test
    public void yearNormalIncrement() {
        Year year2 = new Year(-20);
        year2.increment();
        assertEquals(-19, year2.getYear());
    }

    /**
     * ***** Year *****
     * 测试闰年 包括正数负数
     */
    @Test
    public void isLeapYear() {
        Year year4 = new Year(4);
        Year year100 = new Year(100);
        Year year400 = new Year(400);
        Year year101 = new Year(101);
        Year year_1 = new Year(-1);
        Year year_3 = new Year(-3);
        Year year_101 = new Year(-101);
        Year year_401 = new Year(-401);
        assertTrue(year4.isLeap());
        assertFalse(year100.isLeap());
        assertTrue(year400.isLeap());
        assertFalse(year101.isLeap());
        assertTrue(year_1.isLeap());
        assertFalse(year_3.isLeap());
        assertFalse(year_101.isLeap());
        assertTrue(year_401.isLeap());
    }

    /**
     * ***** Year *****
     * 测试Equals()
     */
    @Test
    public void testEqualsYear() {
        int c = 1;
        Year year1 = new Year(1);
        Year year2 = new Year(2);
        assertFalse(year1.equals(year2));
        assertFalse(year1.equals(c));
        year1.increment();
        assertTrue(year1.equals(year2));
    }
}