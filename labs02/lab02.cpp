#include <iostream>
#include <set>
#include <random>
#include <fstream>
#include <ctime>

using State = int;
const State MaxState = 1000;

class GeneralState {
protected:
    std::set<State> state;

public:
    bool contains(const State &s) const
    {
        return (state.find(s) != state.end());
    }

    GeneralState(const std::set<State> &state) : state(state) {}

    GeneralState() = default;
    GeneralState(const int N, int min, int max, int seed)
    {
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(min, max);

        for (int unique_states = 0; unique_states != N; unique_states++) {
            int current_random = dstr(reng);
            if (state.find(current_random) == state.end()) {
                state.emplace(current_random);
            }
        }
    }

    GeneralState operator+(const GeneralState &rha) const
    {
        GeneralState Sum = *this;
        for (std::set<State>::iterator i = rha.state.begin(); i != rha.state.end(); ++i) {
            Sum.state.emplace(*i);
        }
        return Sum;
    }

    GeneralState operator*(const GeneralState &rha) const
    {
        GeneralState Res;
        for (std::set<State>::iterator i = rha.state.begin(); i != rha.state.end(); ++i) {
            for (std::set<State>::iterator j = state.begin(); j != state.end(); ++j) {
                if (*i == *j) {
                    Res.state.emplace(*i);
                }
            }
        }
        return Res;
    }

    GeneralState operator!() const
    {
        GeneralState Res;

        for (State i = -MaxState; i <= MaxState; i++) {
            if (!(this->contains(i))) {
                Res.state.emplace(i);
            }
        }

        return Res;
    }
};

class DiscreteState : public GeneralState {
public:
    DiscreteState(State s0)
    {
        state.emplace(s0);
    }
    DiscreteState() : DiscreteState(0) {}
};

class SegmentState : public GeneralState {
public:
    SegmentState(State begin_s0, State end_s0)
    {
        for (int i = begin_s0; i < end_s0 + 1; i++) {
            state.emplace(i);
        }
    }
    SegmentState() : SegmentState(0, 0) {};
};

class ProbabilityTest {
private:
    State const E_min, E_max;

public:
    ProbabilityTest(State E_min, State E_max) : E_min(E_min), E_max(E_max) {}

    float test(const GeneralState &system, const unsigned test_count, const unsigned seed)
    {
        std::default_random_engine reng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt) {
            if (system.contains(dstr(reng))) {
                ++good;
            }
        }

        return static_cast<float>(good) / static_cast<float>(test_count);
    }

    float different_seed_test(const GeneralState &system, const unsigned test_count, const int seed_seed)
    {
        int N = 5;
        int E = 100;
        float sum = 0;

        for (int i = 0; i < N; i++) {
            std::default_random_engine reng(seed_seed);
            std::uniform_int_distribution<int> dstr(-E, E);
            sum += test(system, test_count, reng, dstr);
        }

        return sum/N;
    }

    float test(const GeneralState &system, const unsigned test_count, std::default_random_engine reng, std::uniform_int_distribution<int> dstr)
    {

        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt) {
            if (system.contains(dstr(reng))) {
                ++good;
            }
        }

        return static_cast<float>(good) / static_cast<float>(test_count);
    }

};

int main()
{
    int seed_for_State = time(nullptr);
    int seed_for_Test = time(nullptr);
    srand(seed_for_Test);

    //GeneralState a(100, -1000, 1000, seed_for_State);
    DiscreteState b(1);
    SegmentState c(0, 99);
    ProbabilityTest pt(-1000, 1000);

    std::ofstream fout;

    fout.open("results.txt");

    for (int test_amount = 0; test_amount < 40000; test_amount += 10) {
        fout << test_amount << " ;" << pt.different_seed_test(b, test_amount, seed_for_Test) << " ;"
             << pt.different_seed_test(c, test_amount, seed_for_Test) << '\n';
        //seed_for_Test = rand() * 1000 / 83 + time(nullptr) * (rand() + 1);
    }

    fout.close();

    return 0;
}
