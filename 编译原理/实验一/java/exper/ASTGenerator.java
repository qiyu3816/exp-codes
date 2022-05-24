package exper;

import MIDL.MIDLBaseVisitor;
import MIDL.MIDLParser;

/**
 * @author 梁芮槐 2019302789
 * @brief 重载MIDLBaseVisitor 在分析树遍历过程中生成自定义抽象语法树
 */
public class ASTGenerator extends MIDLBaseVisitor<String> {

    int memberIndex = 0;             // member_lists使用member作下级中间变量
    String typeSpec = new String();  // 对于同一member中的多个declarator 暂存type_spec构造格式化
    String astParseTree = new String();
    /**
     * specification -> definition { definition }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitSpecification(MIDLParser.SpecificationContext ctx) {
        astParseTree += ("specification( ");
        for (int i = 0; i < ctx.getChildCount(); i++) {
            visit(ctx.getChild(i));
        }
        astParseTree += (" ) ");
        return null;
    }

    /**
     * definiton -> type_decl“;”| module “;”
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitDefinition(MIDLParser.DefinitionContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /***
     * module -> “module”ID “{” definition { definition } “}”
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitModule(MIDLParser.ModuleContext ctx) {
        astParseTree += ("module$" + ctx.getChild(1) + "( ");
        for(int i = 3; i < ctx.getChildCount() - 1; i++) {
            visit(ctx.getChild(i));
        }
        astParseTree += (" ) ");
        return null;
    }

    /**
     * type_decl -> struct_type | “struct” ID
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitType_decl(MIDLParser.Type_declContext ctx) {
        String child = ctx.getChild(0).getText();
        if(child.equals("struct"))
        {
            astParseTree += ("struct$" + ctx.getChild(1).getText() + "(  ) ");
        } else {
            visit(ctx.getChild(0));
        }
        return null;
    }

    /***
     * struct_type->“struct” ID “{”   member_list “}”
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitStruct_type(MIDLParser.Struct_typeContext ctx) {
        astParseTree += ("struct$" + ctx.getChild(1).getText() + "( ");
        visit(ctx.getChild(3));
        astParseTree += (" ) ");
        return null;
    }

    /**
     * member_list->{ type_spec declarators “;” }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitMember_list(MIDLParser.Member_listContext ctx) {
        int n = ctx.getChildCount();
        for (int i = 0; i < n / 3; i++) {
            astParseTree += ("member$" + memberIndex++ + "( ");
            visit(ctx.getChild(3 * i));
            astParseTree += ("( ");
            visit(ctx.getChild(3 * i + 1));
            astParseTree += (" ) ");
            astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * type_spec -> scoped_name | base_type_spec | struct_type
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitType_spec(MIDLParser.Type_specContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /**
     * scoped_name -> [“::”] ID {“::” ID }
     * ::ab::cd::ef
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitScoped_name(MIDLParser.Scoped_nameContext ctx) {
        typeSpec = "";
        typeSpec += ("scoped_name$");
        int n = ctx.getChildCount();
        for (int i = 0; i < n; i++) {
            typeSpec += (ctx.getChild(i).getText());
        }
        astParseTree += typeSpec;
        return null;
    }

    /**
     * base_type_spec->floating_pt_type|integer_type|“char”|“string”|“boolean”
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitBase_type_spec(MIDLParser.Base_type_specContext ctx) {
        if(ctx.getChild(0).getText().equals("char")
                || ctx.getChild(0).getText().equals("string")
                || ctx.getChild(0).getText().equals("boolean")) {
            typeSpec = "";
            typeSpec += ("base_type_spec$" + ctx.getChild(0).getText());
            astParseTree += typeSpec;
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * floating_pt_type -> “float” | “double” | “long double”
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitFloating_pt_type(MIDLParser.Floating_pt_typeContext ctx) {
        typeSpec = "";
        typeSpec += ("floating_pt_type$" + ctx.getChild(0).getText().replaceAll("\\s*", ""));
        astParseTree += typeSpec;
        return null;
    }

    /**
     * integer_type -> signed_int | unsigned_int
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitInteger_type(MIDLParser.Integer_typeContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /**
     * signed_int->(“short”|“int16”)
     * |(“long”|“int32”)
     * |(“long long”|“int64”)
     * |“int8”
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitSigned_int(MIDLParser.Signed_intContext ctx) {
        typeSpec = "";
        typeSpec += ("signed_int$" + ctx.getChild(0).getText().replaceAll("\\s*", ""));
        astParseTree += typeSpec;
        return null;
    }

    /**
     * unsigned_int -> (“unsigned short”| “uint16”)
     *    | (“unsigned long”| “uint32”)
     *    | (“unsigned long long” | “uint64”)
     *    | “uint8”
     * @breif AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitUnsigned_int(MIDLParser.Unsigned_intContext ctx) {
        typeSpec = "";
        typeSpec += ("unsigned_int$" + ctx.getChild(0).getText().replaceAll("\\s*", ""));
        astParseTree += typeSpec;
        return null;
    }

    /**
     * declarators -> declarator {“,” declarator }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitDeclarators(MIDLParser.DeclaratorsContext ctx) {
        for(int i = 0; i < ctx.getChildCount(); i++) {
            if(i > 0 && !ctx.getChild(i).getText().equals(",")) {
                astParseTree += " ) " + typeSpec + "( ";
                visit(ctx.getChild(i));
            } else visit(ctx.getChild(i));
        }
        return null;
    }

    /**
     * declarator -> simple_declarator | array_declarator
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitDeclarator(MIDLParser.DeclaratorContext ctx) {
        visit(ctx.getChild(0));
        return null;
    }

    /**
     * simple_declarator -> ID [“=” or_expr]
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitSimple_declarator(MIDLParser.Simple_declaratorContext ctx) {
        if(ctx.getChildCount() > 1) {
            astParseTree += ("assign( " + ctx.getChild(0).getText() + " ");
            visit(ctx.getChild(2));
            astParseTree += (" ) ");
        } else {
            astParseTree += (ctx.getChild(0).getText());
        }
        return null;
    }

    /**
     * array_declarator -> ID “[” or_expr “]” [“=” exp_list ]
     *
     * @param ctx
     * @return
     */
    @Override
    public String visitArray_declarator(MIDLParser.Array_declaratorContext ctx) {
        astParseTree += ("array_declarator$" + ctx.getChild(0).getText() + "( ");
        visit(ctx.getChild(2));
        if(4 < ctx.getChildCount()) {
            astParseTree += ("assignArray( ");
            visit(ctx.getChild(5));
            astParseTree += (" ) ");
        }
        astParseTree += (" ) ");
        return null;
    }

