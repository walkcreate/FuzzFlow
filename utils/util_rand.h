#ifndef FUZZFLOW_UTIL_RAND_H
#define FUZZFLOW_UTIL_RAND_H

#include <iostream>
#include <random>

#include <cassert>
#include <memory>

#include <set>
#include <vector>
#include <map>
#include <unordered_map>

using std::set;
using std::vector;
using std::map;
using std::unordered_map;

namespace FuzzFlow {

double random_between_real(double lower, double upper);

unsigned int random_between_integer(unsigned int lower, unsigned int upper);

bool probability(double prob);

unsigned int random_container_index(unsigned int upper);

/// Randomly select a value from the map by key, excluding the specified exclusive_key.
///
template<typename T_key, typename T_value>
std::pair<T_key,T_value> random_unordered_map_element(const unordered_map<T_key, T_value>& the_map, T_key exclusive_key)
{
    assert("The size of map to random select element should be greater than 1" && (the_map.size() >= 1));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, the_map.size()-1);

    T_key result_key;
    T_value result_val;

    for (int i = 0; i < 32; i++) {
        int random_index = dist(mt);
        auto it = the_map.begin();
        std::advance(it, random_index);

        if (it->first != exclusive_key) {
            result_key = it->first;
            result_val = it->second;
            break;
        }
        else {
            //std::cout << "retry random choose" << std::endl;
        }
    }

    assert("Random map element in size times failed" && (!result_key.empty()));

    return {result_key, result_val};
}

template<typename T_key, typename T_value>
std::pair<T_key,T_value> random_map_element(const map<T_key, T_value, std::owner_less<>>& the_map)
{
    assert("The size of map to random select element should be greater than 1" && (the_map.size() >= 1));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, the_map.size()-1);

    T_key result_key;
    T_value result_val;

    int random_index = dist(mt);
    auto it = the_map.begin();
    std::advance(it, random_index);

    result_key = it->first;
    result_val = it->second;

    return {result_key, result_val};
}

template<typename T>
T random_set_element(const set<T> the_set)
{
    assert("The size of set to random select element should be greater than 1"
           && (the_set.size() >= 1));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, the_set.size()-1);

    int random_index = dist(mt);
    auto it = the_set.begin();
    std::advance(it, random_index);

    T result_element = *it;
    return result_element;
}

/// Randomly select an element from the set and return it.
/// The set contains weak_ptr, so the generic type of the set is set<T, std::owner_less<>>.
///
template<typename T>
T random_set_element(const set<T, std::owner_less<>> the_set)
{
    assert("The size of set to random select element should be greater than 1"
           && (the_set.size() >= 1));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, the_set.size()-1);

    int random_index = dist(mt);
    auto it = the_set.begin();
    std::advance(it, random_index);

    T result_element = *it;
    return result_element;
}

template<typename T>
T random_vector_element(const vector<T> the_vec)
{
    assert("The size of vector to random select element should be greater than 1"
            && (the_vec.size() >= 1));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, the_vec.size()-1);

    int random_index = dist(mt);
    auto it = the_vec.begin();
    std::advance(it, random_index);

    T result_element = *it;
    return result_element;
}

/// Randomly select an element from the vector and return it, along with the index of the selected element
///
template<typename T>
std::pair<int, T> random_vector_element_with_idx(const vector<T> the_vec)
{
    assert("The size of vector to random select element should be greater than 1"
           && (the_vec.size() >= 1));

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, the_vec.size()-1);

    int random_index = dist(mt);
    auto it = the_vec.begin();
    std::advance(it, random_index);

    T result_element = *it;

    return {random_index, result_element};
}

} /// end of namespace

#endif //FUZZFLOW_UTIL_RAND_H
