#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "machine.hpp"

#define BOOST_TEST_MODULE InterfaceSeg

#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())

BOOST_AUTO_TEST_CASE(TestPrinter) {
    std::unique_ptr<IPrinter> p_printer(new PrinterImpl);
    Document doc{"Raw Document"};
    Printer p(std::move(p_printer));
    p.print(doc);
}

BOOST_AUTO_TEST_CASE(TestMachine) {
    std::unique_ptr<IPrinter> p_printer(new PrinterImpl);
    std::unique_ptr<IScanner> p_scanner(new ScannerImpl);
    Document doc{"Raw Document"};
    Machine p(std::move(p_printer), std::move(p_scanner));
    p.print(doc);
    p.scan(doc);
}

BOOST_AUTO_TEST_SUITE_END()
