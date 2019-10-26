#include <cmath>

#include "hsp.hpp"
#include "../util/display.hpp"

namespace Blastn {

/**
 * Bit Score Calculation
 * https://www.ncbi.nlm.nih.gov/books/NBK21106/
 * 
 *  S' = (lambda * S - ln(kappa)) / ln(2)
 *  where S' = bit score
 *        S  = raw alignment score (smith waterman)
 *        lambda = scaling factor (Blastn input arg)
 *        kappa  = scaling factor (Blastn input arg)
 * 
 * 
 * E-Value Calculation
 * http://www.metagenomics.wiki/tools/blast/evalue
 * E = m*n / 2^S'
 * where m  = total length of all subjects combined
 *       n  = length of query
 *       S' = bit score
 *       E  = expected value
 * 
 */

static void calculate_score(HSP& hsp,
                            f32 lambda,
                            f32 kappa,
                            size_t subject_length,
                            size_t query_length)
{
    hsp.bitscore = (double)(lambda * hsp.sw_score - log(kappa)) / log(2);
    hsp.evalue   = (double)(subject_length * query_length) / (powf64(2, hsp.bitscore));
}

static void record_similarity(HSP& hsp, SequenceMap& subject)
{
    string subsequence = subject[hsp.subject_id].substr(hsp.subject_start, hsp.subject_end - hsp.subject_start);

    // find how many of each type there are
    for (size_t i = 0; i < subsequence.size(); i++) {
        if (hsp.extended_pair[i] == Blastn::CGap) {
            hsp.gaps++;
        }
        else if (hsp.extended_pair[i] == subsequence[i]) {
            hsp.matches++;
        }
        else {
            hsp.mismatches++;
        }
    }
    hsp.percentage_id = ((f32)hsp.matches / (f32)subsequence.size());
}

vector<HSP> format_hsps(ExtendedSequenceMap& extended_pairs,
                        SequenceMap& query,
                        SequenceMap& subject,
                        f32 lambda,
                        f32 kappa,
                        size_t subject_length)
{
    vector<HSP> result;
    Progress progress{ extended_pairs.size() };

    for (auto& sid_queries : extended_pairs) {
        for (auto& qid_epairs : sid_queries.second) {
            for (auto& epair : qid_epairs.second) {
                HSP hsp{
                    sid_queries.first,
                    qid_epairs.first,
                    epair.extended_pair,
                    epair.sindex,
                    epair.qindex,
                    epair.score
                };
                
                calculate_score(hsp, lambda, kappa, subject_length, query[qid_epairs.first].size());
                record_similarity(hsp, subject);
                result.push_back(hsp);
            }
        }
        progress.update();
    }
    return result;
}

} // Blastn