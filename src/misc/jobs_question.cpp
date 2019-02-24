#include <iostream>
#include <sstream>
#include <string>
#include <optional>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

struct Job
{
    size_t job_id;
    unsigned runtime_seconds;
    size_t next_job_id;
};

ostream& operator<<(ostream& os, Job& job)
{
    os << job.job_id << "," << job.runtime_seconds << "," << job.next_job_id;
    return os;
}

optional<Job> read_job(const string& job_str)
{
    Job job;
    istringstream is(job_str);
    if (!(is >> job.job_id))
        return nullopt;
    if (is.peek() == ',')
        is.ignore();
    if (!(is >> job.runtime_seconds))
        return nullopt;
    if (is.peek() == ',')
        is.ignore();
    if (!(is >> job.next_job_id))
        return nullopt;

    return make_optional(job);
}

using ChainsMap = map<size_t, vector<Job>>;

optional<ChainsMap> read_chains_map(istream& is)
{
    string s;
    map<size_t, size_t> chain_next_job_id_map;
    ChainsMap chains_map;
    
    while (getline(is, s))
    {
        if (s.empty() || s[0] == '#')
        {
        }
        else
        {
            optional<Job> maybe_job = read_job(s);
            if (!maybe_job)
            {
                return nullopt;
            }
            else
            {
                auto job = *maybe_job;
                auto it = find_if(chain_next_job_id_map.begin(), chain_next_job_id_map.end(),
                                    [&job](const auto& p)
                                    {
                                        return p.second == job.job_id;
                                    });

                if (it == chain_next_job_id_map.end())
                {
                    chain_next_job_id_map[job.job_id] = job.next_job_id;
                    chains_map.insert(make_pair(job.job_id, vector<Job>{{job}}));
                }
                else
                {
                    chain_next_job_id_map[it->first] = job.next_job_id;
                    chains_map[it->first].push_back(job);
                }
            }
        }
    }

    if (!all_of(chain_next_job_id_map.begin(), chain_next_job_id_map.end(),
                [](const auto& p)
                {
                    return p.second == 0;
                }))
    {
        return nullopt;
    }
    return make_optional(chains_map);
}

static int testme()
{
    auto maybe_chains_map = read_chains_map(cin);
    if (!maybe_chains_map)
    {
        cout << "Malformed Input" << endl;
        return 1;
    }
    auto chains_map = *maybe_chains_map;

    cout << "Chain summary" << endl;
    for (const auto& p : chains_map)
    {
        const auto& chain = p.second;
        cout << "-" << endl;
        for (const auto& job : chain)
        {
            cout << job.job_id << "->";
        }
        cout << endl;
        cout << "first_job_id: " << chain[0].job_id << endl;
        cout << "last_job_id: " << chain[p.second.size()-1].job_id << endl;
        auto sum = accumulate(chain.begin(), chain.end(), 0,
                                [](const auto& a, const auto& job)
                                {
                                    return a + job.runtime_seconds;
                                });
        cout << "runtime sum: " << sum << endl; 
        cout << "-" << endl;
    }

    return 0;
}

