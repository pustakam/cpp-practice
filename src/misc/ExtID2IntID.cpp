#include <cassert>
#include <utility>

#include "ExtID2IntID.hpp"

BucketElement**
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
ExtID2IntID::destroy_bucket_array(BucketElement** bucket_array, size_t bucket_array_size)
{
    for (size_t i = 0; i < bucket_array_size; ++i)
    {
        delete [] bucket_array[i];
    }
    delete [] bucket_array;
}

ExtID2IntID::ExtID2IntID()
    : bucket_size_{8},
    bucket_array_size_{1024},
    bucket_array_{}
{
    bucket_array_ = create_bucket_array(bucket_array_size_, bucket_size_);
}

ExtID2IntID::~ExtID2IntID()
{
    destroy_bucket_array(bucket_array_, bucket_array_size_);
}

size_t
ExtID2IntID::index(uint64_t extID, size_t bucket_array_size)
{
    return extID % bucket_array_size;
}

BucketElement*
ExtID2IntID::begin(size_t i)
{
    return bucket_array_[i];
}

const BucketElement*
ExtID2IntID::begin(size_t i) const
{
    return bucket_array_[i];
}

BucketElement*
ExtID2IntID::end(size_t i)
{
    return bucket_array_[i] + bucket_size_;
}

const BucketElement*
ExtID2IntID::end(size_t i) const
{
    return bucket_array_[i] + bucket_size_;
}

void
ExtID2IntID::insert(uint64_t extID, uint64_t intID)
{
    if (extID == 0 || intID == 0)
        return;

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

    // TODO: Have to rehash
    // exit(1);
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

