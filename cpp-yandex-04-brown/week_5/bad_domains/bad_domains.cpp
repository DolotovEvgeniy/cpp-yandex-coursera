#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <deque>

using namespace std;

deque<string> ReversedParts(string_view s) {
  deque<string> parts;
  while (!s.empty()) {
    size_t pos = s.find('.');
    if (pos == s.npos) {
      parts.emplace_front(s);
      break;
    }
    parts.emplace_front(s.substr(0, pos));
    s.remove_prefix(pos + 1);
  }
  return parts;
}

class Domain {
public:
  explicit Domain(string_view text)
    : parts_reversed_(ReversedParts(text))
  {}

  size_t GetPartCount() const {
    return parts_reversed_.size();
  }

  const deque<string>& GetReversedParts() const {
    return parts_reversed_;
  }

  bool operator<(const Domain& other) const {
    return lexicographical_compare(
      begin(parts_reversed_), end(parts_reversed_),
      begin(other.parts_reversed_), end(other.parts_reversed_)
    );
  }

private:
  deque<string> parts_reversed_;
};

// domain is subdomain of itself
bool IsSubdomain(const Domain& subdomain, const Domain& domain) {
  const auto subdomain_reversed_parts = subdomain.GetReversedParts();
  const auto domain_reversed_parts = domain.GetReversedParts();
  return
      subdomain.GetPartCount() >= domain.GetPartCount()
      && equal(begin(domain_reversed_parts), end(domain_reversed_parts),
               begin(subdomain_reversed_parts));
}

class DomainChecker {
public:
  DomainChecker(vector<Domain> banned_domains)
    : domains_(move(banned_domains))
  {
    sort(begin(domains_), end(domains_));
    domains_ = AbsorbSubdomains(move(domains_));
  }

  // Check if candidate is subdomain of some domain
  bool IsSubdomain(const Domain& candidate) const {
    const auto it = upper_bound(begin(domains_), end(domains_), candidate);
    return it != begin(domains_)
        && ::IsSubdomain(candidate, *prev(it));
  }

private:
  vector<Domain> domains_;

  static vector<Domain> AbsorbSubdomains(vector<Domain> domains) {
    domains.erase(
        unique(begin(domains), end(domains),
          [](const Domain& lhs, const Domain& rhs) {
            return ::IsSubdomain(rhs, lhs);
          }
        ),
        end(domains)
    );
    return domains;
  }
};


vector<Domain> ReadDomains(istream& in_stream = cin) {
  vector<Domain> domains;

  size_t count;
  in_stream >> count;
  domains.reserve(count);

  for (size_t i = 0; i < count; ++i) {
    string domain_text;
    in_stream >> domain_text;
    domains.emplace_back(domain_text);
  }
  return domains;
}

vector<bool> CheckDomains(const DomainChecker& checker, const vector<Domain>& domains_to_check) {
  vector<bool> check_results;
  check_results.reserve(domains_to_check.size());
  for (const Domain& domain_to_check : domains_to_check) {
    check_results.push_back(!checker.IsSubdomain(domain_to_check));
  }

  return check_results;
}

void PrintCheckResults(const vector<bool>& check_results, ostream& out_stream = cout) {
  for (const bool check_result : check_results) {
    out_stream << (check_result ? "Good" : "Bad") << "\n";
  }
}

int main() {
  const DomainChecker checker(ReadDomains());
  const vector<Domain> domains_to_check = ReadDomains();
  PrintCheckResults(CheckDomains(checker, domains_to_check));
  return 0;
}
