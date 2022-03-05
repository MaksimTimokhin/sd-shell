#include "expander.h"

#include <algorithm>

Expander::Expander() = default;

std::string Expander::GetVariable(const std::string &name) const {
    auto it = variables_.find(name);
    if (it == variables_.end()) {
        return "";
    }
    return it->second;
}

void Expander::SetVariable(const VariableAssignment &expression) {
    variables_[expression.name] = expression.value;
}

std::string Expander::ExpandExpression(const std::string &expression) const {
    auto curr_dollar_it = std::find(expression.begin(), expression.end(), '$');
    std::string result(expression.begin(), curr_dollar_it);
    for (; curr_dollar_it < expression.end() - 1;) {
        if (!isalnum(*(curr_dollar_it + 1))) {
            auto next_dollar_it = std::find(curr_dollar_it + 1, expression.end(), '$');
            std::copy(curr_dollar_it, next_dollar_it, std::back_inserter(result));
            curr_dollar_it = next_dollar_it;
            continue;
        }

        auto name_end = std::find_if_not(curr_dollar_it + 1, expression.end(),
                                         isalpha(*(curr_dollar_it + 1)) ? isalnum : isdigit);

        std::string var_name(curr_dollar_it + 1, name_end);
        result += GetVariable(var_name);

        curr_dollar_it = std::find(curr_dollar_it + 1, expression.end(), '$');
        std::copy(name_end, curr_dollar_it, std::back_inserter(result));
    }
    if (curr_dollar_it != expression.end()) {
        result.push_back('$');
    }
    return result;
}

std::optional<Expander::VariableAssignment> Expander::ParseVariableAssignment(
    const std::string &expression) const {
    if (expression.empty() || !isalpha(expression.front())) {
        return std::nullopt;
    }

    size_t operator_pos = std::string::npos;
    std::string name;
    for (size_t i = 0; i < expression.size(); ++i) {
        if (expression[i] == '=') {
            operator_pos = i;
            break;
        }
        if (!isalnum(expression[i])) {
            return std::nullopt;
        }
        name.push_back(expression[i]);
    }
    if (operator_pos == std::string::npos) {
        return std::nullopt;
    }

    return VariableAssignment{name, ExpandExpression(expression.substr(operator_pos + 1))};
}
