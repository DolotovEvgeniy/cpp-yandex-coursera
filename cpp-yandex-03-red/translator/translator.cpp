#include "test_runner.h"
#include <string>
#include <string_view>
#include <set>
#include <unordered_map>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        auto [source_it, source_inserted] = words_.emplace(source);
        string_view source_sv = *source_it;
        auto [target_it, target_inserted] = words_.emplace(target);
        string_view target_sv = *target_it;
        forward_[source_sv] = target_sv;
        backward_[target_sv] = source_sv;
    }

    string_view TranslateForward(string_view source) const {
        auto it = forward_.find(source);
        return it == forward_.end() ? ""sv : it->second;
    }

    string_view TranslateBackward(string_view target) const {
        auto it = backward_.find(target);
        return it == backward_.end() ? ""sv : it->second;
    }

private:
    set<string> words_;
    unordered_map<string_view, string_view> forward_;
    unordered_map<string_view, string_view> backward_;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
