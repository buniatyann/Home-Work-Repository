#include "engine/graph/graph.h"
#include "core/errors/errors.h"
#include "engine/rule_database/rule_database.h"
#include <gtest/gtest.h>

using namespace mymake;

TEST(GraphTest, SingleTarget) {
    RuleDatabase rules;
    ExplicitRule r;
    r.target = "all";
    r.recipes = {"echo hello"};
    rules.add_explicit_rule(std::move(r));

    DependencyGraph graph;
    graph.build({"all"}, rules);

    auto order = graph.topological_order();
    ASSERT_EQ(order.size(), 1);
    EXPECT_EQ(order[0], "all");
}

TEST(GraphTest, LinearDependency) {
    RuleDatabase rules;

    ExplicitRule r1;
    r1.target = "all";
    r1.normal_prereqs = {"foo"};
    r1.recipes = {"echo all"};
    rules.add_explicit_rule(std::move(r1));

    ExplicitRule r2;
    r2.target = "foo";
    r2.recipes = {"echo foo"};
    rules.add_explicit_rule(std::move(r2));

    DependencyGraph graph;
    graph.build({"all"}, rules);

    auto order = graph.topological_order();
    ASSERT_EQ(order.size(), 2);

    // foo must come before all
    size_t foo_pos = 0, all_pos = 0;
    for (size_t i = 0; i < order.size(); ++i) {
        if (order[i] == "foo") foo_pos = i;
        if (order[i] == "all") all_pos = i;
    }
    EXPECT_LT(foo_pos, all_pos);
}

TEST(GraphTest, CycleDetection) {
    RuleDatabase rules;

    ExplicitRule r1;
    r1.target = "a";
    r1.normal_prereqs = {"b"};
    rules.add_explicit_rule(std::move(r1));

    ExplicitRule r2;
    r2.target = "b";
    r2.normal_prereqs = {"a"};
    rules.add_explicit_rule(std::move(r2));

    DependencyGraph graph;
    graph.build({"a"}, rules);

    EXPECT_THROW(graph.topological_order(), CycleError);
}

TEST(GraphTest, PatternRuleMatching) {
    RuleDatabase rules;

    PatternRule pr;
    pr.target_pattern = "%.o";
    pr.prereq_patterns = {"%.c"};
    pr.recipes = {"gcc -c $< -o $@"};
    rules.add_pattern_rule(std::move(pr));

    ExplicitRule r;
    r.target = "all";
    r.normal_prereqs = {"main.o"};
    r.recipes = {"gcc main.o -o all"};
    rules.add_explicit_rule(std::move(r));

    DependencyGraph graph;
    graph.build({"all"}, rules);

    auto* node = graph.node("main.o");
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->stem, "main");
    ASSERT_EQ(node->normal_prereqs.size(), 1);
    EXPECT_EQ(node->normal_prereqs[0], "main.c");
}

TEST(GraphTest, PhonyTarget) {
    RuleDatabase rules;

    ExplicitRule phony;
    phony.target = ".PHONY";
    phony.normal_prereqs = {"clean"};
    rules.add_explicit_rule(std::move(phony));

    ExplicitRule clean;
    clean.target = "clean";
    clean.recipes = {"rm -f *.o"};
    rules.add_explicit_rule(std::move(clean));

    DependencyGraph graph;
    graph.build({"clean"}, rules);

    auto* node = graph.node("clean");
    ASSERT_NE(node, nullptr);
    EXPECT_TRUE(node->is_phony);
}
