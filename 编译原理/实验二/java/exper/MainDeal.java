package exper;

import MIDL.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.*;

import java.io.*;

/**
 * @author 梁芮槐 2019302789
 * @brief MainDeal 调用重载后的MIDLBaseVisitor 按行读取输入文件 输出格式化抽象语法树到对应文件 同时输出语义分析的结果
 */
public class MainDeal {
    private static final String inputFileName = "./src/main/txt/input.txt";
    private static final String astOutputFileName = "./src/main/txt/astOutput.txt";
    private static final String hxxOutputFileDir = "./src/main/txt/";
    private static final String logOutputFileName = "./src/main/txt/logOutput.txt";

    /**
     * 对单次输入进行词法、语法、语义分析
     *
     * @param seq 当前用例编号
     * @param input 输入内容
     * @param isHXX 是否导出hxx文件
     * @param astBufferWriter 用于存格式化抽象语法树的文件
     * @param logBufferWriter 用于存储log信息的文件
     * @throws IOException
     */
    public static void run(int seq, String input, boolean isHXX, BufferedWriter astBufferWriter, BufferedWriter logBufferWriter) throws IOException {
        String curLog = new String();
        curLog += "Case " + seq + ": \n" + input + "\n";
        System.out.println("Case " + seq + ": \n" + input);

        CharStream charStream = CharStreams.fromString(input);
        MIDLLexer lexer = new MIDLLexer(charStream);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        MIDLParser parser = new MIDLParser(tokens);
        ParseTree tree = parser.specification();
        ASTGenerator ag = new ASTGenerator();
        ag.visit(tree);

        curLog += "Case " + seq + "\'s ASTParseTree: " + ag.astParseTree + "\n";
        System.out.println("Case " + seq + "\'s ASTParseTree: " + ag.astParseTree);
        curLog += ag.exceptionSum + "\n";
        System.out.println(ag.exceptionSum);
        if(isHXX) {
            TokenTable2HXX tokenTable2HXX = new TokenTable2HXX(ag.getTokenTable());
            tokenTable2HXX.process("IDL_" + seq);

            File hxxFile = new File(hxxOutputFileDir + "HXX_" + seq + ".hxx");
            BufferedWriter hxxWriter = new BufferedWriter(new FileWriter(hxxFile));
            hxxWriter.write(tokenTable2HXX.getFinalHXX());
            hxxWriter.flush();
            hxxWriter.close();

            curLog += "The .hxx file has been written to " + hxxOutputFileDir + "HXX_" + seq + ".hxx\n";
            System.out.println("The .hxx file has been written to " + hxxOutputFileDir + "HXX_" + seq + ".hxx");
        }
        curLog += "----------------------------------------\n";
        System.out.println("----------------------------------------");

        astBufferWriter.write(ag.astParseTree + "\n");
        astBufferWriter.flush();
        logBufferWriter.write(curLog);
        logBufferWriter.flush();
    }

    public static void main(String[] args) throws Exception {
        File inputFile = new File(inputFileName);
        if(inputFile.exists() && inputFile.isFile()) {
            System.out.println("Workplace: " + System.getProperties().getProperty("user.dir"));
            System.out.println("Successfully read " + inputFileName + "\n");
        }
        else {
            System.out.println("Invalid input file!");
            return;
        }
        BufferedReader bufferedReader = new BufferedReader(new FileReader(inputFile));
        File astOutputFile = new File(astOutputFileName);
        BufferedWriter astBW = new BufferedWriter(new FileWriter(astOutputFile));
        File logOutputFile = new File(logOutputFileName);
        BufferedWriter logBW = new BufferedWriter(new FileWriter(logOutputFile));

        String line = new String();
        String totalInput = new String();
        int cnt = 1, initSign = 0;
        boolean hxxSign = false;
        // 井字符分隔 后续输入无HXX转化
        // 美元符分隔 后续输入要加入HXX转化
        while((line = bufferedReader.readLine()) != null) {
            if(line.equals("")) continue;
            if(line.charAt(0) == '#') {
                if(initSign != 1) {
                    initSign = 1;
                } else {
                    run(cnt++, totalInput, hxxSign, astBW, logBW);
                    totalInput = "";
                }
                hxxSign = false;
            } else if (line.charAt(0) == '$'){
                if(initSign != 1) {
                    initSign = 1;
                } else {
                    run(cnt++, totalInput, hxxSign, astBW, logBW);
                    totalInput = "";
                }
                hxxSign = true;
            } else {
                totalInput += line + "\n";
                continue;
            }
        }

        bufferedReader.close();
        astBW.close();
        logBW.close();
    }
}
