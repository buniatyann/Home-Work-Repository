#include "eval/expander.h"
#include <gtest/gtest.h>

using namespace mymake;

class ExpanderTest : public ::testing::Test {
protected:
    VariableTable vars;
    Expander expander{vars};
};

TEST_F(ExpanderTest, NoVariables) {
    EXPECT_EQ(expander.expand("hello world"), "hello world");
}

TEST_F(ExpanderTest, DollarDollar) {
    EXPECT_EQ(expander.expand("price is $$5"), "price is $5");
}

TEST_F(ExpanderTest, UndefinedVariable) {
    EXPECT_EQ(expander.expand("$(UNDEFINED)"), "");
}

TEST_F(ExpanderTest, SimpleParenVariable) {
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(expander.expand("$(CC) -c foo.c"), "gcc -c foo.c");
}

TEST_F(ExpanderTest, SimpleBraceVariable) {
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(expander.expand("${CC} -c foo.c"), "gcc -c foo.c");
}

TEST_F(ExpanderTest, SingleCharVariable) {
    vars.push_scope();
    vars.set_local("@", "main.o");
    EXPECT_EQ(expander.expand("output is $@"), "output is main.o");
    vars.pop_scope();
}

TEST_F(ExpanderTest, MultipleVariables) {
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    vars.set("CFLAGS", "-Wall", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(expander.expand("$(CC) $(CFLAGS) -c foo.c"),
              "gcc -Wall -c foo.c");
}

TEST_F(ExpanderTest, AutomaticVariables) {
    vars.push_scope();
    vars.set_local("@", "prog");
    vars.set_local("<", "main.c");
    vars.set_local("^", "main.c util.c");
    EXPECT_EQ(expander.expand("gcc -o $@ $^"), "gcc -o prog main.c util.c");
    vars.pop_scope();
}

TEST_F(ExpanderTest, RecursiveExpansion) {
    // CC = gcc
    // COMPILE = $(CC) -c
    // Should expand COMPILE to "gcc -c"
    vars.set("CC", "gcc", VarFlavor::Recursive, VarOrigin::File);
    vars.set("COMPILE", "$(CC) -c", VarFlavor::Recursive, VarOrigin::File);
    EXPECT_EQ(expander.expand("$(COMPILE) foo.c"), "gcc -c foo.c");
}

TEST_F(ExpanderTest, SimpleNotReExpanded) {
    // CC := gcc
    // Then CC changes, but COMPILE := $(CC) -c was already expanded
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    // Simulate := by expanding at assignment time
    std::string expanded = expander.expand("$(CC) -c");
    vars.set("COMPILE", expanded, VarFlavor::Simple, VarOrigin::File);
    // Now change CC — COMPILE should NOT change
    vars.set("CC", "clang", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(expander.expand("$(COMPILE)"), "gcc -c");
}

TEST_F(ExpanderTest, NestedVariableReference) {
    // name = CC
    // CC = gcc
    // $($(name)) should expand to gcc
    vars.set("name", "CC", VarFlavor::Recursive, VarOrigin::File);
    vars.set("CC", "gcc", VarFlavor::Recursive, VarOrigin::File);
    EXPECT_EQ(expander.expand("$($(name))"), "gcc");
}

TEST_F(ExpanderTest, InfiniteRecursionGuard) {
    // A = $(A) — should not infinite-loop
    vars.set("A", "$(A)", VarFlavor::Recursive, VarOrigin::File);
    EXPECT_EQ(expander.expand("$(A)"), "");
}

TEST_F(ExpanderTest, MutualRecursionGuard) {
    // A = $(B), B = $(A)
    vars.set("A", "$(B)", VarFlavor::Recursive, VarOrigin::File);
    vars.set("B", "$(A)", VarFlavor::Recursive, VarOrigin::File);
    EXPECT_EQ(expander.expand("$(A)"), "");
}

TEST_F(ExpanderTest, EmptyInput) {
    EXPECT_EQ(expander.expand(""), "");
}

TEST_F(ExpanderTest, TrailingDollar) {
    EXPECT_EQ(expander.expand("trailing$"), "trailing$");
}

TEST_F(ExpanderTest, MixedAutoAndUser) {
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    vars.push_scope();
    vars.set_local("@", "main.o");
    vars.set_local("<", "main.c");
    EXPECT_EQ(expander.expand("$(CC) -c $< -o $@"), "gcc -c main.c -o main.o");
    vars.pop_scope();
}
