#include <iostream>
#include <variant>
#include <optional>

template<typename... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;


struct Counter {
  int value = 0;
};

void draw(const Counter& c) {
  std::cout << "current value: " << c.value << std::endl;
}

struct add_action{};
struct sub_action{};
struct reset_action{
 int value = 0;
};

using action = std::variant<add_action, sub_action, reset_action>;

std::optional<action> intent(char event) {
  switch (event) {
    case '+':  return add_action{};
    case '-':  return sub_action{};
    case '.':  return reset_action{};
    default: return std::nullopt;
  }
}

std::optional<Counter> update(Counter& c, action act) {
  return std::visit(
    overloaded{
      [&](auto& act) { return std::nullopt; },
      [&](add_action& act) { c.value += 1; return c; },
      [&](sub_action& act) { c.value -= 1; return c; },
      [&](reset_action& act) { c.value = act.value; return c; },
    },
    act
  );
}

int main() {
  auto event = char{};
  std::optional<Counter> state = Counter{};
  while (std::cin >> event) {
    state = intent(event)
      .and_then([&](action act) {
        return update(*state, act);
        // return state.and_then([&](Counter c) {
        //   return update(c, act);
        // });
      })
      .or_else([&]() { return state; });
    if (state) {
      draw(*state);
    }
    // auto actor = intent(event);
    // state = update(*state, *actor);
    // draw(*state);
  }
}
