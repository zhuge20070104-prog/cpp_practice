#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "singleton.hpp"
#include "di.hpp"
#include <utility>

#define BOOST_TEST_MODULE SingletonImplModule
#include "test.hpp"

namespace di = boost::di;

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestSingleton) {
    // di::bind的时候是 IFoo 到Foo，不能写反
    auto injector = di::make_injector(
        di::bind<IFoo>().to<Foo>().in(di::singleton)
    );

    auto bar1 = injector.create<std::shared_ptr<Bar>>();
    auto bar2 = injector.create<std::shared_ptr<Bar>>();

    BOOST_CHECK_EQUAL(bar1->foo->name(), bar2->foo->name());
    BOOST_CHECK_EQUAL(bar1->foo.get(), bar2->foo.get());
}

BOOST_AUTO_TEST_SUITE_END()
