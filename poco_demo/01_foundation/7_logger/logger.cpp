#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"

using Poco::Logger;
using Poco::AutoPtr;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;
using std::shared_ptr;


int main(int argc, char* argv[]) {
    AutoPtr<PatternFormatter>  console_formatter(new PatternFormatter("[%O] %s: %p: %t"));
    AutoPtr<ConsoleChannel> console_channel(new ConsoleChannel());
    AutoPtr<FormattingChannel> pFCConsole(new FormattingChannel(console_formatter)); 
    pFCConsole->setChannel(console_channel);
    pFCConsole->open();

    AutoPtr<PatternFormatter> file_formatter(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q:%t"));
    AutoPtr<FileChannel> file_channel(new FileChannel("sample.log"));   
    AutoPtr<FormattingChannel> pFCFile(new FormattingChannel(file_formatter));
    pFCFile->setChannel(file_channel);
    pFCFile->open();


    Logger& consoleLogger = Logger::create("ConsoleLogger", pFCConsole.get(), Message::PRIO_INFORMATION);
    Logger& fileLogger = Logger::create("FileLogger", pFCFile.get(), Message::PRIO_WARNING);

    consoleLogger.error("An error message");
    fileLogger.error("An error message");

    consoleLogger.warning("A warning message");
    fileLogger.warning("A warning message");

    consoleLogger.information("An information message");
    fileLogger.information("An information message");

    poco_information(consoleLogger, "Another information message");
    poco_warning_f2(consoleLogger, "A warning message with arguments: %d, %d", 1, 2);

    Logger::get("ConsoleLogger").error("Another error message");

    return EXIT_SUCCESS;
}