#include "REPL.hh"

#include <chrono>
#include <iostream>

namespace GamR {
namespace Utils {

REPL::REPL(std::string prompt) : fInput(""), fPrompt(prompt), fContinue(true), fNextLine(true)
{
   Prompt();
   fThread = std::thread([&]() {
      std::string input;
      char keypress;
      do {
         input = "";
         while (fContinue.load()) {
            while (std::cin.peek() == EOF) {
               std::this_thread::yield();
            }
            keypress = std::cin.get();
            if (keypress == '\n') {
               break;
            }
            input += keypress;
         }
         if (!fContinue.load()) {
            break;
         }
         while (fContinue.load() && !fNextLine.load()) {
            std::this_thread::yield();
         }
         if (!fContinue.load()) {
            break;
         }
         fInputLock.lock();
         fInput = input;
         fInputLock.unlock();
         fNextLine.store(false);
         Prompt();
      } while (fContinue.load());
   });
   fThread.detach();
}

REPL::~REPL()
{
   Halt();
}

void REPL::Prompt()
{
   std::cout << "\r" << fPrompt << std::flush;
}

bool REPL::Loop()
{
   return fContinue.load();
}

bool REPL::Halt()
{
   fContinue.store(false);
   return true;
}

void REPL::ReadLine(std::string &input)
{
   if (fNextLine.load()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      input.clear();
   } else {
      fInputLock.lock();
      input = fInput;
      fInputLock.unlock();
      fNextLine.store(true);
   }
}

} // namespace Utils
} // namespace GamR
