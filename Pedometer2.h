# include <string>
# include <stdexcept>
# include <sstream>
# include <fstream>
# include <utility>
# include <iterator>
# include <algorithm>

class Pedometer
{
public:
    struct Item
    {
        Item(const std::string &date,
             const std::string &time1,
             const std::string &time2,
             std::size_t count)
        {
            m_Date = date;
            m_BeginTime = time1;
            m_EndTime = time2;
            m_Count = count;
        }

        Item() : Item("", "", "", 0) {}

        Item(const std::string &line)
        {
            std::istringstream stream(line);
            std::string token;
            std::array<std::string, 4> arr;
            std::size_t i = 0;
            for (; std::getline(stream, token, ' '); i++)
            {
                if(i < 4)
                {
                    arr[i] = token;
                }
            }

            if(i != 4)
            {
                throw std::invalid_argument("Incorrect line " + line);
            }

            m_Date = arr[0];
            m_BeginTime = arr[1];
            m_EndTime = arr[2];
            m_Count = std::stoul(arr[3]);
        }

        std::string toString() const
        {
            return m_Date + " " + m_BeginTime + " " + m_EndTime + " " + std::to_string(m_Count);
        }

        std::size_t m_Count;
        std::string m_Date;
        std::string m_BeginTime;
        std::string m_EndTime;
    };

    Pedometer(const std::string &fname)
    {
        std::ifstream in(fname);
        if (!in.is_open())
        {
            throw std::invalid_argument("Can't open file " + fname + " for reading");
        }

        m_capacity = 20;
        m_size = 0;
        m_data = new Item[m_capacity];

        in >> m_InitialDate;
        in >> m_InitialTime;

        std::string line;
        while(std::getline(in, line))
        {
            if(!line.empty())
            {
                Append(Item(line));
            }
        }
    }

    Pedometer(const std::string &date, const std::string &time)
    {
        m_InitialDate = date;
        //если дата некорректная - бросаем исключение
        if(!validateDate(date))
        {
            throw std::invalid_argument("incorrect date = " + date);
        }
        //дата не может быть меньше 1900
        if(date < "1900")
        {
            throw std::invalid_argument("date can't be less that 1900");
        }

        if(!validateTime(time))
        {
            throw std::invalid_argument("incorrect time = " + time);
        }
        m_capacity = 20;
        m_size = 0;
        m_data = new Item[m_capacity];
        m_InitialTime = time;
    }

   Pedometer(const Pedometer &obj) :
        m_capacity(obj.m_capacity),
        m_size(obj.m_size),
        m_data(m_capacity ? new Item[m_capacity]() : nullptr)
    {
        std::copy(obj.m_data, obj.m_data + m_size, m_data);
    }

    Pedometer& operator = (const Pedometer &obj)
    {
        if (this == &obj)
        { return *this; }
        delete[] m_data;
        m_capacity = obj.m_capacity;
        m_size = obj.m_size;
        m_data = new Item[m_capacity];
        std::copy(obj.m_data, obj.m_data + m_size, m_data);
        return *this;
    }

    ~Pedometer(void)
    {
        delete[] m_data;
    }

    bool validateDate(const std::string &date) const
    {
        //дата всегда имеет формат yyyy-mm-dd
        //первым делом проверяем длину
        if(date.size() != 10)
        {
            return false;
        }
        //потом символы-разделители
        if(date[4] != '-')
        {
            return false;
        }

        if(date[7] != '-')
        {
            return false;
        }

        //все оставшиеся символы должны быть цифрами
        for(std::size_t i = 0; i < date.size(); i++)
        {
            if(i != 4 && i != 7)
            {
                auto c = date[i];
                if(c < '0' || c > '9')
                {
                    return false;
                }
            }
        }

        auto m = date.substr(5, 2);
        if(m > "12" || m < "01")
        {
            return false;
        }

        auto d = date.substr(8, 2);
        if(d > "31" || d < "01")
        {
            return false;
        }

        if(date < m_InitialDate)
        {
            return false;
        }

        return true;
    }

