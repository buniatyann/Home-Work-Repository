#include <vector>
#include <limits>
#include <initializer_list>
#include <algorithm>

template <typename T>
struct node {
    std::vector<node*> children;
    T val;
    bool is_maximizer;

    node(const T& x, bool max = true) : val(x), is_maximizer(max) {}
    node(const T& x, std::initializer_list<node*> lst, bool max) : children(lst), val(x), is_maximizer(max) {}
    
    bool is_terminal() const {
        return children.empty();
    }

    int evaluate() {
        return val;
    }
};

template <typename T>
int alpha_beta(node<T>* nd, int depth, int alpha, int beta) {
    if (!nd || depth == 0 || nd->is_terminal()) {
        return nd ? nd->evaluate() : 0;
    }

    if (nd->is_maximizer) {
        return max_value(nd, depth, alpha, beta);
    } 
    else {
        return min_value(nd, depth, alpha, beta);
    }
}

template <typename T>
int max_value(node<T>* x, int depth, int alpha, int beta) {
    int max_eval = std::numeric_limits<int>::min();
    for (node<T>* child : x->children) {
        int eval = alpha_beta(child, depth - 1, alpha, beta);
        max_eval = std::max(max_eval, eval);
        alpha = std::max(eval, alpha);
        if (beta <= alpha) {
            break; // beta cut-off
        }
    }

    return max_eval;
}

template <typename T>
int min_value(node<T>* x, int depth, int alpha, int beta) {
    int min_eval = std::numeric_limits<int>::max();
    for (const move_t& mv : state.legal_moves()) {
        int eval = alpha_beta(child, depth - 1, alpha, beta);
        min_eval = std::min(eval,  min_eval);
        beta = std::min(eval, beta);
        if (beta <= alpha) {
            break // alpha cut-off
        }
    }
}
