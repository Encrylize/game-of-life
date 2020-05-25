#include <algorithm>
#include <stdexcept>

#include "LLCellularAutomaton.h"


LLCA::LLCellularAutomaton(const std::string& rulestring) {
    RulestringParser rulestring_parser(rulestring);
    _birth_sums = rulestring_parser.eat_sums('B', '/');
    _survival_sums = rulestring_parser.eat_sums('S', '\0');
}

// TODO: This can probably be made more efficient
void LLCA::advance() {
    decltype(_live_cells) new_cells;
    for (const auto& cell_pos : _live_cells) {
        auto sum = get_neighborhood_sum(cell_pos);
        if (utils::contains(_survival_sums, sum)) {
            new_cells.insert(cell_pos);
        }

        for (const auto& neighbor_pos : get_cell_neighbors(cell_pos)) {
            if (get_cell_state(neighbor_pos) == CellState::ALIVE) {
                // Live cells will be checked while iterating through
                // _live_cells. No need to do it twice.
                continue;
            }

            sum = get_neighborhood_sum(neighbor_pos);
            if (utils::contains(_birth_sums, sum)) {
                new_cells.insert(neighbor_pos);
            }
        }
    }

    _live_cells = new_cells;
}

LLCA::CellState LLCA::get_cell_state(Vector2D<CellPos> pos) const {
    return utils::contains<Vector2D<CellPos>>(_live_cells, pos) ?
        CellState::ALIVE : CellState::DEAD;
}

void LLCA::set_cell_state(Vector2D<CellPos> pos, CellState state) {
    if (state == CellState::ALIVE) {
        _live_cells.insert(pos);
    } else {
        auto iter = _live_cells.find(pos);
        if (iter != _live_cells.end()) {
            _live_cells.erase(iter);
        }
    }
}

void LLCA::toggle_cell_state(Vector2D<CellPos> pos) {
    auto new_state = get_cell_state(pos) == CellState::DEAD ?
        CellState::ALIVE : CellState::DEAD;
    set_cell_state(pos, new_state);
}

// TODO: Throw more appropriate custom exception
LLCA::RulestringParser::RulestringParser(const std::string& rulestring) :
    _str(rulestring), _str_pos(0) {}

char LLCA::RulestringParser::eat_char(const std::unordered_set<char>& chars) {
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

std::unordered_set<uint8_t> LLCA::RulestringParser::eat_sums(
        char prefix, char terminator) {
    std::unordered_set<uint8_t> sums;

    eat_char({prefix});
    std::unordered_set<char> chars{'0', '1', '2', '3', '4', '5', '6', '7', '8'};
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

std::unordered_set<Vector2D<LLCA::CellPos>> LLCA::get_cell_neighbors(
        Vector2D<CellPos> pos) const {
    std::unordered_set<Vector2D<CellPos>> neighbors;
    for (int8_t x_i = -1; x_i <= 1; x_i++) {
        for (int8_t y_i = -1; y_i <= 1; y_i++) {
            if (x_i == 0 && y_i == 0) {
                continue;
            }

            Vector2D<CellPos> neighbor_pos(pos.x + x_i, pos.y + y_i);
            neighbors.insert(neighbor_pos);
        }
    }

    return neighbors;
}

uint8_t LLCA::get_neighborhood_sum(Vector2D<CellPos> pos) const {
    uint8_t sum = 0;
    for (const auto& neighbor_pos : get_cell_neighbors(pos)) {
        if (get_cell_state(neighbor_pos) == CellState::ALIVE) {
            sum++;
        }
    }
    return sum;
}
