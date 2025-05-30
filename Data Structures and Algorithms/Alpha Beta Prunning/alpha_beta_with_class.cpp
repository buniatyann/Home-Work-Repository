#include <vector>
#include <limits>
#include <algorithm>

struct move_t {
    int row{};
    int col{};
};

class game_state {
public:
    bool is_terminal() const;
    int evaluate() const;
    std::vector<move_t> legal_moves() const;
    void apply_move(const move_t& move);
    void undo_move(const move_t& move);
    bool is_maximizers_move() const;
};

int alpha_beta(game_state& state, int depth, int alpha, int beta) {
    if (depth == 0 || state.is_terminal()) {
        return state.evaluate();
    }

    if (state.is_maximizers_move()) {
        int max_eval = std::numeric_limits<int>::min();
        for (const move_t& mv : state.legal_moves()) {
            state.apply_move(mv);
            int eval = alpha_beta(state, depth - 1, alpha, beta);
            state.undo_move(mv);
            max_eval = std::max(eval, max_eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha) {
                break; // beta cut-off
            }
        }
    
        return max_eval;
    } 
    else {
        int min_eval = std::numeric_limits<int>::max();
        for (const move_t& mv : state.legal_moves()) {
            state.apply_move(mv);
            int eval = alpha_beta(state, depth - 1, alpha, beta);
            state.undo_move(mv);
            min_eval = std::min(eval, min_eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break; // alpha cut-off
            }
        }
    
        return min_eval;
    }
}
