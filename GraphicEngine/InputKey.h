#pragma once

enum class InputKey {
    Up, Down, Left, Right,
    EndTurn, None
};

#include <queue>
#include <mutex>
#include <optional>

class InputQueue {
private:
    std::queue<InputKey> queue;
    std::mutex mutex;

public:
    void Push(InputKey key) {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(key);
    }

    std::optional<InputKey> Pop() {
        std::lock_guard<std::mutex> lock(mutex);
        if (queue.empty()) return std::nullopt;
        InputKey key = queue.front();
        queue.pop();
        return key;
    }
};