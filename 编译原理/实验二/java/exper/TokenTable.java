package exper;

import org.omg.CORBA.PRIVATE_MEMBER;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

/**
 * @author 梁芮槐 2019302789
 * @date 2022-05-31
 * @breif 符号表管理类，进行符号表数据结构管理，负责新表项的插入与存储和异常检测
 */
public class TokenTable {
    private ArrayList<String> integers = new ArrayList<String>(
            Arrays.asList("short", "int16", "long", "int32", "long long", "int64", "int8",
                    "unsigned short", "uint16", "unsigned long", "uint32", "unsigned long long", "uint64", "uint8"));
    private ArrayList<String> floatings = new ArrayList<String>(
            Arrays.asList("float", "double", "long double"));
    private ArrayList<String> special = new ArrayList<String>(
            Arrays.asList("char", "string", "boolean"));

    private Validator validator = new Validator();

    // String为module的ID 可以是ID::ID形式 Integer为该module包含的struct哈希表在structTable中的index
    private HashMap<String, Integer> moduleTable = new HashMap<String, Integer>();
    private int moduleCnt = 1;

    // String为struct的ID Integer为该struct包含的value哈希表在valueTable中的index
    private ArrayList<HashMap<String, Integer>> structTable = new ArrayList<HashMap<String, Integer>>();
    private int structCnt = 0;

    // String为value的ID Token为其基本信息
    private ArrayList<HashMap<String, Token>> valueTable = new ArrayList<HashMap<String, Token>>();

    // 内部判断三种插入模式
    // 1. 输入struct和token全为空时，是使用module，即INSERT_MODEL.MODULE
    // 2. 只有输入token为空时，是struct定义，即INSERT_MODEL.STRUCT_DEFINE
    // 3. 全都不为空时，是插入struct下的对象，即INSERT_MODEL.VAL
    private enum INSERT_MODEL{MODULE, STRUCT_DEFINE, VAL};
    private INSERT_MODEL currentModel;

    private String globalSpace = "#global";
    private String currentModule = new String();
    private String currentStruct = new String();
    private Token currentToken;
    private ArrayList<String> currentStructTokenVal = new ArrayList<String>();   // 用于存储struct嵌套调用的信息 便于导出hxx
    private ArrayList<String> currentStructTokenValId = new ArrayList<String>(); // 用于存储struct嵌套调用的信息 便于导出hxx

    private String exceptionSummary = new String();
    private String curLineNum = new String();
    private String declConflictException = new String();
    private String undefinedException = new String();
    private String valTypeException = new String();

    boolean m_debug = false;

    /**
     * @brief 初始化函数
     * 将全局名称空间加入moduleTable中，并为其在structTable中分配位置，防止全局空间struct插入时因找不到module而出错
     */
    public TokenTable(){
        moduleTable.put(globalSpace, 0);
        structTable.add(new HashMap<String, Integer>());
    }

    /**
     * @brief 检查声明是否冲突
     * 1. 不能有同名module
     * 2. 同一module中不能有同名struct定义
     * 3. 同一struct中不能有同名对象
     *
     * @return 若检查通过，返回true，否则返回false，报错信息存储在declConflictException
     */
    private boolean checkDeclConflict() {
        boolean res = true;

        // 不能出现同名module
        if(currentModel == INSERT_MODEL.MODULE) {
            if(moduleTable.containsKey(currentModule)) {
                declConflictException += "Exception: module \'" + currentModule + "\' reused.\n";
                res = false;
            }
        }

        // 同一module中不能有多个同名struct定义
        if(currentModel == INSERT_MODEL.STRUCT_DEFINE) {
            if(structTable.get(moduleTable.get(currentModule)).containsKey(currentStruct)) {
                declConflictException += "Exception: struct \'" + currentStruct + "\' redefined.\n";
                res = false;
            }
        }

        // 同一struct中不能有多个同名普通对象声明 也不能有多个同名struct对象声明
        if(currentModel == INSERT_MODEL.VAL) {
            if(valueTable.get(structTable.get(moduleTable.get(currentModule)).get(currentStruct)).containsKey(currentToken.id)) {
                declConflictException += "Exception: object \'" + currentToken.id + "\' redeclared.\n";
                res = false;
            }
        }

        return res;
    }

