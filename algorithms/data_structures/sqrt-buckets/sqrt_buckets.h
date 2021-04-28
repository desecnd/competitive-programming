#ifndef SQRT_BUCKETS_H_8239482394
#define SQRT_BUCKETS_H_8239482394

#include <vector>
#include <cassert>
 
template<typename T>
class sqrt_buckets {
private:
    size_t bucket_size;
    size_t size;
 
    std::vector<T> value;
    std::vector<T> bucket_sum;
    std::vector<T> bucket_delta;
 
    // Propagate Delta changes in selected bucket
    inline void bucket_touch(size_t bucket_id) { 
        size_t bucket = bucket_size * bucket_id;
        for (size_t off = 0; off < bucket_size; off++)  
            value[bucket + off] += bucket_delta[bucket_id];
        bucket_delta[bucket_id] = 0;
    }
 
public:
 
    sqrt_buckets(int n) : 
        bucket_size(ceil(sqrt(n))), size(bucket_size * bucket_size), 
        value(size, 0), bucket_sum(bucket_size, 0), bucket_delta(bucket_size, 0) {}
    
    void update_range(size_t l, size_t r, T val) {
        size_t bucket_l = l / bucket_size;
        size_t bucket_r = r / bucket_size;
        
        bucket_touch(bucket_l);
        bucket_touch(bucket_r);
 
        if (bucket_r - bucket_l < 2) {
            for (size_t off = l; off <= r; off++) {
                value[off] += val;
                bucket_sum[off / bucket_size] += val;
            }
        }
        else {
            for (size_t bucket_id = bucket_l + 1; bucket_id < bucket_r; bucket_id++) {
                bucket_sum[bucket_id] += val * bucket_size;
                bucket_delta[bucket_id] += val;
            }
            
            for (size_t off = l; off/bucket_size == bucket_l; off++) {
                value[off] += val;
                bucket_sum[bucket_l] += val;
            }
 
            for (size_t off = r; off/bucket_size == bucket_r; off--) {
                value[off] += val;
                bucket_sum[bucket_r] += val;
            }
        }
    }
    
    T query_range(size_t l, size_t r) {
        size_t bucket_l = l / bucket_size;
        size_t bucket_r = r / bucket_size;
        
        bucket_touch(bucket_l);
        bucket_touch(bucket_r);
 
        T result = 0;
        if (bucket_r - bucket_l < 2) {
            for (size_t off = l; off <= r; off++) {
                result += value[off];
            }
        }
        else {
            for (size_t bucket_id = bucket_l + 1; bucket_id < bucket_r; bucket_id++) {
                result += bucket_sum[bucket_id];
            }
            
            for (size_t off = l; off/bucket_size == bucket_l; off++) {
                result += value[off];
            }
 
            for (size_t off = r; off/bucket_size == bucket_r; off--) {
                result += value[off];
            }
        }
        return result;
    }
};
 
void test() {
    sqrt_buckets<long long> buckets(8);

    buckets.update_range(1, 3, 26);
    buckets.update_range(3, 7, 80);
    buckets.update_range(3, 4, 20);
    
    assert(buckets.query_range(7, 7) == 80);
    
    buckets.update_range(4, 6, 14);
    
    assert(buckets.query_range(3, 7) == 508);
}

#endif