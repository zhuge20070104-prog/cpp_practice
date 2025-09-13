#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"
#include <iostream>
#include <thread>

using Poco::ActiveMethod;
using Poco::ActiveResult;

class ActiveMethodExample {
public:
    struct AddArgs {
        int a;
        int b;
    };

    ActiveMethodExample(): activeAdd(this, &ActiveMethodExample::activeAddImp) {

    }

    ActiveMethod<int, AddArgs, ActiveMethodExample> activeAdd;
private:
    int activeAddImp(AddArgs const& args) {
        std::cout << "in activeAddImp: " << std::this_thread::get_id() << std::endl;
        return args.a + args.b;
    }
};

int main(int argc, char* argv[]) {
    ActiveMethodExample example;
    
    ActiveMethodExample::AddArgs args = {1, 2};
    ActiveResult<int> result = example.activeAdd(args);
    result.wait();

    std::cout << "In main thread: " << std::this_thread::get_id() << std::endl;
    std::cout << result.data() << std::endl;
    
    return EXIT_SUCCESS;
}


