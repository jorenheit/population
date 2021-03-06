#include <limits>

template <typename Population_t>
PopulationIterator__<Population_t> begin(Population_t &);

template <typename Population_t>
PopulationIterator__<Population_t> end(Population_t &);

template <typename Population_t>
class PopulationIterator__
{
    // Only these classes are allowed to construct iterators. 
    friend class PopulationIterator__<Population>; // for the implicit conversion non-const to const
    friend Population_t; // begin() and end()

    using Index_t = signed long long;

    enum class IteratorValue: Index_t { 
        BEGIN = -1,
        END = std::numeric_limits<Index_t>::max() 
    };

    Population_t &d_population;
    Index_t d_idx;

private: // Private constructors, only accessible to friends

    PopulationIterator__(Population_t &pop, IteratorValue val): 
        d_population(pop)
    {
        switch (val)
        {
        case IteratorValue::BEGIN:
            d_idx = d_population.d_first;
            break;
        case IteratorValue::END:
            d_idx = static_cast<Index_t>(IteratorValue::END);
            break;
        default:
            throw std::string("Default reached in constructor of PopulationIterator");
        }
    }

    PopulationIterator__(Population_t &pop, Agent const &agent): 
        d_population(pop),
        d_idx(pop.getIdx(agent))
    {
        if (d_idx == static_cast<Index_t>(IteratorValue::END) || !pop[d_idx].alive())
            throw std::string("Attempt to construct iterator to invalid agent.");
    }

public:
    PopulationIterator__ &operator++()
    {
        if (d_population.size() == 0 || d_idx >= d_population.d_last || 
            d_idx == static_cast<Index_t>(IteratorValue::END))
        {
            d_idx = static_cast<Index_t>(IteratorValue::END);
            return *this;
        }

        // Look for next alive agent
        while (!d_population[++d_idx]) {}

        return *this;
    }

    PopulationIterator__ &operator--()
    {
        if (d_idx == d_population.d_first)
            return *this;
        else if (d_population.size() == 0)
            d_idx = static_cast<Index_t>(IteratorValue::END);
        else if (d_idx == static_cast<Index_t>(IteratorValue::END))
            d_idx = d_population.d_last;
        else
            while (!d_population[--d_idx]) {}

        return *this;
    }

    PopulationIterator__ operator++(int)
    {
        PopulationIterator__ copy(*this);
        ++(*this);
        return copy;
    }

    PopulationIterator__ operator--(int)
    {
        PopulationIterator__ copy(*this);
        --(*this);
        return copy;
    }

    PopulationIterator__ &operator+=(int amount)
    {
        for (int i = 0; i != amount; ++i)
            ++(*this);

        return *this;
    }

    PopulationIterator__ &operator-=(int amount)
    {
        for (int i = 0; i != amount; ++i)
            --(*this);

        return *this;
    }

    bool operator==(PopulationIterator__<Population_t> const &other)
    {
        return d_idx == other.d_idx;
    }

    bool operator!=(PopulationIterator__<Population_t> const &other)
    {
        return d_idx != other.d_idx;
    }

    bool operator<(PopulationIterator__<Population_t> const &other)
    {
        return d_idx < other.d_idx;
    }

    bool operator>(PopulationIterator__<Population_t> const &other)
    {
        return d_idx > other.d_idx;
    }

    bool operator<=(PopulationIterator__<Population_t> const &other)
    {
        return d_idx <= other.d_idx;
    }

    bool operator>=(PopulationIterator__<Population_t> const &other)
    {
        return d_idx >= other.d_idx;
    }

    typename std::conditional<std::is_const<Population_t>::value, Agent const *, Agent *>::type
    operator->() const
    {
        return &d_population[d_idx];
    }

    typename std::conditional<std::is_const<Population_t>::value, Agent const&, Agent&>::type
    operator*() const
    { 
        if (d_idx == static_cast<Index_t>(IteratorValue::END))
            throw std::string("Trying to dereference end-iterator");

        return d_population[d_idx]; 
    }

    operator PopulationIterator__<Population_t const>()
    {
        return PopulationIterator__<Population_t const>(d_population, d_population[d_idx]);
    }
};

template <typename Population_t>
inline PopulationIterator__<Population_t> operator+(PopulationIterator__<Population_t> const &it, int amount)
{
    PopulationIterator__<Population_t> copy(it);
    return (copy += amount);
}

template <typename Population_t>
inline PopulationIterator__<Population_t> operator-(PopulationIterator__<Population_t> const &it, int amount)
{
    PopulationIterator__<Population_t> copy(it);
    return (copy -= amount);
}

template <typename Population_t>
inline PopulationIterator__<Population_t> operator+(int amount, PopulationIterator__<Population_t> const &it)
{
    return it + amount;
}

template <typename Population_t>
inline PopulationIterator__<Population_t> operator-(int amount, PopulationIterator__<Population_t> const &it)
{
    return it - amount;
}
