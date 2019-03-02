#ifndef __UINT128_HPP__
#define __UINT128_HPP__

#include <type_traits>
#include <cstdint>

class UInt128
{
public:
    UInt128()
        : lower_{}, upper_{}
    {}
    UInt128(uint64_t l, uint64_t u)
        : lower_{l}, upper_{u}
    {}

    template <typename T,
             typename = typename std::enable_if<std::is_integral<T>::value>::type>
    UInt128(T val)
        : lower_{static_cast<uint64_t>(val)}, upper_{}
    {}

    ~UInt128() = default;
    UInt128(const UInt128&) = default;
    UInt128& operator=(const UInt128&) = default;
    UInt128(UInt128&&) = default;
    UInt128& operator=(UInt128&&) = default;

    uint64_t lower()
    { return lower_;}

    uint64_t upper()
    { return upper_;}

    UInt128& operator+=(const UInt128& rhs)
    {
        uint64_t tmp = lower_ + rhs.lower_;
        if (tmp < lower_ && tmp < rhs.lower_)
        {
            // Overflow from adding lower_'s
            upper_ += rhs.upper_ + 1; 
        }
        else
        {
            upper_ += rhs.upper_; 
        }
        lower_ = tmp;

        return *this;
    }

    UInt128& operator-=(UInt128 rhs)
    {
        // Get 2's complement of rhs
        rhs.lower_ = ~(rhs.lower_);
        rhs.upper_ = ~(rhs.upper_);
        rhs += UInt128(UINT8_C(1));

        operator+=(rhs);

        return *this;
    }

    friend UInt128 operator+(UInt128 lhs, const UInt128& rhs) 
    {
        lhs += rhs;
        return lhs;
    }

    friend UInt128 operator-(UInt128 lhs, const UInt128& rhs) 
    {
        lhs -= rhs;
        return lhs;
    }

    friend bool operator==(const UInt128& lhs, const UInt128& rhs)
    {
        return lhs.lower_ == rhs.lower_ && lhs.upper_ == rhs.upper_;
    }
    friend bool operator!=(const UInt128& lhs, const UInt128& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const UInt128& lhs, const UInt128& rhs)
    {
        return std::tie(lhs.upper_, lhs.lower_) < std::tie(rhs.upper_, rhs.lower_);
    }
    friend bool operator>(const UInt128& lhs, const UInt128& rhs)
    {
        return rhs < lhs;
    }

private:
    uint64_t lower_;
    uint64_t upper_;
};

#endif // __UINT128_HPP__
