#include "../includes/medication.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

Medication::Medication()
    : InventoryItem(), expiryDate(sys_days{year{2099}/12/31}) {}

Medication::Medication(const string& name, double price, const sys_days& expiryDate)
    : InventoryItem(name, price), expiryDate(expiryDate) {}

Medication::Medication(const Medication& other) = default;


bool Medication::isExpiringSoon() const {
    auto today = floor<days>(system_clock::now());
    return expiryDate <= today + days(30);
}

double Medication::getRentabilityScore() const {
    auto today = floor<days>(system_clock::now());
    auto daysLeft = duration_cast<days>(expiryDate - today).count();
    return (daysLeft > 0 && price > 0) ? static_cast<double>(daysLeft) / price : 0;
}

void Medication::display(ostream& os) const {
    os << "[Medication] ID: " << id << " | Name: " << name
       << " | Price: $" << price << " | Expiry: " << formatDate(expiryDate);
    if (isExpiringSoon()) os << " ⚠️ EXPIRING SOON";
}

unique_ptr<InventoryItem> Medication::clone() const {
    return make_unique<Medication>(*this);
}

sys_days Medication::parseDate(const string& dateStr) {
    istringstream ss(dateStr);
    int y, m, d;
    char dash;
    ss >> y >> dash >> m >> dash >> d;
    return sys_days{year{y}/month{static_cast<unsigned>(m)}/day{static_cast<unsigned>(d)}};

}

string Medication::formatDate(const sys_days& date) {
    auto ymd = year_month_day{date};
    ostringstream ss;
    ss << static_cast<int>(ymd.year()) << '-'
       << setfill('0') << setw(2) << static_cast<unsigned>(ymd.month()) << '-'
       << setw(2) << static_cast<unsigned>(ymd.day());
    return ss.str();
}

std::chrono::sys_days Medication::getExpiryDate() const {
    return expiryDate;
}

void Medication::saveToCSV(std::ostream& out) const {
    out << "Medication," << name << "," << price << "," << formatDate(expiryDate) << "\n";
}

