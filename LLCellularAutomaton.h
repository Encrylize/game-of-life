#ifndef _LL_CELLULAR_AUTOMATON_H
#define _LL_CELLULAR_AUTOMATON_H

#include <set>
#include <string>
#include <vector>

#include "Vector2D.h"


class LLCellularAutomaton {
public:
    enum CellState {
        DEAD = 0,
        ALIVE = 1
    };

private:
    using GridRow = std::vector<CellState>;
    using Grid = std::vector<GridRow>;

public:
    using GridSize = Grid::size_type;

    // Rulestring should be in B/S notation
    LLCellularAutomaton(const std::string& rulestring, Vector2D<GridSize> size);

    void advance();

    CellState get_cell_state(Vector2D<GridSize> pos) const;
    void set_cell_state(Vector2D<GridSize> pos, CellState state);

    Vector2D<GridSize> get_size() const;

private:
    class RulestringParser {
    public:
        RulestringParser(const std::string& rulestring);

        std::set<uint8_t> eat_sums(char prefix, char terminator);

    private:
        char eat_char(const std::set<char>& chars);

        const std::string& _str;
        std::string::size_type _str_pos;
    };

    uint8_t get_neighborhood_sum(Vector2D<GridSize> pos) const;

    Grid _grid;
    Vector2D<GridSize> _size;
    std::set<uint8_t> _birth_sums, _survival_sums;
};

using LLCA = LLCellularAutomaton;

#endif
