package exper;

import MIDL.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.*;

import java.io.*;

/**
 * @author 梁芮槐 2019302789
 * @brief ASTDeal 调用重载后的MIDLBaseVisitor 按行读取输入文件 输出格式化抽象语法树到对应文件
 */
public class ASTDeal{
    private static final String inputFileName = "./src/main/txt/input.txt";
    private static final String outputFileName = "./src/main/txt/output.txt";
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
        File outputFile = new File(outputFileName);
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(outputFile));

        String line = new String();
        int cnt = 1;
        while((line = bufferedReader.readLine()) != null) {
            System.out.println("Case " + cnt + ": " + line);

            CharStream input = CharStreams.fromString(line);
            MIDLLexer lexer = new MIDLLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            MIDLParser parser = new MIDLParser(tokens);
            ParseTree tree = parser.specification();
            ASTGenerator ag = new ASTGenerator();
            ag.visit(tree);

            System.out.println("Case " + cnt++ + "\'s ASTParseTree: " + ag.astParseTree);
            System.out.println("----------------------------------------");

            bufferedWriter.write(ag.astParseTree + "\n");
            bufferedWriter.flush();
        }
        bufferedReader.close();
        bufferedWriter.close();
    }
}
