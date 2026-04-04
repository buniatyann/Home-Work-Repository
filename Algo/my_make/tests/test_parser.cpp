#include "parser/lexer.h"
#include "parser/parser.h"
#include <gtest/gtest.h>

using namespace mymake;

class ParserTest : public ::testing::Test {
protected:
    Lexer lexer;
    Parser parser;

    ast::Makefile parse(const std::string& input) {
        auto lines = lexer.lex_string(input);
        return parser.parse(lines);
    }
};

TEST_F(ParserTest, SimpleRule) {
    auto mf = parse("all:\n\techo hello\n");
    ASSERT_EQ(mf.size(), 1);
    auto* rule = std::get_if<ast::Rule>(&mf[0]);
    ASSERT_NE(rule, nullptr);
    ASSERT_EQ(rule->targets.size(), 1);
    EXPECT_EQ(rule->targets[0], "all");
    ASSERT_EQ(rule->recipes.size(), 1);
    EXPECT_EQ(rule->recipes[0], "echo hello");
}

TEST_F(ParserTest, RuleWithPrereqs) {
    auto mf = parse("all: foo bar\n\techo building\n");
    ASSERT_EQ(mf.size(), 1);
    auto* rule = std::get_if<ast::Rule>(&mf[0]);
    ASSERT_NE(rule, nullptr);
    EXPECT_EQ(rule->targets[0], "all");
    ASSERT_EQ(rule->normal_prereqs.size(), 2);
    EXPECT_EQ(rule->normal_prereqs[0], "foo");
    EXPECT_EQ(rule->normal_prereqs[1], "bar");
}

TEST_F(ParserTest, MultipleRules) {
    auto mf = parse("all: foo\n\techo all\n\nfoo:\n\techo foo\n");
    ASSERT_EQ(mf.size(), 2);
    auto* r1 = std::get_if<ast::Rule>(&mf[0]);
    auto* r2 = std::get_if<ast::Rule>(&mf[1]);
    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r1->targets[0], "all");
    EXPECT_EQ(r2->targets[0], "foo");
}

TEST_F(ParserTest, InlineRecipe) {
    auto mf = parse("all: ; echo hello\n");
    ASSERT_EQ(mf.size(), 1);
    auto* rule = std::get_if<ast::Rule>(&mf[0]);
    ASSERT_NE(rule, nullptr);
    ASSERT_EQ(rule->recipes.size(), 1);
    EXPECT_EQ(rule->recipes[0], "echo hello");
}

TEST_F(ParserTest, PatternRule) {
    auto mf = parse("%.o: %.c\n\tgcc -c $< -o $@\n");
    ASSERT_EQ(mf.size(), 1);
    auto* rule = std::get_if<ast::Rule>(&mf[0]);
    ASSERT_NE(rule, nullptr);
    EXPECT_TRUE(rule->is_pattern);
    EXPECT_EQ(rule->targets[0], "%.o");
    EXPECT_EQ(rule->normal_prereqs[0], "%.c");
}

TEST_F(ParserTest, OrderOnlyPrereqs) {
    auto mf = parse("all: foo | bar\n\techo done\n");
    ASSERT_EQ(mf.size(), 1);
    auto* rule = std::get_if<ast::Rule>(&mf[0]);
    ASSERT_NE(rule, nullptr);
    ASSERT_EQ(rule->normal_prereqs.size(), 1);
    EXPECT_EQ(rule->normal_prereqs[0], "foo");
    ASSERT_EQ(rule->order_only_prereqs.size(), 1);
    EXPECT_EQ(rule->order_only_prereqs[0], "bar");
}

TEST_F(ParserTest, VariableAssignmentRecursive) {
    auto mf = parse("CC = gcc\n");
    ASSERT_EQ(mf.size(), 1);
    auto* assign = std::get_if<ast::VariableAssignment>(&mf[0]);
    ASSERT_NE(assign, nullptr);
    EXPECT_EQ(assign->name, "CC");
    EXPECT_EQ(assign->value, "gcc");
    EXPECT_EQ(assign->flavor, ast::VariableAssignment::Recursive);
}

TEST_F(ParserTest, VariableAssignmentSimple) {
    auto mf = parse("CC := gcc\n");
    ASSERT_EQ(mf.size(), 1);
    auto* assign = std::get_if<ast::VariableAssignment>(&mf[0]);
    ASSERT_NE(assign, nullptr);
    EXPECT_EQ(assign->flavor, ast::VariableAssignment::Simple);
}

TEST_F(ParserTest, VariableAssignmentAppend) {
    auto mf = parse("CFLAGS += -Wall\n");
    ASSERT_EQ(mf.size(), 1);
    auto* assign = std::get_if<ast::VariableAssignment>(&mf[0]);
    ASSERT_NE(assign, nullptr);
    EXPECT_EQ(assign->flavor, ast::VariableAssignment::Append);
}

TEST_F(ParserTest, VariableAssignmentConditional) {
    auto mf = parse("CC ?= gcc\n");
    ASSERT_EQ(mf.size(), 1);
    auto* assign = std::get_if<ast::VariableAssignment>(&mf[0]);
    ASSERT_NE(assign, nullptr);
    EXPECT_EQ(assign->flavor, ast::VariableAssignment::Conditional);
}

TEST_F(ParserTest, MultipleRecipes) {
    auto mf = parse("all:\n\techo one\n\techo two\n\techo three\n");
    ASSERT_EQ(mf.size(), 1);
    auto* rule = std::get_if<ast::Rule>(&mf[0]);
    ASSERT_NE(rule, nullptr);
    ASSERT_EQ(rule->recipes.size(), 3);
}
