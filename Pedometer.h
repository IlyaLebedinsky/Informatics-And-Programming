# include <string>
# include <vector>
# include <stdexcept>
# include <sstream>
# include <fstream>
# include <utility>
# include <iterator>

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

            std::vector<std::string> vec{ std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>() };

            if(vec.size() != 4)
            {
                throw std::invalid_argument("Incorrect line " + line);
            }

            m_Date = vec[0];
            m_BeginTime = vec[1];
            m_EndTime = vec[2];
            m_Count = std::stoul(vec[3]);
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
        in >> m_InitialDate;
        in >> m_InitialTime;

        std::string line;
        while(std::getline(in, line))
        {
            if(!line.empty())
            {
            m_data.push_back(Item(line));
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
        m_InitialTime = time;
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
            std::cout<<"Incorrect data ="<<date<<'\n';
            return false;
        }

        if(!validateTime(time1))
        {
            std::cout<<"Incorrect time1 ="<<time1<<'\n';
            return false;
        }

        if(!validateTime(time2))
        {
            std::cout<<"Incorrect time2 ="<<time2<<'\n';
            return false;
        }
        //начало движение должно быть меньше завершения
        if(time1 > time2)
        {
            std::cout<<"time1 > time2\n";
            return false;
        }
        //начало движения должно быть меньше начальной даты
        if((date + " " + time1) < (m_InitialDate + " " + m_InitialTime))
        {
            std::cout<<"datetime > initial datetime\n";
            return false;
        }

        m_data.push_back(Item(date, time1, time2, count));
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
        for(const auto &el : m_data)
        {
            out << el.toString() << '\n';
        }

        return bool(out);
    }

    std::size_t getValue(const std::string &date, const std::string &time1, const std::string &time2) const
    {
		for(const auto &el : m_data)
		{
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
		
		for(const auto &el : m_data)
		{
			if(el.m_Date.substr(0,7) == str)
			{
				S += el.m_Count;
				count ++;
			}
		}
		
		if(!count)
		{
		    return -1;	
		}
		
		return S/count;
	}

    double getAverage() const
	{
		double S = 0;
		unsigned int count = 0;
		
		for(const auto &el : m_data)
		{
			S += el.m_Count;
		    count ++;
		}
		
		if(!count)
		{
		    return -1;	
		}
		
		return S/count;
	}
	
	std::pair<std::size_t,std::string> getMaximum(const std::string &str) const
	{
		std::size_t max = 0;
		std::string date;
		
		for(const auto &el : m_data)
		{
			if(el.m_Date.substr(0,7) == str && el.m_Count > max)
			{
				max = el.m_Count;
				date = el.m_Date;
			}
		}
				
		return std::make_pair(max, date);
	}

    std::pair<std::size_t,std::string> getMaximum() const
	{
		std::size_t max = 0;
		std::string date;
		
		for(const auto &el : m_data)
		{
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
    std::vector<Item> m_data;
};

