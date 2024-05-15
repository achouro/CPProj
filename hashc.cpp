#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;
using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    int ind;
};
//hash function 
class QueryProcessor {
    int bucket_count;
    // store all strings in one vector

    vector<list<string> > elems;

    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = (((hash * multiplier + s[i]) % prime)+prime)%prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(int bucket_count){
        this->bucket_count=bucket_count;
        list<string> l;
        for(size_t i=0;i<bucket_count; ++i){this->elems.push_back(l);}}
     


    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type == "check")
            cin >> query.ind;
        else
            cin >> query.s;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            if(query.ind<elems.size()){
                auto L=elems[query.ind];
                for(auto s:L){ cout<< s <<" ";}
                cout<<endl;}}
        else{
            size_t hash_index=hash_func(query.s);
            auto it=find(elems[hash_index].begin(),elems[hash_index].end(), query.s);

            if (query.type == "find")
                writeSearchResult(it != elems[hash_index].end());
            else if (query.type == "add") {
                if (it == elems[hash_index].end())
                    elems[hash_index].push_front(query.s);}
            else if (query.type == "del") {
                if (it != elems[hash_index].end())
                    elems[hash_index].erase(it);}}}                              


/*
            // use reverse order, because we append strings to the end
            for (int i = static_cast<int>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";

        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }
*/
    void processQueries() {
        int n;
        cin >> n;
        vector<Query> queries(n);
        for(int i=0; i<n; ++i)
            queries[i]=readQuery();
        for (int i = 0; i < n; ++i)
            processQuery(queries[i]);
        cout<<endl;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}

