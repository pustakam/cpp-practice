#include <utility>
#include <stdexcept>

#include "ExtID2IntID.hpp"

size_t
ExtID2IntID::next_pow_2(size_t n)
{
    size_t v{1};
    while (v <= n)
        v = v << 1;

    return v;
}

ExtID2IntID::BucketElement**
ExtID2IntID::create_bucket_array(size_t bucket_array_size, size_t bucket_size)
{
    BucketElement** bucket_array = new BucketElement*[bucket_array_size];
    for (size_t i = 0; i < bucket_array_size; ++i)
    {
        bucket_array[i] = new BucketElement[bucket_size]();
    }
    return bucket_array;
}

void
ExtID2IntID::destroy_bucket_array(ExtID2IntID::BucketElement** bucket_array, size_t bucket_array_size)
{
    for (size_t i = 0; i < bucket_array_size; ++i)
    {
        delete [] bucket_array[i];
    }
    delete [] bucket_array;
}

ExtID2IntID::ExtID2IntID(size_t bucket_array_size, size_t bucket_size)
    : bucket_array_size_{next_pow_2(bucket_array_size)},
    bucket_size_{next_pow_2(bucket_size)},
    bucket_array_{}
{
    if (bucket_array_size_ == 0 || bucket_size_ == 0)
        throw std::invalid_argument("bucket_array_size_ == 0 || bucket_size_ == 0");
    
    bucket_array_ = create_bucket_array(bucket_array_size_, bucket_size_);
}

ExtID2IntID::~ExtID2IntID()
{
    destroy_bucket_array(bucket_array_, bucket_array_size_);
}

ExtID2IntID::ExtID2IntID(ExtID2IntID&& other)
    : bucket_array_size_{other.bucket_array_size_},
    bucket_size_{other.bucket_size_},
    bucket_array_{std::move(other.bucket_array_)}
{
    other.bucket_array_size_ = 0;
    other.bucket_size_ = 0;
    other.bucket_array_ = nullptr;
}

ExtID2IntID::BucketElement*
ExtID2IntID::begin(size_t i)
{
    return bucket_array_[i];
}

const ExtID2IntID::BucketElement*
ExtID2IntID::begin(size_t i) const
{
    return bucket_array_[i];
}

ExtID2IntID::BucketElement*
ExtID2IntID::end(size_t i)
{
    return bucket_array_[i] + bucket_size_;
}

const ExtID2IntID::BucketElement*
ExtID2IntID::end(size_t i) const
{
    return bucket_array_[i] + bucket_size_;
}

void
ExtID2IntID::rehash()
{
    size_t old_bucket_size = bucket_size_;
    size_t old_bucket_array_size = bucket_array_size_;
    BucketElement** old_bucket_array = bucket_array_;

    bucket_size_ = new_bucket_size(old_bucket_size);
    bucket_array_size_ = new_bucket_array_size(old_bucket_array_size);
    bucket_array_ = create_bucket_array(bucket_array_size_, bucket_size_);

    for (size_t i = 0; i < old_bucket_array_size; ++i)
    {
        const BucketElement* element = old_bucket_array[i];
        const BucketElement* end = old_bucket_array[i] + old_bucket_size;
        while (element != end)
        {
            if (element->extID == 0)
                break;

            insert(element->extID, element->intID);
            ++element;
        }
    }

    destroy_bucket_array(old_bucket_array, old_bucket_array_size);
}

void
ExtID2IntID::insert(uint64_t extID, uint64_t intID)
{
    if (extID == 0 || intID == 0)
        return;

    size_t maybe_rehash_idx = index(extID, bucket_array_size_);
    BucketElement* last_element = end(maybe_rehash_idx) - 1;
    if (last_element->extID != 0)
    {
        rehash();
    }

    size_t idx = index(extID, bucket_array_size_);
    BucketElement* element = begin(idx);
    while (element != end(idx))
    {
        if (element->extID == 0 || element->extID == extID)
        {
            element->extID = extID;
            element->intID = intID;
            return;
        }
        ++element;
    }
}

void
ExtID2IntID::remove(uint64_t extID)
{
    if (extID == 0)
        return;

    size_t idx = index(extID, bucket_array_size_);

    BucketElement* element = begin(idx);
    while (element != end(idx))
    {
        if (element->extID == extID)
        {
            element->extID = 0;
            element->intID = 0;
            break;
        }
        ++element;
    }

    // If there is an element to remove
    if (element != end(idx))
    {
        // Find the last non zero element to swap with removed element 
        BucketElement* last_non_zero_element = end(idx) - 1;
        while (last_non_zero_element != element)
        {
            if (last_non_zero_element->extID != 0)
            {
                std::swap(*element, *last_non_zero_element);
                break;
            }
            --last_non_zero_element;
        }
    }
}

uint64_t
ExtID2IntID::lookup(uint64_t extID)
{
    size_t idx = index(extID, bucket_array_size_);
    const BucketElement* element = begin(idx);

    while (element != end(idx))
    {
        if (element->extID == extID)
            return element->intID;

        ++element;
    }

    return 0;
}