    /**
     * @brief 检查对未定义struct类型进行对象声明
     *
     * @return 若检查通过，返回true，否则返回false，报错信息存储在undefinedException
     */
    private boolean checkUndefined() {
        boolean res = true;

        if(currentModel == INSERT_MODEL.VAL) {
            if(!integers.contains(currentToken.type) && !floatings.contains(currentToken.type) && !special.contains(currentToken.type)) {
                if(currentToken.type.contains("::")) {
                    ArrayList<String> ss = new ArrayList<String>(Arrays.asList(currentToken.type.split("::")));
                    if(ss.get(0).equals("")) ss.remove(0);
                    if(ss.size() == 1) {
                        if(!structTable.get(moduleTable.get(globalSpace)).containsKey(ss.get(0))) {
                            res = false;
                        }
                    } else {
                        String nameSpace = new String();
                        String typeSpace = currentToken.type;
                        if(typeSpace.charAt(0) == ':') typeSpace = typeSpace.substring(2);
                        if(!structTable.get(moduleTable.get(globalSpace)).containsKey(typeSpace)) {
                            for (int i = 0; i < ss.size() - 1; i++) {
                                if (!nameSpace.equals("")) nameSpace += "::" + ss.get(i);
                                else nameSpace += ss.get(i);
                                typeSpace = typeSpace.substring(ss.get(i).length() + 2);
                                if(moduleTable.containsKey(nameSpace) && structTable.get(moduleTable.get(nameSpace)).containsKey(typeSpace)) {
                                    res = true;
                                    for(Token t:valueTable.get(structTable.get(moduleTable.get(nameSpace)).get(typeSpace)).values()) {
                                        if(t.val.size() > 0) currentStructTokenVal.add(t.val.get(0));
                                        if(t.valType.size() > 0) currentStructTokenValId.add(t.id);
                                    }
                                    break;
                                } else res = false;
                            }
                        }
                    }
                } else if(!structTable.get(moduleTable.get(globalSpace)).containsKey(currentToken.type)
                        && !structTable.get(moduleTable.get(currentModule)).containsKey(currentToken.type)) {
                    res = false;
                } else if(structTable.get(moduleTable.get(globalSpace)).containsKey(currentToken.type)) {
                    for(Token t:valueTable.get(structTable.get(moduleTable.get(globalSpace)).get(currentToken.type)).values()) {
                        if(t.val.size() > 0) currentStructTokenVal.add(t.val.get(0));
                        if(t.valType.size() > 0) currentStructTokenValId.add(t.id);
                    }
                } else if(structTable.get(moduleTable.get(currentModule)).containsKey(currentToken.type)) {
                    for(Token t:valueTable.get(structTable.get(moduleTable.get(currentModule)).get(currentToken.type)).values()) {
                        if(t.val.size() > 0) currentStructTokenVal.add(t.val.get(0));
                        if(t.valType.size() > 0) currentStructTokenValId.add(t.id);
                    }
                }
                if(!res) undefinedException += "Exception: undefined spec_type " + currentToken.type + " used by object " + currentToken.id + ".\n";
            }
        }

        return res;
    }

