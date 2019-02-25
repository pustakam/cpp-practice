#ifndef __EXTID2INTID__
#define __EXTID2INTID__

#include <stdint.h>
#include <stddef.h>

class ExtID2IntID
{
public:
    ExtID2IntID();
    ~ExtID2IntID();

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

    static BucketElement** create_bucket_array(size_t bucket_array_size, size_t bucket_size);
    static void destroy_bucket_array(BucketElement** bucket_array, size_t bucket_array_size);

    size_t index(uint64_t extID, size_t bucket_array_size) const
    { return extID % bucket_array_size; }

    size_t new_bucket_size(size_t old_bucket_size) const
    { return old_bucket_size + (old_bucket_size/2); }
    size_t new_bucket_array_size(size_t old_bucket_array_size) const
    { return old_bucket_array_size + (old_bucket_array_size/2); }

    void rehash();

private:
    size_t bucket_size_;
    size_t bucket_array_size_;
    BucketElement** bucket_array_;
};

#endif // __EXTID2INTID__
