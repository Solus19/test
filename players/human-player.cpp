#include "players/human-player.h"

#include <cmath>

human_player_t::human_player_t(std::istream &input_stream, std::ostream &output_stream)
  : input_stream(input_stream)
  , output_stream(output_stream) {
  for (size_t i = 1; i <= field_t::FIELD_SIZE; ++i)
    for (char c = 'A'; c <= 'A' + (char)(field_t::FIELD_SIZE - 1); ++c)
      _possible_moves.push_back(std::to_string(i) + c);
}

std::pair<int, int> human_player_t::make_move(const field_t &my_field,
                                              const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;

  std::string move;
  while (true) {
    std::getline(input_stream, move);

    for (size_t i = 0; i < (size_t)std::pow(field_t::FIELD_SIZE, 2); ++i)
      if (_possible_moves[i] == move)
        return { i / field_t::FIELD_SIZE, i % field_t::FIELD_SIZE };

    output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
  }
}

void human_player_t::on_incorrect_move(int, int) {}

void human_player_t::on_duplicate_move(int i, int j) {
  output_stream << _possible_moves[i * field_t::FIELD_SIZE + j] << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int i, int j) {
  output_stream << _possible_moves[i * field_t::FIELD_SIZE + j] << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int i, int j) {
  output_stream << _possible_moves[i * field_t::FIELD_SIZE + j] << " HIT! Your next move!" << std::endl;
}

void human_player_t::on_kill(int i, int j) {
  output_stream << _possible_moves[i * field_t::FIELD_SIZE + j] << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}
