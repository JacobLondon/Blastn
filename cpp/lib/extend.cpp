#include "extend.hpp"
#include "smith_waterman.hpp"

#define MIN(v1, v2) (((v1) > (v2)) ? (v2) : (v1))
#define MAX(v1, v2) (((v1) < (v2)) ? (v2) : (v1))

/* 
 *        ex) Query: G'TC'TGAA'CT'GAGC
 *            Data:  AG'TC'TGATGA'CT'GGGGAACTCGA
 *            Left Word:  'TC'
 *            Right Word: 'CT'
 * 
 *            Steps:
 *          1. Query: G'TC'                 -> score high enough? (extend left)
 *             Data:  G'TC'
 *          2. Query: G'TC'T                -> score high enough? (extend right)
 *             Data: G'TC'T
 *          3. Query: G'TC'TGAA             -> score high enough? (extend right more...)
 *             Data:  G'TC'TGAT
 *          4. Query: G'TC'TGAA--           -> score high enough? (add gaps)
 *             Data:  G'TC'TGATGA
 *          5. Query: G'TC'TGAA--'CT'       -> score high enough? (add right word)
 *             Data:  G'TC'TGATGA'CT'
 *          6. Query: G'TC'TGAA--'CT'GAGC   -> score high enough? (extend right more...)
 *             Data:  G'TC'TGATGA'CT'GGGG
 *          7. Done!
 */

Extended extend_and_score(AdjacentPair pair,
                          string query,
                          string data,
                          s32 match,
                          s32 mismatch,
                          s32 gap,
                          s32 minscore,
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
    string dextended = data.substr(dleftindex, pair.length);

    // extend left
	s32 qexindex = qleftindex;
	s32 dexindex = dleftindex;
    while (qexindex - 1 >= 0 && dexindex - 1 >= 0) {
		qexindex--; dexindex--;
        qextended = query[qexindex] + qextended;
        dextended = data[dexindex] + dextended;
        if (score && smith_waterman(qextended, dextended, match, mismatch, gap, true) < minscore)
        {
			return Extended{ Blastn::Invalid, -1 };
        }
    }

	// the left-most index in the database
	int dindex = dexindex;
	
    // extend left pair to the right
    qexindex = qleftindex + pair.length - 1;
    dexindex = dleftindex + pair.length - 1;
    while ((u32)qexindex + 1 < qrightindex) {
		qexindex++; dexindex++;
        qextended = qextended + query[qexindex];
        dextended = dextended + data[dexindex];
    }

    // extend right with gaps until qextended aligns with data
    while ((u32)dexindex + 1 < drightindex) {
		qexindex++; dexindex++;
        qextended = qextended + Blastn::SGap;
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
        if (score && smith_waterman(qextended, dextended, match, mismatch, gap, true) < minscore)
        {
			return Extended{ Blastn::Invalid, -1 };
        }
    }

    if (printing) {
        std::cout << "Data Ext:\t" << dextended << std::endl;
        std::cout << "Quer Ext:\t" << qextended << std::endl;
    }
	return Extended{ qextended, dindex };
}

Blastn::ExtendedSequenceMap extend_filter(Blastn::PairedSequenceMap& pairs,
										  Blastn::SequenceMap& query,
										  Blastn::SequenceMap& data,
										  s32 minscore,
										  s32 match,
										  s32 mismatch,
										  s32 gap)
{
	Blastn::ExtendedSequenceMap result;
	for (auto dname_quermap = pairs.begin(); dname_quermap != pairs.end(); ++dname_quermap) {
		Blastn::ExtendedPairsMap temp;
		for (auto qname_pairvec = dname_quermap->second.begin();
				  qname_pairvec != dname_quermap->second.end();
			    ++qname_pairvec)
		{
			for (auto adjacent_pair : qname_pairvec->second) {

				Extended ext = extend_and_score(adjacent_pair,
												query[qname_pairvec->first],
												data[dname_quermap->first],
												match, mismatch, gap, minscore, true, false);
				// the word scored above the minscore
				if (ext.extended_pair != Blastn::Invalid) {
					// no items in the vector of Extended pairs
					if (temp.find(qname_pairvec->first) == temp.end()) {
						temp[qname_pairvec->first] = vector<Extended>{ ext };
					}
					// at least one item in the vector of Extended pairs
					else {
						temp[qname_pairvec->first].push_back(ext);
					}
				}
			}
		}
		if (!temp.empty())
			result[dname_quermap->first] = temp;
	}
	return result;
}
