#ifndef DATE_H
#define DATE_H
#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>

class Date
{
private:
    uint8_t  day;
    uint8_t  month;
    uint16_t year;

public:
    Date(uint8_t day_, uint8_t month_, uint16_t year_)
        : day(day_), month(month_), year(year_)
    {
        if (!isValid(*this))
            throw std::invalid_argument("Fecha invalida");
    }

    // Getter's zone
    uint8_t  getDay()   const { return day;   }
    uint8_t  getMonth() const { return month; }
    uint16_t getYear()  const { return year;  }

    // Validaciones
    static bool isValidYear(int y)  { return y >= 1980 && y <= 2030; }

    static bool isLeapYear(int y)   {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static bool isValidMonth(int m) { return m >= 1 && m <= 12; }

    static bool isValidDay(int d, int m, int y)
    {
        if (d < 1)            return false;
        if (!isValidMonth(m)) return false;

        if (m == 2)
            return d <= (isLeapYear(y) ? 29 : 28);

        const bool hasThirty = (m == 4 || m == 6 || m == 9 || m == 11);
        return d <= (hasThirty ? 30 : 31);
    }

    static bool isValid(const Date& date)
    {
        return isValidYear(date.year)
            && isValidMonth(date.month)
            && isValidDay(date.day, date.month, date.year);
    }

    // Utilidades
    std::string toString() const
    {
        return std::to_string(day) + "/" +
               std::to_string(month) + "/" +
               std::to_string(year);
    }

    bool equals(const Date& other) const
    {
        return day   == other.day
            && month == other.month
            && year  == other.year;
    }

    bool isGreater(const Date& other) const
    {
        return  year  > other.year
                || (year  == other.year && month > other.month)
                || (year  == other.year && month == other.month && day > other.day);
    }

    bool isLess(const Date& other) const
    {
        if (year  != other.year)  return year  < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

#endif // Final de DATE_H
