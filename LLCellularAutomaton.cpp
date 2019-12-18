#include <stdexcept>

#include "LLCellularAutomaton.h"
#include "utils.h"


LLCellularAutomaton::LLCellularAutomaton(const std::string& rulestring,
        Vector2D<GridSize> size) :
    _grid(size.y, GridRow(size.x, CellState::DEAD)), _size(size) {
    RulestringParser rulestring_parser(rulestring);
    _birth_sums = rulestring_parser.eat_sums('B', '/');
    _survival_sums = rulestring_parser.eat_sums('S', '\0');
}

void LLCellularAutomaton::advance() {
    Grid new_grid(_size.y, GridRow(_size.x));
    for (GridSize y = 0; y < _size.y; y++) {
        for (GridSize x = 0; x < _size.x; x++) {
            auto sum = get_neighborhood_sum(Vector2D<GridSize>(x, y));
            auto cur_state = _grid[y][x];

            if ((cur_state == CellState::DEAD &&
                        utils::contains(_birth_sums, sum)) ||
                    (cur_state == CellState::ALIVE &&
                        utils::contains(_survival_sums, sum))) {
                new_grid[y][x] = CellState::ALIVE;
            } else {
                new_grid[y][x] = CellState::DEAD;
            }
        }
    }

    _grid = new_grid;
}

LLCellularAutomaton::CellState LLCellularAutomaton::get_cell_state(
        Vector2D<GridSize> pos) const {
    return _grid[pos.y][pos.x];
}

void LLCellularAutomaton::set_cell_state(Vector2D<GridSize> pos,
        CellState state) {
    _grid[pos.y][pos.x] = state;
}

Vector2D<LLCellularAutomaton::GridSize> LLCellularAutomaton::get_size() const {
    return _size;
}

// TODO: Throw more appropriate custom exception
LLCellularAutomaton::RulestringParser::RulestringParser(
        const std::string& rulestring) : _str(rulestring), _str_pos(0) {}

char LLCellularAutomaton::RulestringParser::eat_char(
        const std::set<char>& chars) {
    if (_str_pos > _str.length()) {
        throw std::invalid_argument("Tried to read past end of string");
    }

    char ch = _str[_str_pos];
    if (utils::contains(chars, ch)) {
        _str_pos++;
        return ch;
    } else {
        //throw std::invalid_argument("Expected [" + chars + "]");
        throw std::invalid_argument("Expected other chars..");
    }
}

std::set<uint8_t> LLCellularAutomaton::RulestringParser::eat_sums(
        char prefix, char terminator) {
    std::set<uint8_t> sums;

    eat_char({prefix});
    std::set<char> chars{'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    chars.insert(terminator);

    char ch;
    while ((ch = eat_char(chars)) != terminator) {
        uint8_t sum = utils::convert_digit_to_int(ch);
        if (!sums.insert(sum).second) {
            throw std::invalid_argument("Sums must be unique");
        }
    }

    return sums;
}

uint8_t LLCellularAutomaton::get_neighborhood_sum(Vector2D<GridSize> pos)
    const {
    uint8_t sum = 0;

    for (int8_t x_i = -1; x_i <= 1; x_i++) {
        auto x = pos.x + x_i;
        if (x < 0 || x >= _size.x) {
            continue;
        }

        for (int8_t y_i = -1; y_i <= 1; y_i++) {
            auto y = pos.y + y_i;
            if (y < 0 || y >= _size.y || (x_i == 0 && y_i == 0)) {
                continue;
            }
            sum += _grid[y][x];
        }
    }

    return sum;
}
