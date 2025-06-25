#pragma once
#include "../Assets/Command.h"
#include <vector>
#include <memory>

class CommandInvoker {
private:
    std::vector<std::shared_ptr<Command>> commandHistory;

public:
    void executeCommand(std::shared_ptr<Command> command) {
        command->execute();  // Виконання команди
        commandHistory.push_back(command);  // Додавання команди до історії
    }

    // Можна додати функціонал для скасування команд, якщо треба
    void undo() {
        if (!commandHistory.empty()) {
            commandHistory.pop_back();  // Скасувати останню команду
        }
    }
};
