#include <iostream>
#include <thread>
#include <atomic>
#include "GameHandler.h"
#include "CommandInvoker.h"
#include "../GraphicEngine/WindowRenderer.h"

int main() {
    std::cout << "Starting Game...\n";

    GameHandler gameHandler;
    CommandInvoker invoker;

    std::atomic<bool> isRunning(true);

    // ���� ���
    std::thread gameThread([&]() {
        gameHandler.Initiate();
        gameHandler.Run(invoker);
        isRunning = false;
        });

    // ���� �������
    WindowRenderer renderer(1200, 800);
    std::thread renderThread([&]() {
        renderer.RenderGame(isRunning, [&]() -> Grid* {
            return gameHandler.GetGrid();  // ������� ���� � ���
            });
        });

    gameThread.join();
    renderThread.join();

    std::cout << "Game exited.\n";
    return 0;
}
