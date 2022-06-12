package exper;

import java.util.ArrayList;

/**
 * @author 梁芮槐 2019302789
 * @date 2022-05-31
 * @breif 符号表表项类 底层数据项
 */
public class Token {
    public String type; // 表项数据类型
    public String id;   // 表项对象id
    public ArrayList<String> val = new ArrayList<String>(); // 为表项进行赋值的字面量
    public ArrayList<String> valType = new ArrayList<String>(); // 每个字面量的类型

    public Token(String t, String i, ArrayList<String> v, ArrayList<String> vt) {
        type = t;
        id = i;
        val = v;
        valType = vt;
    }
}