    /**
     * exp_list -> “[” or_expr { “,”or_expr } “]”
     *
     * @param ctx
     * @return
     */
    @Override
    public String visitExp_list(MIDLParser.Exp_listContext ctx) {
        int n = ctx.getChildCount();
        for(int i = 1; i < n - 1; i += 2) {
            if(!ctx.getChild(i).getText().equals(",")) {
                visit(ctx.getChild(i));
            }
        }
        return null;
    }

    /**
     * or_expr -> xor_expr {“|” xor_expr }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitOr_expr(MIDLParser.Or_exprContext ctx) {
        int n = ctx.getChildCount();
        if(n == 1) {
            visit(ctx.getChild(0));
        } else {
            int leftCount = 1;
            for (int i = 1; i + 1 < ctx.getChildCount(); i += 2) {
                astParseTree += (ctx.getChild(i).getText() + "( ");
                visit(ctx.getChild(i - 1));
                astParseTree += (" ");

                if(i == ctx.getChildCount() - 2) {
                    visit(ctx.getChild(i + 1));
                } else {
                    leftCount++;
                }
            }
            while(leftCount-- != 0) astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * xor_expr -> and_expr {“^” and_expr }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitXor_expr(MIDLParser.Xor_exprContext ctx) {
        int n = ctx.getChildCount();
        if(n == 1) {
            visit(ctx.getChild(0));
        } else {
            int leftCount = 1;
            for (int i = 1; i + 1 < ctx.getChildCount(); i += 2) {
                astParseTree += (ctx.getChild(i).getText() + "( ");
                visit(ctx.getChild(i - 1));
                astParseTree += (" ");

                if(i == ctx.getChildCount() - 2) {
                    visit(ctx.getChild(i + 1));
                } else {
                    leftCount++;
                }
            }
            while(leftCount-- != 0) astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * and_expr -> shift_expr {“&”shift_expr }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitAnd_expr(MIDLParser.And_exprContext ctx) {
        int n = ctx.getChildCount();
        if(n == 1) {
            visit(ctx.getChild(0));
        } else {
            int leftCount = 1;
            for (int i = 1; i + 1 < ctx.getChildCount(); i += 2) {
                astParseTree += (ctx.getChild(i).getText() + "( ");
                visit(ctx.getChild(i - 1));
                astParseTree += (" ");

                if(i == ctx.getChildCount() - 2) {
                    visit(ctx.getChild(i + 1));
                } else {
                    leftCount++;
                }
            }
            while(leftCount-- != 0) astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * shift_expr -> add_expr { (“>>” | “<<”) add_expr }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitShift_expr(MIDLParser.Shift_exprContext ctx) {
        int n = ctx.getChildCount();
        if(n == 1) {
            visit(ctx.getChild(0));
        } else {
            int leftCount = 1;
            for (int i = 1; i + 1 < ctx.getChildCount(); i += 2) {
                astParseTree += (ctx.getChild(i).getText() + "( ");
                visit(ctx.getChild(i - 1));
                astParseTree += (" ");

                if(i == ctx.getChildCount() - 2) {
                    visit(ctx.getChild(i + 1));
                } else {
                    leftCount++;
                }
            }
            while(leftCount-- != 0) astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * add_expr -> mult_expr { ("+"|"-") mult_expr }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitAdd_expr(MIDLParser.Add_exprContext ctx) {
        int n = ctx.getChildCount();
        if(n == 1) {
            visit(ctx.getChild(0));
        } else {
            int leftCount = 1;
            for (int i = 1; i + 1 < ctx.getChildCount(); i += 2) {
                astParseTree += (ctx.getChild(i).getText() + "( ");
                visit(ctx.getChild(i - 1));
                astParseTree += (" ");

                if(i == ctx.getChildCount() - 2) {
                    visit(ctx.getChild(i + 1));
                } else {
                    leftCount++;
                }
            }
            while(leftCount-- != 0) astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * mult_expr -> unary_expr { (“*” |“/”|“%”) unary_expr }
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitMult_expr(MIDLParser.Mult_exprContext ctx) {
        int n = ctx.getChildCount();
        if(n == 1) {
            visit(ctx.getChild(0));
        } else {
            int leftCount = 1;
            for (int i = 1; i + 1 < ctx.getChildCount(); i += 2) {
                astParseTree += (ctx.getChild(i).getText() + "( ");
                visit(ctx.getChild(i - 1));
                astParseTree += (" ");

                if(i == ctx.getChildCount() - 2) {
                    visit(ctx.getChild(i + 1));
                } else {
                    leftCount++;
                }
            }
            while(leftCount-- != 0) astParseTree += (" ) ");
        }
        return null;
    }

    /**
     * unary_expr -> [“-”| “+” | “~”] literal
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitUnary_expr(MIDLParser.Unary_exprContext ctx) {
        if(ctx.getChildCount() == 2)
        {
            astParseTree += (ctx.getChild(0).getText() + "( ");
            visit(ctx.getChild(1));
            astParseTree += (" ) ");
            return null;
        } else visit(ctx.getChild(0));
        return null;
    }

    /**
     * literal -> INTEGER | FLOATING_PT | CHAR | STRING | BOOLEAN
     * @brief AST trans
     * @param ctx
     * @return
     */
    @Override
    public String visitLiteral(MIDLParser.LiteralContext ctx) {
        astParseTree += ("literal$" + ctx.getChild(0).getText() + " ");
        return null;
    }
}
