#pragma once

#include <optional>
#include <string>
#include <unordered_map>

class Expander {
public:
    struct VariableAssignment {
        std::string name;
        std::string value;
    };

public:
    Expander();
    std::string GetVariable(const std::string &name) const;
    void SetVariable(const VariableAssignment &expression);
    std::string ExpandExpression(const std::string &expression) const;
    std::optional<VariableAssignment> ParseVariableAssignment(const std::string &expression) const;

private:
    std::unordered_map<std::string, std::string> variables_;
};