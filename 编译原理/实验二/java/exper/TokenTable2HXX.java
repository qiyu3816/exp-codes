package exper;

import org.stringtemplate.v4.ST;
import org.stringtemplate.v4.STGroup;
import org.stringtemplate.v4.STGroupFile;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * @brief 用于从现有符号表导出hxx文件
 *
 * @author 梁芮槐 2019302789
 *
 * @date 2022-06-01
 */
public class TokenTable2HXX {

    private String finalHXX = new String();
    private ArrayList<TokenTableItem> curTokenItemArray = new ArrayList<TokenTableItem>();
    private HashMap<String, String> typeMap = new HashMap<String, String>();

    private String currentSrcFileName = new String();
    STGroup stGroup;
    private ST header;
    private ST struct;
    private ST footer;
    private String footerStr = new String();

    private TokenTable tokenTable;
    private HashMap<String, Integer> moduleTable = new HashMap<String, Integer>();
    private ArrayList<HashMap<String, Integer>> structTable = new ArrayList<HashMap<String, Integer>>();
    private ArrayList<HashMap<String, Token>> valueTable = new ArrayList<HashMap<String, Token>>();

    boolean m_debug = false;

    /**
     * @brief 初始化函数 准备好用于转化hxx的类型映射和StringTemplate
     *
     * @param tt 传入现有符号表
     */
    public TokenTable2HXX(TokenTable tt) {
        typeMap.put("uint8", "UnsignedInt8");
        typeMap.put("unsigned int8", "UnsignedInt8");
        typeMap.put("uint16", "UnsignedShort");
        typeMap.put("unsigned short", "UnsignedShort");
        typeMap.put("uint32", "UnsignedLong");
        typeMap.put("unsigned long", "UnsignedLong");
        typeMap.put("uint64", "UnsignedLongLong");
        typeMap.put("unsigned long long", "UnsignedLongLong");
        typeMap.put("int8", "Int8");
        typeMap.put("int16", "Short");
        typeMap.put("short", "Short");
        typeMap.put("int32", "Long");
        typeMap.put("long", "Long");
        typeMap.put("int64", "LongLong");
        typeMap.put("long long", "LongLong");
        typeMap.put("float", "Float");
        typeMap.put("double", "Double");
        typeMap.put("long double", "LongDouble");
        typeMap.put("char", "Char");
        typeMap.put("string", "String");
        typeMap.put("boolean", "Boolean");

        tokenTable = tt;
        moduleTable = tokenTable.getModuleTable();
        structTable = tokenTable.getStructTable();
        valueTable = tokenTable.getValueTable();

        stGroup = new STGroupFile("D:\\Projects\\IdeaProjects\\CompileExp\\src\\main\\resources\\STG\\template.stg");
        header = stGroup.getInstanceOf("headerTemplate");
        struct = stGroup.getInstanceOf("structTemplate");
        footer = stGroup.getInstanceOf("footerTemplate");
    }

    /**
     * @brief 外部主调函数
     *
     * @param imaginarySrcFileName 当前输入的idl文件的名称 hxx文件中使用
     */
    public void process(String imaginarySrcFileName) {
        currentSrcFileName = imaginarySrcFileName;
        header.add("src_file_name", currentSrcFileName);
        finalHXX += header.render();
        footer.add("src_file_name", currentSrcFileName);
        footerStr = footer.render();
        for (Map.Entry<String, Integer> entry1 : moduleTable.entrySet()) {
            int structIndex = entry1.getValue();
            String curModule = entry1.getKey();
            curModule = curModule.replaceAll("::", "_");
            if(curModule.charAt(0) == '#') curModule = "";
            for(Map.Entry<String, Integer> entry2 : structTable.get(structIndex).entrySet()) {
                boolean nestStruct = false;
                int valIndex = entry2.getValue();
                String curStruct = entry2.getKey();

                header = stGroup.getInstanceOf("headerTemplate");
                struct = stGroup.getInstanceOf("structTemplate");
                footer = stGroup.getInstanceOf("footerTemplate");
                if(valueTable.get(valIndex).size() > 0) {
                    for(Token t : valueTable.get(valIndex).values()) {
                        boolean isArray = false;
                        if(t.valType.size() > 0 && t.valType.get(0).startsWith("array_index")) isArray = true;
                        if(typeMap.containsKey(t.type)) t.type = typeMap.get(t.type);
                        else t.type = curModule + "_" + t.type;
                        t.type = t.type.replaceAll("__", "_");
                        String finalVal = new String();
                        if(t.val.size() > 0) finalVal = t.val.get(0);
                        if(isArray) {
                            finalVal = "{";
                            for(int i = 1; i < t.val.size(); i++) {
                                finalVal += t.val.get(i);
                                if(i != t.val.size() - 1) finalVal += ",";
                            }
                            finalVal += "}";
                        }
                        if(isArray) curTokenItemArray.add(new TokenTableItem(t.id, t.type, finalVal, t.val.get(0)));
                        else {
                            TokenTableItem tmp = new TokenTableItem(t.id, t.type, finalVal, "");
                            if(tmp.isStruct) {
                                nestStruct = true;
                                for(int i = 0; i < t.val.size(); i++) {
                                    tmp.addStructItem(t.valType.get(i), t.val.get(i));
                                }
                            }
                            curTokenItemArray.add(tmp);
                        }
                    }

                    if(!curModule.equals("") && curModule.charAt(curModule.length() - 1) != '_') curModule += "_";
                    curModule = curModule.replaceAll("__", "_");
                    struct.add("moduleSpace", curModule);
                    curStruct = curStruct.replaceAll("::", "_");
                    curStruct = curStruct.replaceAll("__", "_");
                    if(curStruct.length() > 0 && curStruct.charAt(0) == '_') curStruct = curStruct.substring(1);
                    struct.add("structID", curStruct);
                    struct.add("tokenItemArray", curTokenItemArray);
                    struct.add("nestStruct", nestStruct);

                    if(m_debug) {
                        System.out.println("Before render: ");
                        System.out.println("module=" + curModule + " struct=" + curStruct);
                        if (nestStruct) System.out.println("nestStruct true");
                        else System.out.println("nestStruct false");
                        for (TokenTableItem ti : curTokenItemArray) {
                            System.out.println("ti type=" + ti.type + " id=" + ti.id + " value=" + ti.val);
                            if (ti.isArray) System.out.println("isArray index=" + ti.indexVal);
                            if (ti.isStruct) {
                                System.out.println("isStruct ");
                                for (int i = 0; i < ti.structItems.size(); i++) {
                                    System.out.println("struct attribute id=" + ti.structItems.get(i).id + " attribute=" + ti.structItems.get(i).attribute);
                                }
                            }
                        }
                        System.out.println("GO RENDER");
                    }

                    finalHXX += struct.render();
                    curTokenItemArray.clear();
                } else {
                    struct.add("moduleSpace", curModule);
                    struct.add("structID", curStruct);
                    struct.add("tokenItemArray", curTokenItemArray);
                    finalHXX += struct.render();
                }
            }
        }
        finalHXX += footerStr;
    }

    /**
     * @brief 获取已经转换完成的hxx文件内容
     *
     * @return finalHXX
     */
    public String getFinalHXX() {
        return finalHXX;
    }
}


