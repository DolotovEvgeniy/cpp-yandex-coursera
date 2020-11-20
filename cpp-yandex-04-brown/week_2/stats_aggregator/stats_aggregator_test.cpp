#include "stats_aggregator.h"
#include "test_runner.h"

#include <sstream>
using namespace std;

string PrintedValue(const StatsAggregator& aggr) {
  ostringstream output;
  aggr.PrintValue(output);
  return output.str();
}

namespace StatsAggregators {

void TestSum() {
  StatsAggregators::Sum aggr;
  ASSERT_EQUAL(PrintedValue(aggr), "Sum is 0");

  aggr.Process(3);
  aggr.Process(8);
  aggr.Process(-1);
  aggr.Process(16);

  ASSERT_EQUAL(PrintedValue(aggr), "Sum is 26");
}

void TestMin() {
  StatsAggregators::Min aggr;
  ASSERT_EQUAL(PrintedValue(aggr), "Min is undefined");

  aggr.Process(3);
  aggr.Process(8);
  aggr.Process(-1);
  aggr.Process(16);

  ASSERT_EQUAL(PrintedValue(aggr), "Min is -1");
}

void TestMax() {
  StatsAggregators::Max aggr;
  ASSERT_EQUAL(PrintedValue(aggr), "Max is undefined");

  aggr.Process(3);
  aggr.Process(8);
  aggr.Process(-1);
  aggr.Process(16);

  ASSERT_EQUAL(PrintedValue(aggr), "Max is 16");
}

void TestAverage() {
  StatsAggregators::Average aggr;
  ASSERT_EQUAL(PrintedValue(aggr), "Average is undefined");

  aggr.Process(3);
  aggr.Process(8);
  aggr.Process(-1);
  aggr.Process(16);

  ASSERT_EQUAL(PrintedValue(aggr), "Average is 6");
}

void TestMode() {
  StatsAggregators::Mode aggr;
  ASSERT_EQUAL(PrintedValue(aggr), "Mode is undefined");

  aggr.Process(3);
  aggr.Process(3);
  aggr.Process(8);
  aggr.Process(8);
  aggr.Process(8);
  aggr.Process(8);
  aggr.Process(-1);
  aggr.Process(-1);
  aggr.Process(-1);
  aggr.Process(16);

  ASSERT_EQUAL(PrintedValue(aggr), "Mode is 8");
}

void TestComposite() {
  StatsAggregators::Composite aggr;
  aggr.Add(make_unique<StatsAggregators::Sum>());
  aggr.Add(make_unique<StatsAggregators::Min>());
  aggr.Add(make_unique<StatsAggregators::Max>());
  aggr.Add(make_unique<StatsAggregators::Average>());
  aggr.Add(make_unique<StatsAggregators::Mode>());

  aggr.Process(3);
  aggr.Process(8);
  aggr.Process(-1);
  aggr.Process(16);
  aggr.Process(16);

  string expected = "Sum is 42\n";
  expected += "Min is -1\n";
  expected += "Max is 16\n";
  expected += "Average is 8\n";
  expected += "Mode is 16\n";
  ASSERT_EQUAL(PrintedValue(aggr), expected);
}

}
