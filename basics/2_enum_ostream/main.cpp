#include <iostream>

enum FailReason {
    TypeValidationFailure,
	StartEndDistanceFailure,
	TurnCountDiffFailure,
	TurnCurveRateFailure	
};

std::ostream& operator<<(std::ostream& os, FailReason const& reason) {
   
    if(reason == TypeValidationFailure) {
        os << "TypeValidationFailure";
    } else if(reason == StartEndDistanceFailure) {
        os << "StartEndDistanceFailure";
    } else if(reason == TurnCountDiffFailure) {
        os << "TurnCountDiffFailure";
    } else {
        os << "TurnCurveRateFailure";
    }
    return os;
}

int main(int argc, char* argv[]) {
    FailReason reason = StartEndDistanceFailure;
    std::cout << reason << std::endl;
    return EXIT_SUCCESS;
}