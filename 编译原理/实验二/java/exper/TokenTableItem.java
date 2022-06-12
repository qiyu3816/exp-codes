package exper;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * @brief 符号表中对象所有信息的另一种存储形式 用于存储即将导出hxx文件的符号表信息
 *
 * @author 梁芮槐 2019302789
 *
 * @date 2022-06-01
 */
public class TokenTableItem {
    private ArrayList<String> commonType = new ArrayList<String>(
            Arrays.asList("UnsignedInt8", "UnsignedShort", "UnsignedLong", "UnsignedLongLong",
                    "Int8", "Short", "Long", "LongLong",
                    "Float", "Double", "LongDouble",
                    "Char", "String", "Boolean"));

    public String id;
    public String type;
    public boolean isStruct = false;
    public ArrayList<StructItem> structItems = new ArrayList<StructItem>(); // 针对struct嵌套引用 存储struct内部变量名和属性的数组
    public String capitalType;
    public String val;
    public boolean isString = false;
    public boolean isArray = false;
    public String indexVal;

    /**
     * 默认构造函数
     * @param i id
     * @param t type
     * @param v value
     * @param iv 如果是数组 则代表indexVal
     */
    public TokenTableItem(String i, String t, String v, String iv) {
        id = i;
        type = t;
        if(!commonType.contains(type)) isStruct = true;
        capitalType = type.toUpperCase();
        if(type.equals("String")) isString = true;
        val = v;
        if(!iv.equals("")) {
            isArray = true;
            indexVal = iv;
        }
    }

    /**
     * 添加struct对象名和属性
     * @param i id
     * @param a attribute
     */
    public void addStructItem(String i, String a) {
        structItems.add(new StructItem(i, a));
    }
}

/**
 * @brief 针对struct嵌套引用 存储单个struct内部变量名和属性
 */
class StructItem {
    public String id = new String();
    public String attribute = new String();

    public StructItem(String i, String a) {
        id = i;
        attribute = a;
    }
}