#pragma once

namespace utl {

template <typename Map, typename Function>
class map_aggregate_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    map_aggregate_iterator(Map& map, Function aggregator) : map_(map), aggregator_(aggregator) {}
    map_aggregate_iterator operator++(){ return *this; }
    map_aggregate_iterator operator*(){ return *this; }
    template<typename KeyValue>
    map_aggregate_iterator& operator=(KeyValue const& keyValue)
    {
        auto position = map_.find(keyValue.first);
        if (position != map_.end())
        {
            position->second = aggregator_(position->second, keyValue.second);
        }
        else
        {
            map_.insert(position, keyValue);
        }
        return *this;
    }
    
private:
    Map& map_;
    Function aggregator_;
};

template<typename Map, typename Function>
map_aggregate_iterator<Map, Function> map_aggregator(Map& map, Function aggregator)
{
    return map_aggregate_iterator<Map, Function>(map, aggregator);
}

}
