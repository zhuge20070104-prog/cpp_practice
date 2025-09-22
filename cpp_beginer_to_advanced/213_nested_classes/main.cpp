#include <iostream>


class Outer {
private:
    int integer {};
    double floating {};
    inline static int stat_int {60};

public:
    Outer(int i, double d): integer {i}, floating {d} {}
    void get_inner() {
        Inner i1 {2.6};
        std::cout << "Inner inside the Outer: " << i1.get_inner() << '\n';

        // passing the current instance of outer - inner can access private members
        // of outer now
        i1.get_outer(this);
    }

    class Inner {
    public:
        explicit Inner(double inner_param);
        ~Inner() = default;

        double get_inner() const {
            return inner;
        }

        void get_outer(Outer* outer) {
            std::cout << "Inside the inner: " << outer->integer << ", "
             << outer->floating << '\n';
            std::cout << "Static from outer: " << stat_int << '\n';
        }

    private:
        double inner{};
    };
};


Outer::Inner::Inner(double inner_param): inner {inner_param} {

}

int main(int argc, char* argv[]) {
    Outer outer {2222, 2.22};
    outer.get_inner();
    return EXIT_SUCCESS;
}