    /**
     * @brief 检查声明时赋给对象的值的类型是否合法
     * 1. 普通变量只能赋值当前类型的值
     * 2. 整形和浮点型普通变量要进行溢出检测
     * 3. 任何对象的数组的声明长度必须为整形，且不能超出short的范围
     * 4. 鉴于文法未规定，此处struct变量不允许进行赋值操作
     *
     * @return 若检查通过，返回true，否则返回false，报错信息存储在valTypeException
     */
    private boolean checkValType() {
        boolean res = true;

        String arrayObject = "";
        if(currentModel == INSERT_MODEL.VAL) {
            if(currentToken.val.size() > 0 && currentToken.valType.get(0).startsWith("array_index#")) arrayObject = "array ";
            if(integers.contains(currentToken.type)) {
                for(int i = 0; i < currentToken.valType.size(); i++) {
                    if(!currentToken.valType.get(i).equals("integer")) {
                        if(currentToken.valType.get(i).startsWith("array_index#")) {
                            String realType = currentToken.valType.get(i).substring(12);
                            if (!realType.equals("integer")) {
                                valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with " + realType + " value \'" + currentToken.val.get(i) + "\'.\n";
                                res = false;
                            } else if(!validator.validate(currentToken.val.get(i), "short")) {
                                valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                                res = false;
                            }
                            continue;
                        }
                        valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\' was assigned with invalid value " + currentToken.valType.get(i) + " \'" + currentToken.val.get(i) + "\'.\n";
                        res = false;
                    } else if(!validator.validate(currentToken.val.get(i), currentToken.type)) {
                        valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\' was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                        res = false;
                    }
                }
            } else if(floatings.contains(currentToken.type)) {
                for(int i = 0; i < currentToken.valType.size(); i++) {
                    if(!currentToken.valType.get(i).equals("floating_pt")) {
                        if(currentToken.valType.get(i).startsWith("array_index#")) {
                            String realType = currentToken.valType.get(i).substring(12);
                            if (!realType.equals("integer")) {
                                valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with " + realType + " value \'" + currentToken.val.get(i) + "\'.\n";
                                res = false;
                            } else if(!validator.validate(currentToken.val.get(i), "short")) {
                                valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                                res = false;
                            }
                            continue;
                        }
                        valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\' was assigned with invalid value " + currentToken.valType.get(i) + " \'" + currentToken.val.get(i) + "\'.\n";
                        res = false;
                    } else if(!validator.validate(currentToken.val.get(i), currentToken.type)) {
                        valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\' was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                        res = false;
                    }
                }
            } else if(special.contains(currentToken.type)) {
                if(currentToken.type.equals("char")) {
                    for(int i = 0; i < currentToken.valType.size(); i++) {
                        if(!currentToken.valType.get(i).equals("char")) {
                            if(currentToken.valType.get(i).startsWith("array_index#")) {
                                String realType = currentToken.valType.get(i).substring(12);
                                if (!realType.equals("integer")) {
                                    valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with " + realType + " value \'" + currentToken.val.get(i) + "\'.\n";
                                    res = false;
                                } else if(!validator.validate(currentToken.val.get(i), "short")) {
                                    valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                                    res = false;
                                }
                                continue;
                            }
                            valTypeException += "Exception: " + arrayObject + " char object \'" + currentToken.id + "\'" + " was assigned with invalid value " + currentToken.valType.get(i) + " \'" + currentToken.val.get(i) + "\'.\n";
                            res = false;
                        }
                    }
                } else if(currentToken.type.equals("string")) {
                    for(int i = 0; i < currentToken.valType.size(); i++) {
                        if(!currentToken.valType.get(i).equals("string")) {
                            if(currentToken.valType.get(i).startsWith("array_index#")) {
                                String realType = currentToken.valType.get(i).substring(12);
                                if (!realType.equals("integer")) {
                                    valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with " + realType + " value \'" + currentToken.val.get(i) + "\'.\n";
                                    res = false;
                                } else if(!validator.validate(currentToken.val.get(i), "short")) {
                                    valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                                    res = false;
                                }
                                continue;
                            }
                            valTypeException += "Exception: " + arrayObject + " string object \'" + currentToken.id + "\'" + " was assigned with invalid value " + currentToken.valType.get(i) + " \'" + currentToken.val.get(i) + "\'.\n";
                            res = false;
                        }
                    }
                } else if(currentToken.type.equals("boolean")) {
                    for(int i = 0; i < currentToken.valType.size(); i++) {
                        if(!currentToken.valType.get(i).equals("boolean")) {
                            if(currentToken.valType.get(i).startsWith("array_index#")) {
                                String realType = currentToken.valType.get(i).substring(12);
                                if (!realType.equals("integer")) {
                                    valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with " + realType + " value \'" + currentToken.val.get(i) + "\'.\n";
                                    res = false;
                                } else if(!validator.validate(currentToken.val.get(i), "short")) {
                                    valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with overflowed value \'" + currentToken.val.get(i) + "\'.\n";
                                    res = false;
                                }
                                continue;
                            }
                            valTypeException += "Exception: " + arrayObject + " boolean object \'" + currentToken.id + "\'" + " was assigned with invalid value " + currentToken.valType.get(i) + " \'" + currentToken.val.get(i) + "\'.\n";
                            res = false;
                        }
                    }
                }
            } else {
                if(!arrayObject.equals("")) {
                    if(currentToken.valType.get(0).startsWith("array_index#")) {
                        String realType = currentToken.valType.get(0).substring(12);
                        if (!realType.equals("integer")) {
                            valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with " + realType + " value \'" + currentToken.val.get(0) + "\'.\n";
                            res = false;
                        } else if(!validator.validate(currentToken.val.get(0), "short")) {
                            valTypeException += "Exception: " + arrayObject + currentToken.type + " object \'" + currentToken.id + "\'s index was assigned with overflowed value \'" + currentToken.val.get(0) + "\'.\n";
                            res = false;
                        }
                    }
                    if(currentToken.valType.size() > 1) {
                        valTypeException += "Exception: spec_type \'" + currentToken.type + "\' object \'" + currentToken.id + "\'" + " was assigned invalid value.\n";
                        res = false;
                    }
                } else if(currentToken.valType.size() > 0) {
                    valTypeException += "Exception: spec_type \'" + currentToken.type + "\' object \'" + currentToken.id + "\'" + " was assigned invalid value.\n";
                    res = false;
                }
            }
        }

        return res;
    }

