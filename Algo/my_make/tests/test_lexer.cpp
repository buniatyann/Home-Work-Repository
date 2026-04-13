#include "parser/lexer/lexer.h"
#include <gtest/gtest.h>

using namespace mymake;

TEST(LexerTest, EmptyInput) {
    Lexer lexer;
    auto lines = lexer.lex_string("");
    EXPECT_TRUE(lines.empty());
}

TEST(LexerTest, SimpleRule) {
    Lexer lexer;
    auto lines = lexer.lex_string("all:\n\techo hello\n");
    ASSERT_EQ(lines.size(), 2);
    EXPECT_EQ(lines[0].kind, LogicalLine::RuleOrOther);
    EXPECT_EQ(lines[0].content, "all:");
    EXPECT_EQ(lines[1].kind, LogicalLine::Recipe);
    EXPECT_EQ(lines[1].content, "echo hello");
}

TEST(LexerTest, CommentStripping) {
    Lexer lexer;
    auto lines = lexer.lex_string("# this is a comment\nall: # inline comment\n\techo hello\n");
    ASSERT_EQ(lines.size(), 2);
    EXPECT_EQ(lines[0].content, "all:");
    EXPECT_EQ(lines[1].content, "echo hello");
}

TEST(LexerTest, LineContinuation) {
    Lexer lexer;
    auto lines = lexer.lex_string("all: foo \\\n  bar\n\techo hello\n");
    ASSERT_EQ(lines.size(), 2);
    EXPECT_EQ(lines[0].kind, LogicalLine::RuleOrOther);
    // Continuation joins with a space
    EXPECT_TRUE(lines[0].content.find("foo") != std::string::npos);
    EXPECT_TRUE(lines[0].content.find("bar") != std::string::npos);
}

TEST(LexerTest, Assignment) {
    Lexer lexer;
    auto lines = lexer.lex_string("CC = gcc\n");
    ASSERT_EQ(lines.size(), 1);
    EXPECT_EQ(lines[0].kind, LogicalLine::Assignment);
    EXPECT_EQ(lines[0].content, "CC = gcc");
}

TEST(LexerTest, ImmediateAssignment) {
    Lexer lexer;
    auto lines = lexer.lex_string("CC := gcc\n");
    ASSERT_EQ(lines.size(), 1);
    EXPECT_EQ(lines[0].kind, LogicalLine::Assignment);
}

TEST(LexerTest, MultipleRecipes) {
    Lexer lexer;
    auto lines = lexer.lex_string("all:\n\techo one\n\techo two\n");
    ASSERT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[1].kind, LogicalLine::Recipe);
    EXPECT_EQ(lines[1].content, "echo one");
    EXPECT_EQ(lines[2].kind, LogicalLine::Recipe);
    EXPECT_EQ(lines[2].content, "echo two");
}

TEST(LexerTest, EscapedHash) {
    Lexer lexer;
    auto lines = lexer.lex_string("FOO = hello\\#world\n");
    ASSERT_EQ(lines.size(), 1);
    EXPECT_TRUE(lines[0].content.find("#world") != std::string::npos);
}

TEST(LexerTest, LineNumbers) {
    Lexer lexer;
    auto lines = lexer.lex_string("# comment\n\nall:\n\techo hi\n");
    ASSERT_EQ(lines.size(), 2);
    EXPECT_EQ(lines[0].location.line, 3);
    EXPECT_EQ(lines[1].location.line, 4);
}

TEST(LexerTest, DirectiveDetection) {
    Lexer lexer;
    auto lines = lexer.lex_string("include foo.mk\n");
    ASSERT_EQ(lines.size(), 1);
    EXPECT_EQ(lines[0].kind, LogicalLine::Directive);
}
