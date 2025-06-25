
#include <iostream>
#include "GameHandler.h"
#include "CommandInvoker.h"

int main()
{


    std::cout << "Hello World!\n";

    GameHandler gameHandlerInstance;
    GameHandler& gameHandler = gameHandlerInstance;
    CommandInvoker invoker;


    gameHandler.Initiate();
    gameHandler.Run(invoker);

   


}

