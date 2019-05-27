// dtmap.h
// 因STL的map不支持在DLL中export, dtmap以vector为基础以支持map的操作, 但性能上只能达到vector的性能.

#pragma once

template<class KEY, class VALUE>
class odtpair 
{
public:
	typename KEY first;
	typename VALUE second;

public:
	odtpair(){};
	odtpair(const KEY& p_key, const VALUE& p_value)
	{
		first = p_key;
		second = p_value;
	}

	odtpair(const odtpair<KEY, VALUE>& p_odtpair)
	{
		first = p_odtpair.first;
		second = p_odtpair.second;
	}

	bool operator==(const odtpair<KEY, VALUE>& p_odtpair)
	{
		return (first == p_odtpair.first);
	}

	odtpair<KEY, VALUE>& operator=(const odtpair<KEY, VALUE>& p_odtpair)
	{
		first = p_odtpair.first;
		second = p_odtpair.second;
		return (*this);
	}
	
	bool operator<(const odtpair<KEY, VALUE>& p_odtpair)
	{
		return (first < p_odtpair.first);
	}
};

template<class KEY, class VALUE>
class dtmap
{
public:
	typedef odtpair<KEY, VALUE> value_type;
	typedef std::vector<value_type> vectormap;
	typedef vectormap::size_type size_type;
	typedef vectormap::const_iterator const_iterator;
	typedef vectormap::iterator iterator;
	typedef vectormap::reverse_iterator reverse_iterator;
	typedef vectormap::const_reverse_iterator const_reverse_iterator;
	typedef vectormap::reference reference;
	typedef vectormap::const_reference const_reference;

private:
	vectormap m_tvDatas;

public:
    iterator begin()
	{
		return m_tvDatas.begin();
	}

    const_iterator begin() const
	{
		return m_tvDatas.begin();
	}

    iterator end()
 	{
		return m_tvDatas.end();
	}

	const_iterator end() const
 	{
		return m_tvDatas.end();
	}

	reverse_iterator rbegin()
	{
		return m_tvDatas.rbegin();
	}

    const_reverse_iterator rbegin() const
	{
		return m_tvDatas.rbegin();
	}

    reverse_iterator rend()
	{
		return m_tvDatas.rend();
	}
    const_reverse_iterator rend() const
	{
		return m_tvDatas.rend();
	}

	size_type size() const
	{
		return m_tvDatas.size();
	}

    size_type max_size() const
	{
		return m_tvDatas.max_size();
	}
    
	bool empty() const
	{
		return m_tvDatas.empty();
	}

    VALUE& operator[](const KEY& p_key)
	{
		iterator l_it = find(p_key);

		if (l_it == m_tvDatas.end())
		{
			// Add new 
			value_type l_v;
			l_v.first = p_key;
			m_tvDatas.push_back(l_v);
			return m_tvDatas.back().second;
		}
		else
		{
			int l_iPos = l_it - m_tvDatas.begin();
			return m_tvDatas[l_iPos].second;
		}
	}

    void insert(const value_type& x)
	{
		if (find(x.first) == m_tvDatas.end())
		{
			m_tvDatas.push_back(x);
		}
	}
 
    void insert(const KEY& p_key, const VALUE& p_value)
	{
		if (find(p_key) == m_tvDatas.end())
		{
			value_type l_v(p_key, p_value);
			m_tvDatas.push_back(l_v);
		}
	}

    iterator erase(iterator it)
	{
		return m_tvDatas.erase(it);
	}

    iterator erase(iterator first, iterator last)
	{
		return m_tvDatas.erase(first, last);
	}

	void clear()
	{
		m_tvDatas.clear();
	}

	iterator find(const KEY& p_key)
	{
		iterator it;
		for (it = m_tvDatas.begin(); it != m_tvDatas.end(); it++)
		{
			if (p_key == (*it).first)
			{
				return it;
			}
			
		}
		return m_tvDatas.end();
	}

    const_iterator find(const KEY& p_key) const
	{
		for (const_iterator it = m_tvDatas.begin(); it != m_tvDatas.end(); it++)
		{
			if (p_key == (*it).first)
			{
				return it;
			}
		}
		return m_tvDatas.end();
	}

};
