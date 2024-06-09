#pragma once

#include <string>
#include <vector>
#include "expr.hh"

namespace rift
{
    namespace ast
    {
        using string = std::string;
        using ExprStr  = rift::ast::Expr::Expr<string>;
        using VisitStr = rift::ast::Expr::Visitor<string>;
        using namespace rift::ast::Expr;

        class VisitorPrinter;
        
        /// @class Printer
        /// @brief This class is used to print the expression.
        class Printer
        {
            public:
                Printer();
                ~Printer() = default;
                friend class VisitorPrinter;

                /// Prints the given expression string.
                /// @param expr The expression to print.
                /// @return string representation of the expression.
                string print(ExprStr *expr);

                /// @brief  Wraps the given expression in parentheses.
                /// @param name The name of the expression.
                /// @param exprs The expressions to wrap.
                /// @return The wrapped expression.
                string parenthesize(string name, std::vector<ExprStr*> expr);
                
            private:
                VisitorPrinter *visitor;
        };

        /// @class Visitor
        /// @brief This class is used to visit each type of expression
        class VisitorPrinter : public VisitStr
        {
            public:
                VisitorPrinter(Printer &printer);
                ~VisitorPrinter() = default;

                string visit_binary(Binary<string> *expr) const;
                string visit_grouping(Grouping<string> *expr) const;
                string visit_literal(Literal<string> *expr) const;
                string visit_unary(Unary<string> *expr) const;
            
            private:
                Printer *printer;
        };
    }
}