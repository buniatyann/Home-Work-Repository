#include "variables/variable_table.h"
#include <gtest/gtest.h>

using namespace mymake;

TEST(VariableTableTest, SetAndLookup) {
    VariableTable vars;
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    auto val = vars.lookup("CC");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(*val, "gcc");
}

TEST(VariableTableTest, Undefined) {
    VariableTable vars;
    EXPECT_FALSE(vars.lookup("NONEXISTENT").has_value());
    EXPECT_FALSE(vars.is_defined("NONEXISTENT"));
}

TEST(VariableTableTest, Append) {
    VariableTable vars;
    vars.set("CFLAGS", "-Wall", VarFlavor::Recursive, VarOrigin::File);
    vars.append("CFLAGS", "-Werror");
    auto val = vars.lookup("CFLAGS");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(*val, "-Wall -Werror");
}

TEST(VariableTableTest, AppendToUndefined) {
    VariableTable vars;
    vars.append("NEW", "value");
    auto val = vars.lookup("NEW");
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(*val, "value");
}

TEST(VariableTableTest, ConditionalSet) {
    VariableTable vars;
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);
    vars.set_conditional("CC", "clang", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(*vars.lookup("CC"), "gcc"); // not overwritten

    vars.set_conditional("CXX", "g++", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(*vars.lookup("CXX"), "g++"); // was undefined, now set
}

TEST(VariableTableTest, CommandLineOverride) {
    VariableTable vars;
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::CommandLine);
    // File-level set should NOT override command-line
    vars.set("CC", "clang", VarFlavor::Simple, VarOrigin::File);
    EXPECT_EQ(*vars.lookup("CC"), "gcc");
}

TEST(VariableTableTest, Scoping) {
    VariableTable vars;
    vars.set("CC", "gcc", VarFlavor::Simple, VarOrigin::File);

    vars.push_scope();
    vars.set_local("@", "foo.o");
    EXPECT_EQ(*vars.lookup("@"), "foo.o");
    EXPECT_EQ(*vars.lookup("CC"), "gcc"); // global still visible

    vars.pop_scope();
    EXPECT_FALSE(vars.lookup("@").has_value()); // local gone
    EXPECT_EQ(*vars.lookup("CC"), "gcc");
}
