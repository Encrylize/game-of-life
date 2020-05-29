#ifndef _LL_CELLULAR_AUTOMATON_H
#define _LL_CELLULAR_AUTOMATON_H

#include <string>
#include <unordered_set>

#include "Vector2D.h"

class LLCellularAutomaton {
public:
    enum CellState { DEAD, ALIVE };

    using CellPos = intmax_t;

    // Rulestring should be in B/S notation
    LLCellularAutomaton(const std::string& rulestring);

    void advance();

    CellState get_cell_state(Vector2D<CellPos> pos) const;
    void set_cell_state(Vector2D<CellPos> pos, CellState state);
    void toggle_cell_state(Vector2D<CellPos> pos);

private:
    class RulestringParser {
    public:
        RulestringParser(const std::string& rulestring);

        std::unordered_set<uint8_t> eat_sums(char prefix, char terminator);

    private:
        char eat_char(const std::unordered_set<char>& chars);

        const std::string& _str;
        std::string::size_type _str_pos;
    };

    std::unordered_set<Vector2D<CellPos>>
        get_cell_neighbors(Vector2D<CellPos> pos) const;
    uint8_t get_neighborhood_sum(Vector2D<CellPos> pos) const;

    std::unordered_set<Vector2D<CellPos>> _live_cells;
    std::unordered_set<uint8_t> _birth_sums, _survival_sums;
};

using LLCA = LLCellularAutomaton;

#endif
