#ifndef __EXTID2INTID__
#define __EXTID2INTID__

#include <stdint.h>
#include <stddef.h>

class ExtID2IntID
{
public:
    ExtID2IntID(size_t bucket_array_size, size_t bucket_size);
    ~ExtID2IntID();

    ExtID2IntID(const ExtID2IntID&) = delete;
    ExtID2IntID& operator=(const ExtID2IntID&) = delete;

    ExtID2IntID(ExtID2IntID&& other);
    ExtID2IntID& operator=(ExtID2IntID&&) = delete;

    void insert(uint64_t extID, uint64_t intID);
    void remove(uint64_t extID);
    uint64_t lookup(uint64_t extID);

private:
    struct BucketElement
    {
        uint64_t extID;
        uint64_t intID;
    };

    BucketElement* begin(size_t i);
    const BucketElement* begin(size_t i) const;

    BucketElement* end(size_t i);
    const BucketElement* end(size_t i) const;

    size_t next_pow_2(size_t n);
    BucketElement** create_bucket_array(size_t bucket_array_size, size_t bucket_size);
    void destroy_bucket_array(BucketElement** bucket_array, size_t bucket_array_size);

    size_t index(uint64_t extID, size_t bucket_array_size)
    { return extID % bucket_array_size; }

    size_t new_bucket_size(size_t old_bucket_size)
    { return 2 * old_bucket_size; }
    size_t new_bucket_array_size(size_t old_bucket_array_size)
    { return 2 * old_bucket_array_size; }

    void rehash();

private:
    size_t bucket_array_size_;
    size_t bucket_size_;
    BucketElement** bucket_array_;
};

#endif // __EXTID2INTID__
