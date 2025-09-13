#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "neural.hpp"
#include <utility>

#define BOOST_TEST_MODULE CompositeNeurons
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestCompositeNeurons) {
    Neuron n1, n2;
    n1.connect_to(n2);

    std::cout << n1 << n2 << std::endl;

    NeuronLayer l1{5};
    Neuron n3;
    l1.connect_to(n3);
    
    std::cout << "Neuron " << n3.id << std::endl << n3 << std::endl;
    std::cout << "Layer " << std::endl << l1 << std::endl;

    NeuronLayer l2{ 2 }, l3{ 3 };
    l2.connect_to(l3);
    std::cout << "Layer l2" << std::endl << l2;
    std::cout << "Layer l3" << std::endl << l3;
}

BOOST_AUTO_TEST_SUITE_END()
