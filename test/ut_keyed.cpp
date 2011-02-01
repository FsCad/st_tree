#include <boost/test/unit_test.hpp>

#include "ootree.h"
#include "ut_common.h"


BOOST_AUTO_TEST_SUITE(ut_keyed)


BOOST_AUTO_TEST_CASE(default_ctor) {
    tree<int, cscat<keyed, std::string> > t1;
    BOOST_CHECK(t1.empty());
    BOOST_CHECK_EQUAL(t1.size(), 0);
    BOOST_CHECK_EQUAL(t1.depth(), 0);
    BOOST_CHECK_THROW(t1.root(), ootree::exception);
}

BOOST_AUTO_TEST_CASE(insert_root) {
    tree<int, cscat<keyed, std::string> > t1;
    t1.insert(7);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.size(), 1);
    BOOST_CHECK_EQUAL(t1.depth(), 1);
    BOOST_CHECK_EQUAL(t1.root().is_root(), true);
    BOOST_CHECK_EQUAL(t1.root().data(), 7);
    BOOST_CHECK_THROW(t1.root().parent(), ootree::exception);
}


BOOST_AUTO_TEST_CASE(insert_subnodes) {
    tree<int, cscat<keyed, std::string> > t1;
    typedef tree<int, cscat<keyed, std::string> >::node_type::value_type value_type;

    t1.insert(7);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.size(), 1);
    BOOST_CHECK_EQUAL(t1.depth(), 1);
    BOOST_CHECK_EQUAL(t1.root().size(), 0);

    t1.root().insert(value_type("0", 8));
    BOOST_CHECK_EQUAL(t1.size(), 2);
    BOOST_CHECK_EQUAL(t1.depth(), 2);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.root().size(), 1);

    t1.root().insert(value_type("1", 9));
    BOOST_CHECK_EQUAL(t1.size(), 3);
    BOOST_CHECK_EQUAL(t1.depth(), 2);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.root().size(), 2);

    BOOST_CHECK_EQUAL(t1.root().data(), 7);
    BOOST_CHECK_EQUAL(t1.root()["0"].data(), 8);
    BOOST_CHECK_EQUAL(t1.root()["1"].data(), 9);
}


BOOST_AUTO_TEST_CASE(clear) {
    tree<int, cscat<keyed, std::string> > t1;
    typedef tree<int, cscat<keyed, std::string> >::node_type::value_type value_type;

    t1.insert(7);
    t1.root().insert("0", 8);
    t1.root().insert("1", 9);
    BOOST_CHECK_EQUAL(t1.size(), 3);
    BOOST_CHECK_EQUAL(t1.depth(), 2);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.root().size(), 2);

    CHECK_TREE(t1, data(), "7 8 9");

    t1.clear();
    BOOST_CHECK_EQUAL(t1.size(), 0);
    BOOST_CHECK_EQUAL(t1.depth(), 0);
    BOOST_CHECK_EQUAL(t1.empty(), true);
    BOOST_CHECK_THROW(t1.root(), ootree::exception);
}


BOOST_AUTO_TEST_CASE(reinsert) {
    tree<int, cscat<keyed, std::string> > t1;
    typedef tree<int, cscat<keyed, std::string> >::node_type::value_type value_type;
 
    t1.insert(7);
    t1.root().insert("0", 8);
    t1.root().insert("1", 9);
    BOOST_CHECK_EQUAL(t1.size(), 3);
    BOOST_CHECK_EQUAL(t1.depth(), 2);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.root().size(), 2);
    CHECK_TREE(t1, data(), "7 8 9");

    t1.insert(3);
    BOOST_CHECK_EQUAL(t1.size(), 1);
    BOOST_CHECK_EQUAL(t1.depth(), 1);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.root().size(), 0);
    BOOST_CHECK_EQUAL(t1.root().data(), 3);
    CHECK_TREE(t1, data(), "3");
}


BOOST_AUTO_TEST_CASE(erase) {
    tree<int, cscat<keyed, std::string> > t1;
    typedef tree<int, cscat<keyed, std::string> >::node_type::value_type value_type;
 
    t1.insert(7);
    t1.root().insert("0", 8);
    CHECK_TREE(t1, data(), "7 8");

    t1.root().erase(t1.root().begin());
    BOOST_CHECK_EQUAL(t1.size(), 1);
    BOOST_CHECK_EQUAL(t1.depth(), 1);
    BOOST_CHECK_EQUAL(t1.empty(), false);
    BOOST_CHECK_EQUAL(t1.root().size(), 0);
    BOOST_CHECK_EQUAL(t1.root().data(), 7);
}


BOOST_AUTO_TEST_CASE(erase_noarg) {
    tree<int, cscat<keyed, std::string> > t1;
    typedef tree<int, cscat<keyed, std::string> >::node_type::value_type value_type;
 
    t1.insert(2);
    t1.root().insert("0", 3);
    t1.root().insert("1", 5);
    t1.root()["0"].insert("0",7);
    t1.root()["0"].insert("1",11);
    t1.root()["1"].insert("0",13);
    t1.root()["1"].insert("1",17);

    CHECK_TREE(t1, data(), "2 3 5 7 11 13 17");
    t1.root()["1"].erase();
    CHECK_TREE(t1, data(), "2 3 7 11");

    t1.root()["0"]["1"].erase();
    CHECK_TREE(t1, data(), "2 3 7");

    t1.root().erase();
    BOOST_CHECK_EQUAL(t1.empty(), true);
    CHECK_TREE(t1, data(), "");
}


BOOST_AUTO_TEST_SUITE_END()
