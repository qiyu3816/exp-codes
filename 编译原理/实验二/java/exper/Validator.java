package exper;

import java.io.IOException;
import java.math.BigDecimal;
import java.math.BigInteger;

/**
 * @brief 用于给定类型字面量范围合法性检查
 */
public class Validator {

    /**
     * 检查int8类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkINT8(String num) {
        int now = Integer.parseInt(num);
        final int INT8_MAX = 127;
        final int INT8_MIN = -128;
        return now >= INT8_MIN && now <= INT8_MAX;
    }

    /**
     * 检查uint8类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkUINT8(String num) {
        int now = Integer.parseInt(num);
        final int UINT8_MAX = 256;
        return now >= 0 && now <= UINT8_MAX;
    }

    /**
     * 检查int16类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkINT16(String num) {
        int now = Integer.parseInt(num);
        final int INT16_MAX = 32767;
        final int INT16_MIN = -32768;
        return now >= INT16_MIN && now <= INT16_MAX;
    }

    /**
     * 检查uint16类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkUINT16(String num) {
        int now = Integer.parseInt(num);
        final int UINT16_MAX = 65535;
        return now >= 0 && now <= UINT16_MAX;
    }

    /**
     * 检查int32类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkINT32(String num) {
        long now = Long.parseLong(num);
        final long INT32_MAX = 2147483647L;
        final long INT32_MIN = -2147483648;
        return now >= INT32_MIN && now <= INT32_MAX;
    }

    /**
     * 检查uint32类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkUINT32(String num) {
        BigInteger now = new BigInteger(num);
        final BigInteger UINT32_MAX = new BigInteger("4294967295");
        return now.compareTo(BigInteger.ZERO) >= 0 && now.compareTo(UINT32_MAX) <= 0;
    }

    /**
     * 检查int64类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkINT64(String num) {
        BigInteger now = new BigInteger(num);
        final BigInteger INT64_MAX = new BigInteger("9223372036854775807");
        final BigInteger INT64_MIN = new BigInteger("-9223372036854775808");
        return now.compareTo(INT64_MIN) >= 0 && now.compareTo(INT64_MAX) <= 0;
    }

    /**
     * 检查uint64类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkUINT64(String num) {
        BigInteger now = new BigInteger(num);
        final BigInteger UINT64_MAX = new BigInteger("18446744073709551615");
        return now.compareTo(BigInteger.ZERO) >= 0 && now.compareTo(UINT64_MAX) <= 0;
    }

    /**
     * 检查float类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkFloat(String num) {
        try {
            Float now = Float.parseFloat(num);
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    /**
     * 检查double类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkDouble(String num) {

        try {
            Double now = Double.parseDouble(num);
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    /**
     * 检查long double类型
     * @param num 输入字面量 字符串形式
     * @return 合法返回true，否则false
     */
    public boolean checkLongDouble(String num) {
        try {
            BigDecimal now = new BigDecimal(num);
        } catch (Exception e) {
            return false;
        }
        BigDecimal now = new BigDecimal(num);
        now = now.abs();
        BigDecimal LONG_DOUBLE_MAX = new BigDecimal("1.79E308");
        return now.compareTo(LONG_DOUBLE_MAX) < 0;
    }

    /**
     * 外部主调函数
     * @param num 输入字面量 字符串形式
     * @param numType 输入字面量类型 字符串形式
     * @return 合法返回true，否则false，若所输类型不在检查范围内，也输出false
     */
    public boolean validate(String num, String numType) {
        if(num.length() > 0 && (num.charAt(num.length() - 1) == 'L' || num.charAt(num.length() - 1) == 'l'
                || num.charAt(num.length() - 1) == 'F' || num.charAt(num.length() - 1) == 'f'
                || num.charAt(num.length() - 1) == 'D' || num.charAt(num.length() - 1) == 'd')) num = num.substring(0, num.length() - 1);
        switch (numType) {
            case "short":
            case "int16":
                return checkINT16(num);
            case "unsigned short":
            case "uint16":
                return checkUINT16(num);
            case "long":
            case "int32":
                return checkINT32(num);
            case "unsigned long":
            case "uint32":
                return checkUINT32(num);
            case "long long":
            case "int64":
                return checkINT64(num);
            case "unsigned long long":
            case "uint64":
                return checkUINT64(num);
            case "int8":
                return checkINT8(num);
            case "uint8":
                return checkUINT8(num);
            case "float":
                return checkFloat(num);
            case "double":
                return checkDouble(num);
            case "long double":
                return checkLongDouble(num);
            default:
                return false;
        }
    }

}