    /**
     *
     * @param module 插入所在的module
     * @param struct 插入所在的struct
     * @param token 插入所在的对象
     *
     * @return 若插入成功，返回true，否则返回false，全部报错信息存储在exceptionSummary
     */
    public boolean insertToken(String module, String struct, Token token) {
        exceptionSummary = new String();
        declConflictException = new String();
        undefinedException = new String();
        valTypeException = new String();
        currentStructTokenVal.clear();
        currentStructTokenValId.clear();

        if(module.equals("")) currentModule = globalSpace; // 若module为空，根据文法即为全局struct的操作，此时默认module为全局空间
        else currentModule = module;
        currentStruct = struct;
        currentToken = token;
        if(m_debug) {
            System.out.println("Insert: module=" + module + " struct=" + struct + " type=" + currentToken.type + " id=" + currentToken.id);
            for(int i = 0; i < currentToken.val.size(); i++) {
                System.out.println("value[" + i + "]=" + currentToken.val.get(i) + " valueType[" + i + "]=" + currentToken.valType.get(i));
            }
        }

        if(!currentToken.id.equals("")) currentModel = INSERT_MODEL.VAL;
        else if(!currentStruct.equals("")) currentModel = INSERT_MODEL.STRUCT_DEFINE;
        else currentModel = INSERT_MODEL.MODULE;

        boolean checkDeclConflict = checkDeclConflict();
        boolean checkUndefined = checkUndefined();
        boolean checkValType = checkValType();

        if(checkDeclConflict && checkUndefined && checkValType) {
            if(currentModel == INSERT_MODEL.VAL) { // 插入token
                if(m_debug) System.out.println("SInsert: val");
                Token tmp;
                if(!integers.contains(currentToken.type) && !floatings.contains(currentToken.type) && !special.contains(currentToken.type)) {
                    tmp = new Token(currentToken.type, currentToken.id, new ArrayList<String>(currentStructTokenVal), new ArrayList<String>(currentStructTokenValId));
                    if(m_debug) System.out.println("Last insert is struct nest.");
                } else tmp = new Token(currentToken.type, currentToken.id, new ArrayList<String>(currentToken.val), new ArrayList<String>(currentToken.valType));
                valueTable.get(structTable.get(moduleTable.get(currentModule)).get(currentStruct)).put(tmp.id, tmp);
            } else if(currentModel == INSERT_MODEL.MODULE) { // 插入module
                if(m_debug) System.out.println("SInsert: module");
                moduleTable.put(currentModule, moduleCnt++);
                structTable.add(new HashMap<String, Integer>());
            } else { // 插入struct定义
                if(m_debug) System.out.println("SInsert: struct_define");
                structTable.get(moduleTable.get(currentModule)).put(currentStruct, structCnt++);
                valueTable.add(new HashMap<String, Token>());
            }
            return true;
        } else {
            exceptionSummary = curLineNum + declConflictException + undefinedException + valTypeException;
            return false;
        }
    }

    /**
     * @brief 返回moduleTable
     *
     * @return moduleTable
     */
    public HashMap<String, Integer> getModuleTable() {
        return moduleTable;
    }

    /**
     * @brief 获取structTable
     *
     * @return structTable
     */
    public ArrayList<HashMap<String, Integer>> getStructTable() {
        return structTable;
    }

    /**
     * @brief 获取valueTable
     *
     * @return valueTable
     */
    public ArrayList<HashMap<String, Token>> getValueTable() {
        return valueTable;
    }

    /**
     * @breif 获取全部报错信息exceptionSummary
     *
     * @return 返回全部报错信息exceptionSummary
     */
    public String getExceptionSummary() {
        return exceptionSummary;
    }

    /**
     * 设置当前所在行号 便于进行异常输出
     *
     * @param s
     */
    public void setLineNum(String s) {
        curLineNum = s;
    }

    /**
     * @brief 清空整个符号表
     */
    public void clearAll() {
        moduleTable.clear();
        moduleCnt = 0;
        for(int i = 0; i < structTable.size(); i++) {
            structTable.get(i).clear();
        }
        structTable.clear();
        structCnt = 0;
        for(int i = 0; i < valueTable.size(); i++) {
            valueTable.get(i).clear();
        }
        valueTable.clear();

        currentModule = new String();
        currentStruct = new String();
        currentToken = new Token("", "", new ArrayList<String>(), new ArrayList<String>());
        currentStructTokenVal.clear();
        currentStructTokenValId.clear();

        exceptionSummary = new String();
        declConflictException = new String();
        undefinedException = new String();
        valTypeException = new String();
    }

}
