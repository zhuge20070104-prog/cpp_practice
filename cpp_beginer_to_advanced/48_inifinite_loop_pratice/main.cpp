#include <iostream>


struct calculator {
    calculator() {}
    
    void run() {
        while(!end) {
            std::cout << "-----------------------------------------------------" << std::endl;
            std::cout << "What operation do you want help with?" << std::endl;
            std::cout << "+, -, * and / are supported. Please choose one and type below" << std::endl;
            std::cout << "Your operation: ";
            std::cin >> operation;

            std::cout << std::endl;
            std::cout << "Please type in your two operands separated by space and hit enter: ";
            std::cin >> operand1 >> operand2;
            std::cout << std::endl;

            switch (operation) {
            case '+':
                std::cout << operand1 << " + " << operand2 << " = " << (operand1 + operand2) << std::endl;
                break;
            
            case '-':
                std::cout << operand1 << " - " << operand2 << " = " << (operand1 - operand2) << std::endl;
                break;
            
            case '*':
                std::cout << operand1 << " * " << operand2 << " = " << (operand1 * operand2) << std::endl;
                break;
            
            case '/':
                std::cout << operand1 << " / " << operand2 << " = " << (operand1 / operand2) << std::endl;
                break;
            
            default:
                std::cout << "operation not supported" << std::endl;
                break;
            }

            std::cout << "Continue ? (Y | N): ";
            char go_on;
            std::cin >> go_on;
            if(go_on == 'Y' || go_on == 'y') {
                end = false;
            } else {
                end = true;
            }
        }

        std::cout << "Done helping out. BYE!" << std::endl;
    }


    char operation;
    double operand1;
    double operand2;
    bool end{false};
};

int main(int argc, char* argv[]) {
    
    calculator cal;
    cal.run();

    return EXIT_SUCCESS;
}