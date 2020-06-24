#pragma once

using namespace std;

enum TimeUnit {
  SECONDS,
  MINUTES,
  HOURS,
  DAYS,
  MONTHS,
  YEARS
};

class DateTime {
private:
  static unsigned maxDay(unsigned y, unsigned m) {
    switch (m) {
      case  0: return 31;
      case  1:
        if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {
          return 29;
        } else {
          return 28;
        }
      case  2: return 31;
      case  3: return 30;
      case  4: return 31;
      case  5: return 30;
      case  6: return 31;
      case  7: return 31;
      case  8: return 30;
      case  9: return 31;
      case 10: return 30;
      case 11: return 31;
      default: return  0;
    }
  }

  static unsigned long yearToSecs(unsigned long year, int *is_leap) {
  	if (year - 2uLL <= 136) {
  		int y = year;
  		int leaps = (y - 68) >> 2;
  		if (!((y - 68) & 3)) {
  			leaps--;
  			if (is_leap) *is_leap = 1;
  		} else if (is_leap) *is_leap = 0;
  		return 31536000 * (y - 70) + 86400 * leaps;
  	}

  	int cycles, centuries, leaps, rem;

  	cycles = (year - 100) / 400;
  	rem = (year - 100) % 400;
  	if (rem < 0) {
  		cycles--;
  		rem += 400;
  	}
  	if (!rem) {
  		*is_leap = 1;
  		centuries = 0;
  		leaps = 0;
  	} else {
  		if (rem >= 200) {
  			if (rem >= 300) centuries = 3, rem -= 300;
  			else centuries = 2, rem -= 200;
  		} else {
  			if (rem >= 100) centuries = 1, rem -= 100;
  			else centuries = 0;
  		}
  		if (!rem) {
  			*is_leap = 0;
  			leaps = 0;
  		} else {
  			leaps = rem / 4U;
  			rem %= 4U;
  			*is_leap = !rem;
  		}
  	}

  	leaps += 97 * cycles + 24 * centuries - *is_leap;

  	return (year - 100) * 31536000LL + leaps * 86400LL + 946684800 + 86400;
  }

  static int monthToSecs(int month, int is_leap) {
  	static int secs_through_month[] = {
  		0, 31 * 86400, 59 * 86400, 90 * 86400,
  		120 * 86400, 151 * 86400, 181 * 86400, 212 * 86400,
  		243 * 86400, 273 * 86400, 304 * 86400, 334 * 86400};
  	int t = secs_through_month[month];
  	if (is_leap && month >= 2) t += 86400;
  	return t;
  }

  static unsigned long toSeconds(const DateTime& d) {
	  int is_leap;
	  unsigned year = d.year;
	  unsigned month = d.month;
	  if (month >= 12 || month < 0) {
	  	int adj = month / 12;
	  	month %= 12;
	  	if (month < 0) {
	  		adj--;
	  		month += 12;
	  	}
	  	year += adj;
	  }
	  unsigned long t = yearToSecs(year, &is_leap);
	  t += monthToSecs(month, is_leap);
	  t += 86400uL * d.day;
	  t += 3600uL * d.hours;
	  t += 60uL * d.minutes;
	  t += d.seconds;
	  return t;
  }

  static DateTime fromSeconds(unsigned long t) {
    long long days, secs;
	  int remdays, remsecs, remyears;
	  int qc_cycles, c_cycles, q_cycles;
	  int years, months;
	  static int days_in_month[] = {31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29};

    secs = t - (946684800LL + 86400 * (31 + 29));
	  days = secs / 86400;
	  remsecs = secs % 86400;
	  if (remsecs < 0) {
	  	remsecs += 86400;
	  	days--;
	  }

	  qc_cycles = days / (365 * 400 + 97);
	  remdays = days % (365 * 400 + 97);
	  if (remdays < 0) {
	  	remdays += (365 * 400 + 97);
	  	qc_cycles--;
	  }

	  c_cycles = remdays / (365 * 100 + 24);
	  if (c_cycles == 4) c_cycles--;
	  remdays -= c_cycles * (365 * 100 + 24);

	  q_cycles = remdays / (365 * 4 + 1);
	  if (q_cycles == 25) q_cycles--;
	  remdays -= q_cycles * (365 * 4 + 1);

	  remyears = remdays / 365;
	  if (remyears == 4) remyears--;
	  remdays -= remyears * 365;

	  years = remyears + 4 * q_cycles + 100 * c_cycles + 400 * qc_cycles;

	  for (months = 0; days_in_month[months] <= remdays; months++) {
	  	remdays -= days_in_month[months];
    }

	  unsigned r_year = years + 100;
	  unsigned r_mon = months + 2;
	  if (r_mon >= 12) {
	  	r_mon -=12;
	  	r_year++;
	  }
	  unsigned r_mday = remdays;

	  unsigned r_hour = remsecs / 3600;
	  unsigned r_min = remsecs / 60 % 60;
	  unsigned r_sec = remsecs % 60;

    return DateTime(r_year, r_mon, r_mday, r_hour, r_min, r_sec);
  }

public:
  const unsigned year,  month,    day;
  const unsigned hours, minutes,  seconds;