    bool validateTime(const std::string &time) const
    {
        //дата всегда имеет формат hh:mm
        //первым делом проверяем длину
        if(time.size() != 5)
        {
            return false;
        }
        //потом символ-разделитель
        if(time[2] != ':')
        {
            return false;
        }

        //все оставшиеся символы должны быть цифрами
        for(std::size_t i = 0; i < time.size(); i++)
        {
            if(i != 2)
            {
                auto c = time[i];
                if(c < '0' || c > '9')
                {
                    return false;
                }
            }
        }

        auto h = time.substr(0, 2);
        if(h > "23")
        {
            return false;
        }

        auto m = time.substr(3, 2);
        if(m > "59")
        {
            return false;
        }

        return true;
    }

    bool addItem(const std::string &date, const std::string &time1,
                 const std::string &time2,  std::size_t count)
    {
        if(!validateDate(date))
        {
            std::cout << "Incorrect data =" << date << '\n';
            return false;
        }

        if(!validateTime(time1))
        {
            std::cout << "Incorrect time1 =" << time1 << '\n';
            return false;
        }

        if(!validateTime(time2))
        {
            std::cout << "Incorrect time2 =" << time2 << '\n';
            return false;
        }
        //начало движение должно быть меньше завершения
        if(time1 > time2)
        {
            std::cout << "time1 > time2\n";
            return false;
        }
        //начало движения должно быть меньше начальной даты
        if((date + " " + time1) < (m_InitialDate + " " + m_InitialTime))
        {
            std::cout << "datetime > initial datetime\n";
            return false;
        }

        Append(Item(date, time1, time2, count));
        return true;
    }

    std::string getInitialDate() const
    {
        return m_InitialDate;
    }

    std::string getInitialTime() const
    {
        return m_InitialTime;
    }

    bool toFile(const std::string &fname) const
    {
        std::ofstream out(fname);
        if (!out.is_open())
        {
            return false;
        }

        out << m_InitialDate << ' ' << m_InitialTime << '\n';
        for(std::size_t i = 0; i < m_size; i++)
        {
            auto el = m_data[i];
            out << el.toString() << '\n';
        }

        return bool(out);
    }

    std::size_t getValue(const std::string &date, const std::string &time1, const std::string &time2) const
    {
        for(std::size_t i = 0; i < m_size; i++)
        {
            auto el = m_data[i];
            if(el.m_Date == date && el.m_BeginTime == time1 && el.m_EndTime == time2)
            {
                return el.m_Count;
            }
        }
        return 0;
    }

    double getAverage(const std::string &str) const
    {
        double S = 0;
        unsigned int count = 0;

        for(std::size_t i = 0; i < m_size; i++)
        {
            auto el = m_data[i];
            if(el.m_Date.substr(0, 7) == str)
            {
                S += el.m_Count;
                count ++;
            }
        }

        if(!count)
        {
            return -1;
        }

        return S / count;
    }

    double getAverage() const
    {
        double S = 0;
        unsigned int count = 0;

        for(std::size_t i = 0; i < m_size; i++)
        {
            auto el = m_data[i];
            S += el.m_Count;
            count ++;
        }

        if(!count)
        {
            return -1;
        }

        return S / count;
    }

    std::pair<std::size_t, std::string> getMaximum(const std::string &str) const
    {
        std::size_t max = 0;
        std::string date;

        for(std::size_t i = 0; i < m_size; i++)
        {
            auto el = m_data[i];
            if(el.m_Date.substr(0, 7) == str && el.m_Count > max)
            {
                max = el.m_Count;
                date = el.m_Date;
            }
        }

        return std::make_pair(max, date);
    }

    std::pair<std::size_t, std::string> getMaximum() const
    {
        std::size_t max = 0;
        std::string date;

        for(std::size_t i = 0; i < m_size; i++)
        {
            auto el = m_data[i];
            if(el.m_Count > max)
            {
                max = el.m_Count;
                date = el.m_Date;
            }
        }

        return std::make_pair(max, date);
    }


private:
    std::string m_InitialDate;
    std::string m_InitialTime;
    std::size_t m_capacity;
    std::size_t m_size;
    Item* m_data;
    

    void Append(const Item &el)
    {
        if(m_size < m_capacity)
        {
            m_data[m_size++] = el;
            return;
        }
        Item* newarr = new Item[m_capacity * 2]();
        m_capacity = m_capacity * 2;
        m_data[m_size] = el;
        std::copy(m_data, m_data + m_size++, newarr);
        delete[] m_data;
        m_data = newarr;
    }
};

