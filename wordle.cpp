#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


void make_words(string curr, int loc, const string& floating, const set<string>& dict, set<string>& res);
bool all_are_floating_letters(const string& word, const string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> res;
    make_words(in, 0, floating, dict, res);
    return res;
}

void make_words(string curr, int loc, const string& floating, const set<string>& dict, set<string>& res){
    // base
    if(loc == curr.size()){
        if(all_are_floating_letters(curr, floating) == true){
            if(dict.find(curr) != dict.end()){
                res.insert(curr);
            } 
        }
        return;
    }

    if(curr[loc] != '-'){
        make_words(curr, loc+1, floating, dict, res);
    }
    else{
        for(char c = 'a'; c <= 'z'; c++){
            curr[loc] = c;
            make_words(curr, loc+1, floating, dict, res);
        }
    }
}

bool all_are_floating_letters(const string& word, const string& floating){
    for(int x = 0; x < floating.length(); x++){
        bool we_found_it = false;
        for(int y = 0; y < word.length(); y++){
            if(floating[x] == word[y]){
                we_found_it = true;
                break;
            }
        }
        if(we_found_it == false){
            return false;
        }
    }
    return true;
}