  DateTime(unsigned year, unsigned month, unsigned day,
    int hours, int minutes, int seconds) :
      year    (year   ),
      month   (month  ),
      day     (day    ),
      hours   (hours  ),
      minutes (minutes),
      seconds (seconds) {
  }

  bool isValid() const {
    if (seconds >= 60 || minutes  >= 60 || hours  >= 24 ||
        day     >= 31 || month    >= 12 || year   ==  0   ) {
      return false;
    }
    return day < maxDay(year, month);
  }

  unsigned dayOfYear() const {
    unsigned ret = day;
    for (int i = 0; i < month; i++) {
      ret += maxDay(year, i);
    }
    return ret;
  }

  DateTime add(unsigned long d, TimeUnit unit) const {
    unsigned long a = toSeconds(*this);

    switch (unit) {
      case SECONDS:
        a += d;
        break;
      case MINUTES:
        a += d * 60;
        break;
      case HOURS:
        a += d * 60 * 60;
        break;
      case DAYS:
        a += d * 24 * 60 * 60;
        break;
      case MONTHS:
        a += d * 30 * 24 * 60 * 60;
        break;
      case YEARS:
        a += d * 365 * 24 * 60 * 60;
        break;
      default:
        // invalid
        break;
    }

    return fromSeconds(a);
  }

  DateTime sub(unsigned long d, TimeUnit unit) const {
    unsigned long a = toSeconds(*this);

    switch (unit) {
      case SECONDS:
        a -= d;
        break;
      case MINUTES:
        a -= d * 60;
        break;
      case HOURS:
        a -= d * 60 * 60;
        break;
      case DAYS:
        a -= d * 24 * 60 * 60;
        break;
      case MONTHS:
        a -= d * 30 * 24 * 60 * 60;
        break;
      case YEARS:
        a -= d * 365 * 24 * 60 * 60;
        break;
      default:
        // invalid
        break;
    }

    return fromSeconds(a);
  }

  int dayOfWeek() const {
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    unsigned y = year;
    if (month < 2) {
      y -= 1;
    }

    return (
      y       +
      y /   4 -
      y / 100 +
      y / 400 + t[month] + (day + 1)) % 7;
  }

  static unsigned long diff(const DateTime& a, const DateTime& b, TimeUnit unit) {
    if (a.year < 1970 || b.year < 1970) {
      // undefined
      return 0;
    }

    unsigned long sa = (unsigned long)
      a.seconds + a.minutes * 60 + a.hours * 60 * 60 +
      a.dayOfYear() * 24 * 60 * 60 +
      (a.year - 70) * 31536000 + ((a.year - 69) / 4) * 86400 -
      ((a.year - 1) / 100) * 86400 + ((a.year + 299) / 400) * 86400;

    unsigned long sb = (unsigned long)
      b.seconds + b.minutes * 60 + b.hours * 60 * 60 +
      b.dayOfYear() * 24 * 60 * 60 +
      (b.year - 70) * 31536000 + ((b.year - 69) / 4) * 86400 -
      ((b.year - 1) / 100) * 86400 + ((b.year + 299) / 400) * 86400;

    switch (unit) {
      case SECONDS:
        break;
      case MINUTES:
        sa /= 60;
        sb /= 60;
        break;
      case HOURS:
        sa /= 60 * 60;
        sb /= 60 * 60;
        break;
      case DAYS:
        sa /= 24 * 60 * 60;
        sb /= 24 * 60 * 60;
        break;
      case MONTHS:
        sa /= 30 * 24 * 60 * 60;
        sb /= 30 * 24 * 60 * 60;
        break;
      case YEARS:
        sa /= 365 * 24 * 60 * 60;
        sb /= 365 * 24 * 60 * 60;
        break;
      default:
        // invalid
        break;
    }

    return max(sa, sb) - min(sa, sb);
  }

  static string dayOfWeekToString(int d) {
    switch (d) {
      case  0: return "sunday";
      case  1: return "monday";
      case  2: return "tuesday";
      case  3: return "wednesday";
      case  4: return "thursday";
      case  5: return "friday";
      case  6: return "saturday";
      default: return "invalid";
    }
  }
};
