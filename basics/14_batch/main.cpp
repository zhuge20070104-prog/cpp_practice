#include <string>
#include <iostream>
#include <vector>

int const BATCH_RUN_SIZE = 2;
int main(int argc, char* argv[]) {
    std::vector<int> total_sequences = {1};

    std::vector<std::vector<int>> batch_cases;
    for(int i=0; i<total_sequences.size(); i += BATCH_RUN_SIZE) {      
        std::vector<int>  one_batch;
       
        if(i + BATCH_RUN_SIZE < total_sequences.size()) {
            one_batch.resize(BATCH_RUN_SIZE);
            std::copy(total_sequences.begin()+i, total_sequences.begin() + i + BATCH_RUN_SIZE, one_batch.begin());
        } else {
            one_batch.resize(total_sequences.size() - i);
            std::copy(total_sequences.begin()+i, total_sequences.end(), one_batch.begin());
        }
        one_batch.shrink_to_fit();
        batch_cases.push_back(one_batch);
    }

    total_sequences.clear();

    for(auto const& vec: batch_cases) {
        std::cout << "One batch: ";
        for(auto const& ele: vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }
}