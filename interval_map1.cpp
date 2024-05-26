#include <iostream>
#include <map>

template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	void assign(K const& keyBegin, K const& keyEnd, V const& val) {
	    // Check if the interval is empty or invalid
	    if (!(keyBegin < keyEnd))
	        return;

	    auto firstElement = m_map.lower_bound(keyBegin); // find the first element >= keyBegin
	    auto lastElement = m_map.upper_bound(keyEnd);     // find the first element > keyEnd

	    // Special case: keyBegin is the smallest key
	    if (firstElement == m_map.begin() && !(keyBegin < m_map.begin()->first)) {
	        m_valBegin = val;
	        if (lastElement == m_map.end() || !(keyEnd < lastElement->first)) {
	            // The whole range is covered by the new value, so clear the map
	            m_map.clear();
	            return;
	        }
	    }

	    // Handle the case when the interval overlaps with existing intervals
	    if (firstElement != m_map.begin() && (--firstElement)->second == val) {
	        // Adjust the beginning of the current interval if it has the same value as val
	        if (firstElement->first < keyBegin) {
	            m_map.erase(++firstElement, lastElement);
	            firstElement = m_map.lower_bound(keyBegin);
	        }
	    } else {
	        // Insert a new interval if the beginning of the interval has a different value
	        if (firstElement != m_map.begin() && firstElement != m_map.end() && firstElement->first < keyBegin)
	            ++firstElement;
	        m_map.erase(firstElement, lastElement);
	    }

	    // Insert the new interval
	    m_map[keyBegin] = val;
	    if (lastElement != m_map.end() && !(keyEnd < lastElement->first) && lastElement->second != val)
	        m_map[keyEnd] = lastElement->second;
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};

int main() {
    // Instantiate an interval_map with some example values
    interval_map<int, char> M('A');
    M.assign(1, 3, 'B');
    M.assign(3, 6, 'A');

    // Test the operator[] function
    std::cout << " at key 2: " << M[4] << std::endl;
    std::cout << "Value at key 5: " << M[2] << std::endl;

    return 0;
}
