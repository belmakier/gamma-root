#ifndef GAMR_UTILS_REPL_HH
#define GAMR_UTILS_REPL_HH

#include <atomic>
#include <functional>
#include <mutex>
#include <string>
#include <thread>

namespace GamR {
namespace Utils {

class REPL {
private:
   std::string fInput;
   std::string fPrompt;
   std::atomic<bool> fContinue;
   std::atomic<bool> fNextLine;
   std::mutex fInputLock;
   std::thread fThread;

public:
   REPL(std::string prompt);
   ~REPL();
   void Prompt();
   bool Loop();
   bool Halt();
   void ReadLine(std::string &input);
};

} // namespace Utils
} // namespace GamR

#endif
