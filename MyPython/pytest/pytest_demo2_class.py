# -*-coding:utf-8-*
import pytest

# TestClass
class TestClass:
    def test_one(self):
        x = "this"
        assert "h" in x

    def test_two(self) :
        x = "hello"
        assert hasattr(x, "check" )


# pytest main
if __name__ == '__main__':
    # run all test class in ./ dir (test_*.py and *_test.py)
    pytest.main()

    # run all test class in ./subpath1
    # pytest.main(['./subpath1' ])

    # run target py
    # pytest.main(['./subpath1/test_module1.py'])

    # run target test class
    # pytest.main(['./subpath1/test_module1.py::test_m1_1'])

    # run target test function
    # pytest.main(['./subpath2/test_module2.py::TestM2::test_m2_02'])

    # run all test class which dir, class, case contains 'pp'
    # pytest.main(['-k', 'pp'])

    # run all test class which dir, class, case contains 'spec' in /subpath1/test_module1.py
    # pytest.main(['-k', 'spec', './subpath1/test_module1.py'])

    # run all test case in class ./subpath2/test_module2.py::TestM2
    # pytest.main(['-k', 'pp', './subpath2/test_module2.py::TestM2'])

    # run target test py
    # pytest.main("test_demo2_class.py")
