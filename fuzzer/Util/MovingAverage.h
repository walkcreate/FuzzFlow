#ifndef FUZZFLOW_MOVINGAVERAGE_H
#define FUZZFLOW_MOVINGAVERAGE_H

#include <vector>
#include <cstdint>

using std::vector;

///
/// Computes the average of some value over the last N samples.
///

class MovingAverage {
public:
    uint32_t n;
    vector<double> last_n;
    double sum;
    uint32_t oldest = 0;
    uint32_t seen = 0;

    [[nodiscard]] double current_value() const
    {
        return sum / std::min<uint32_t>(seen, n);
    }

    explicit MovingAverage(const uint32_t n)
    {
        this->n = n;
        for (int i = 0; i < n; i++) {
            last_n.push_back(0.0);
        }
        this->sum = 0.0;
    }

    void add(const double val)
    {
        seen += 1;

        sum -= last_n[oldest];
        last_n[oldest] = val;
        sum += val;

        oldest = (oldest + 1) % n;
    }

    void add(const uint32_t val)
    {
        add(double(val));
    }
};


#endif //FUZZFLOW_MOVINGAVERAGE_H
