#include "extend.hpp"
#include "smith_waterman.hpp"
#include "../util/display.hpp"

namespace Blastn {

#define MIN(v1, v2) (((v1) > (v2)) ? (v2) : (v1))
#define MAX(v1, v2) (((v1) < (v2)) ? (v2) : (v1))

/* 
 *        ex) Query:     G'TC'TGAA'CT'GAGC
 *            Subject:  AG'TC'TGATGA'CT'GGGGAACTCGA
 *            Left Word:  'TC'
 *            Right Word: 'CT'
 * 
 *            Steps:
 *          1. Query:    G'TC'                 -> score high enough? (extend left)
 *             Subject:  G'TC'
 *          2. Query:    G'TC'T                -> score high enough? (extend right)
 *             Subject:  G'TC'T
 *          3. Query:    G'TC'TGAA             -> score high enough? (extend right more...)
 *             Subject:  G'TC'TGAT
 *          4. Query:    G'TC'TGAA--           -> score high enough? (add gaps)
 *             Subject:  G'TC'TGATGA
 *          5. Query:    G'TC'TGAA--'CT'       -> score high enough? (add right word)
 *             Subject:  G'TC'TGATGA'CT'
 *          6. Query:    G'TC'TGAA--'CT'GAGC   -> score high enough? (extend right more...)
 *             Subject:  G'TC'TGATGA'CT'GGGG
 *          7. Done!
 */

Extended extend_and_score(AdjacentPair pair,
                          string query,
                          string subject,
                          s32 match,
                          s32 mismatch,
                          s32 gap,
                          f32 ratio,
                          bool score,
                          bool printing)
{
    // find left most indices
    u32 dleftindex  = MIN(pair.dindex1, pair.dindex2);
    u32 qleftindex  = MIN(pair.qindex1, pair.qindex2);
    u32 drightindex = MAX(pair.dindex1, pair.dindex2);
    u32 qrightindex = MAX(pair.qindex1, pair.qindex2);

    // build string
    string qextended = query.substr(qleftindex, pair.length);
    string dextended = subject.substr(dleftindex, pair.length);

    // running Smith Waterman score
    s32 running_score = 0;

    // extend left
    s32 qexindex = qleftindex;
    s32 dexindex = dleftindex;
    while (qexindex - 1 >= 0 && dexindex - 1 >= 0) {
        qexindex--; dexindex--;
        qextended = query[qexindex] + qextended;
        dextended = subject[dexindex] + dextended;
        if (score) {
            running_score = smith_waterman(qextended, dextended, match, mismatch, gap, true);
            if (running_score < ratio * qextended.size() * match)
                return Extended{ Invalid, 0, 0, 0 };
        }
    }

    // the left-most index in the subject
    u32 dindex = (u32)dexindex;
    u32 qindex = (u32)qexindex;
    
    // extend left pair to the right
    qexindex = qleftindex + pair.length - 1;
    dexindex = dleftindex + pair.length - 1;
    while ((u32)qexindex + 1 < qrightindex && (u32)dexindex + 1 < drightindex) {
        qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + subject[dexindex];
    }

    // extend right with gaps until qextended aligns with subject
    while ((u32)dexindex + 1 < drightindex) {
        qexindex++; dexindex++;
        qextended = qextended + SGap;
        dextended = dextended + subject[dexindex];
    }

    // append the right pair
    qextended = qextended + query.substr(qrightindex, pair.length);
    dextended = dextended + subject.substr(drightindex, pair.length);

    // extend right
    qexindex = qrightindex + pair.length - 1;
    dexindex = drightindex + pair.length - 1;
    while ((s32)(qexindex + 1) < (s32)query.size() && (s32)(dexindex + 1) < (s32)subject.size()) {
        qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + subject[dexindex];
        if (score) {
            running_score = smith_waterman(qextended, dextended, match, mismatch, gap, true);
            if (running_score < ratio * qextended.size() * match)
                return Extended{ Invalid, 0, 0, 0 };
        }
    }

    if (printing) {
        std::cout << "Subject Ext:\t" << dextended << std::endl;
        std::cout << "Quer Ext:\t" << qextended << std::endl;
    }
    return Extended{ qextended, dindex, qindex, running_score };
}

ExtendedSequenceMap extend_filter(PairedSequenceMap& pairs,
                                  SequenceMap& query,
                                  SequenceMap& subject,
                                  s32 match,
                                  s32 mismatch,
                                  s32 gap,
                                  f32 ratio)
{
    ExtendedSequenceMap result;
    bool found = false;
    Progress progress{ pairs.size() };

    for (auto& dname_quermap : pairs) {
        ExtendedPairsMap temp;
        for (auto& qname_pairvec : dname_quermap.second) {
            for (auto adjacent_pair : qname_pairvec.second) {

                Extended ext = extend_and_score(adjacent_pair,
                                                query[qname_pairvec.first],
                                                data[dname_quermap.first],   // sw?    print?
                                                match, mismatch, gap, ratio, true, false);
                // the word scored above the minscore
                if (ext.extended_pair == Invalid)
                    continue;
                
                // check to see if the extended pair was recored yet
                found = false;
                for (auto& e : temp[qname_pairvec.first]) {
                    if (ext.dindex == e.dindex) {
                        found = true;
                        break;
                    }
                }
                // skip if the same pair was already found
                if (found)
                    continue;

                // no items in the vector of Extended pairs
                if (temp.find(qname_pairvec.first) == temp.end())
                    temp[qname_pairvec.first] = vector<Extended>{};
                temp[qname_pairvec.first].push_back(ext);
            }
        }
        if (!temp.empty())
            result[dname_quermap.first] = temp;

        progress.update();
    }
    return result;
}

} // Blastn