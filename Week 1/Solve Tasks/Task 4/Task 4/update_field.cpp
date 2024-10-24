#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

istream& operator>>(istream& is, Date& date){
    char delimiter;
    is >> date.year >> delimiter >> date.month >> delimiter >> date.day;
    return is;
}

istream& operator>>(istream& is, Time& time){
    char delimiter;
    is >> time.hours >> delimiter >> time.minutes;
    return is;
}

#define UPDATE_FIELD(ticket, field, values)                                              \
{                                                                                        \
    auto func = [](AirlineTicket& ticket, const map<string, string>& updates){           \
        map<string, string>::const_iterator it;                                          \
        it = updates.find(#field);                                                       \
        if (it != updates.end()){                                                        \
            istringstream is(it->second);                                                \
            is >> ticket.field;                                                          \
        }                                                                                \
    };                                                                                   \
    func(ticket, values);                                                                \
}
        
void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
