#include <ctime>
#include <iostream>
#include <vector>
#include <optional>
#include <tuple>

using namespace std;

class Date {
public:
  Date() = default;
  explicit Date(int year, int month, int day)
    : year_(year)
    , month_(month)
    , day_(day)
  {}

  int year() const { return year_; }
  int month() const { return month_; }
  int day() const { return day_; }

  time_t AsTimestamp() const {
    std::tm t;
    t.tm_sec = 0;
    t.tm_min = 0;
    t.tm_hour = 0;
    t.tm_mday = day_;
    t.tm_mon = month_ - 1;
    t.tm_year = year_ - 1900;
    t.tm_isdst = 0;
    return mktime(&t);
  }

  bool operator<(const Date& other) const {
    return make_tuple(year_, month_, day_)
         < make_tuple(other.year_, other.month_, other.day_);
  }

  bool operator>(const Date& other) const {
    return make_tuple(year_, month_, day_)
         > make_tuple(other.year_, other.month_, other.day_);
  }

  bool operator==(const Date& other) const {
    return make_tuple(year_, month_, day_)
        == make_tuple(other.year_, other.month_, other.day_);
  }

private:
  int year_;
  int month_;
  int day_;

  friend istream& operator>>(istream& is, Date& date);
};

istream& operator>>(istream& is, Date& date) {
  is >> date.year_;
  is.ignore();
  is >> date.month_;
  is.ignore();
  is >> date.day_;

  return is;
}

struct DateRange {
  Date from;
  Date to;
};

istream& operator>>(istream& is, DateRange& range) {
  is >> range.from >> range.to;
  return is;
}

int GetDays(const Date& lhs, const Date& rhs) {
  static constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
  if (lhs < rhs) {
    return (rhs.AsTimestamp() - lhs.AsTimestamp()) / SECONDS_IN_DAY + 1;
  } else {
    return (lhs.AsTimestamp() - rhs.AsTimestamp()) / SECONDS_IN_DAY + 1;
  }
}

size_t GetIndex(const Date& date) {
  return GetDays(Date(2000, 1, 1), date);
}

int GetDays(const DateRange& range) {
  return GetDays(range.from, range.to);
}

int GetDays(optional<DateRange> range) {
  if (!range.has_value()) {
    return 0;
  }
  return GetDays(range.value());
}

optional<DateRange> Intersects(
    const DateRange& lhs, const DateRange& rhs)
{
  if (lhs.to < rhs.from || lhs.from > rhs.to) {
    return nullopt;
  }
  return DateRange{
    max(lhs.from, rhs.from),
    min(lhs.to, rhs.to)
  };
}

struct IncomeRange {
  DateRange range;
  double value;
};

istream& operator>>(istream& is, IncomeRange& range) {
  is >> range.range.from >> range.range.to >> range.value;
  return is;
}

struct Money {
  double earned = 0.;
  double spended = 0.;
};

class BudgetManager {
public:
  BudgetManager()
    : moneyPerDays_(36600)
  {}

  void Earn(const DateRange& range, double money) {
    double moneyPerDay = money / GetDays(range);
    size_t fromIndex = GetIndex(range.from);
    size_t toIndex = GetIndex(range.to);
    for (size_t i = fromIndex; i <= toIndex; i++) {
      moneyPerDays_[i].earned += moneyPerDay;
    }
  }

  void Spend(const DateRange& range, double money) {
    double moneyPerDay = money / GetDays(range);
    size_t fromIndex = GetIndex(range.from);
    size_t toIndex = GetIndex(range.to);
    for (size_t i = fromIndex; i <= toIndex; i++) {
      moneyPerDays_[i].spended += moneyPerDay;
    }
  }

  double ComputeIncome(const DateRange& range) const {
    double income = 0.;
    size_t fromIndex = GetIndex(range.from);
    size_t toIndex = GetIndex(range.to);
    for (size_t i = fromIndex; i <= toIndex; i++) {
      income += moneyPerDays_[i].earned - moneyPerDays_[i].spended;
    }
    return income;
  }

  void PayTax(const DateRange& range, size_t percentage = 13) {
    const double taxCoeff = percentage / 100.;

    size_t fromIndex = GetIndex(range.from);
    size_t toIndex = GetIndex(range.to);
    for (size_t i = fromIndex; i <= toIndex; i++) {
      double income = max(0., moneyPerDays_[i].earned - moneyPerDays_[i].spended);
      moneyPerDays_[i].earned *= (1 - taxCoeff);
    }
  }

private:
  vector<Money> moneyPerDays_;
};

int main() {
  cout.precision(25);

  BudgetManager manager;

  int q;
  cin >> q;

  for (int i = 0; i < q; i++) {
    string query;
    cin >> query;
    if (query == "Earn") {
      DateRange range;
      double money;
      cin >> range >> money;
      manager.Earn(range, money);
    } else if (query == "Spend") {
      DateRange range;
      double money;
      cin >> range >> money;
      manager.Spend(range, money);
    } else if (query == "ComputeIncome") {
      DateRange range;
      cin >> range;
      cout << manager.ComputeIncome(range) << endl;
    } else if (query == "PayTax") {
      DateRange range;
      size_t percentage;
      cin >> range >> percentage;
      manager.PayTax(range, percentage);
    }
  }

  return 0;
}

