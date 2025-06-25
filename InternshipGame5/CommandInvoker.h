#pragma once
#include "../Assets/Command.h"
#include <vector>
#include <memory>

class CommandInvoker {
private:
    std::vector<std::shared_ptr<Command>> commandHistory;

public:
    void executeCommand(std::shared_ptr<Command> command) {
        command->execute();  // ��������� �������
        commandHistory.push_back(command);  // ��������� ������� �� �����
    }

    // ����� ������ ���������� ��� ���������� ������, ���� �����
    void undo() {
        if (!commandHistory.empty()) {
            commandHistory.pop_back();  // ��������� ������� �������
        }
    }
};
