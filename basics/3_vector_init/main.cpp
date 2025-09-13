#include <string>
#include <iostream>
#include <vector>

enum FailReason {
    TypeValidationFailure,
    StartEndDistanceFailure,
    TurnCountDiffFailure,
    TurnCurveRateFailure,
    DirectionValidFailure,
    CollisionValidFailure
};

std::ostream& operator<<(std::ostream& os, FailReason const& reason) {

    if(reason == TypeValidationFailure) {
        os << "TypeValidationFailure";
    } else if(reason == StartEndDistanceFailure) {
        os << "StartEndDistanceFailure";
    } else if(reason == TurnCountDiffFailure) {
        os << "TurnCountDiffFailure";
    } else if(reason == TurnCurveRateFailure) {
        os << "TurnCurveRateFailure";
    } else if(reason == DirectionValidFailure) {
        os << "DirectionValidFailure";
    } else if(reason == CollisionValidFailure) {
        os << "CollisionValidFailure";
    } else {
        os << "Unknown Failure";
    }

    return os;
}

int main(int argc, char* argv[]) {
   
    std::vector<std::vector<FailReason>> f_reasons;
    f_reasons.resize(3);
    for(auto& f_reason: f_reasons) {
        f_reason.push_back(TurnCountDiffFailure);
    }

    for(auto const& f_reason: f_reasons) {
        for(auto const& rea: f_reason) {
            std::cout << rea << " ";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}