#include <iostream>
#include "extend.hpp"
#include "smith_waterman.hpp"

#define MIN(v1, v2) (((v1) > (v2)) ? (v2) : (v1))
#define MAX(v1, v2) (((v1) < (v2)) ? (v2) : (v1))

std::string _extend_and_score(AdjacentPair pair,
                             std::string query,
                             std::string data,
                             int match,
                             int mismatch,
                             int gap,
                             int minscore,
                             bool score,
                             bool printing)
{
    // find left most indices
    int dleftindex  = MIN(pair.dindex1, pair.dindex2);
    int qleftindex  = MIN(pair.qindex1, pair.qindex2);
    int drightindex = MAX(pair.dindex1, pair.dindex2);
    int qrightindex = MAX(pair.qindex1, pair.qindex2);

    // build string
    std::string qextended = query.substr(qleftindex, pair.length);
    std::string dextended = data.substr(dleftindex, pair.length);

    // extend left
    int qexindex = qleftindex;
    int dexindex = dleftindex;
    while (qexindex - 1 >= 0 && dexindex - 1 >= 0) {
		qexindex--; dexindex--;
        qextended = query[qexindex] + qextended;
        dextended = data[dexindex] + dextended;
        if (score
            && minscore > smith_waterman(qextended, dextended, match, mismatch, gap, true))
        {
            return "NULL";
        }
    }
	
    // extend left pair to the right
    qexindex = qleftindex + pair.length - 1;
    dexindex = dleftindex + pair.length - 1;
    while (qexindex + 1 < qrightindex) {
		qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + data[dexindex];
    }

    // extend right with gaps until qextended aligns with data
    while (dexindex + 1 < drightindex) {
		qexindex++; dexindex++;
        qextended = qextended + "-";
        dextended = dextended + data[dexindex];
    }

    // append the right pair
    qextended = qextended + query.substr(qrightindex, pair.length);
    dextended = dextended + data.substr(drightindex, pair.length);

    // extend right
    qexindex = qrightindex + pair.length - 1;
    dexindex = drightindex + pair.length - 1;
    while (qexindex + 1 < query.size() && dexindex + 1 < data.size()) {
		qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + data[dexindex];
        if (score
            && minscore < smith_waterman(qextended, dextended, match, mismatch, gap, true))
        {
            return "NULL";
        }
    }

    if (printing) {
        std::cout << "Data Ext:\t" << dextended << std::endl;
        std::cout << "Quer Ext:\t" << qextended << std::endl;
    }
    return qextended;
}

void test_extend()
{
    std::string query = "GTCTGAACTGAGC";
    std::string data  = "AGTCTGATGACTGGGGAACTCGA";
    std::string word1 = "TC";
    std::string word2 = "CT";

    int qindex1 = query.find(word1);
    int dindex1 = data.find(word1);
    int qindex2 = query.find(word2, qindex1 + word1.size());
    int dindex2 = data.find(word2, dindex1 + word1.size());

    AdjacentPair pair(word1, word2, dindex1, qindex1, dindex2, qindex2);

    std::cout << "Query:\t\t" << query << std::endl;
    std::cout << "Data:\t\t" << data << std::endl;

    int match = 2;
    int mismatch = -1;
    int gap = -1;
    int minscore = 6;
    bool score = true;
    bool printing = true;
    std::string result = _extend_and_score(pair,
                                           query,
                                           data,
                                           match, mismatch, gap,
                                           minscore,
                                           score,
                                           printing);
}
