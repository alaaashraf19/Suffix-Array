#include <iostream>

class SuffixArray {
struct suffixObject {
    int suffix;
    int rank;
    int nextRank;
    suffixObject(int _suffix, int _rank, int _nextRank): suffix(_suffix), rank(_rank), nextRank(_nextRank) {}
    suffixObject(): suffix(-1), rank(-1), nextRank(-1) {}
};
    char *input;
    suffixObject suffixarray[100];
    int rank[100];
    int nextRank[100];
    int lengthofinput=0;

  public:

    SuffixArray(char *inputString){
    this->input = inputString;
    while (input[lengthofinput] != '\0') {
        ++lengthofinput;
    }
}

    bool compareRanks(const suffixObject& a, const suffixObject& b) {
        if (a.rank == b.rank) {
            return a.nextRank < b.nextRank;
        }
        return a.rank < b.rank;
    }

    void mergeSort(suffixObject suffixarray[], int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;
            mergeSort(suffixarray, left, middle);
            mergeSort(suffixarray, middle + 1, right);
            merge(suffixarray, left, middle, right);
        }
    }

    void merge(suffixObject suffixarray[], int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        suffixObject L[n1], R[n2];
        for (int i = 0; i < n1; i++) {
            L[i] = suffixarray[left + i];
        }
        for (int i = 0; i < n2; i++) {
            R[i] = suffixarray[middle + 1 + i];
        }
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (compareRanks(L[i], R[j])) {
                suffixarray[k] = L[i];
                i++;
            } else {
                suffixarray[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            suffixarray[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            suffixarray[k] = R[j];
            j++;
            k++;
        }
    }



    void ConstructUsingPrefixDoubling() {

        for (int i=0;i<lengthofinput;i++) {

            rank[i]=input[i]-'A';
            if (i+1<lengthofinput) {
                nextRank[i]=input[i+1]-'A';
            }else {
                nextRank[i]=-1;
            }
            suffixarray[i]=suffixObject(i,rank[i],nextRank[i]);
        }

        mergeSort(suffixarray,0,lengthofinput-1);

        int origIndex[lengthofinput];

        bool norepeated;
        for (int k=4; !norepeated; k=k*2) {
            norepeated=true;
            int rank=0;
            int prev_rank=suffixarray[0].rank;
            int prev_next_rank=suffixarray[0].nextRank;
            suffixarray[0].rank=rank;
            origIndex[suffixarray[0].suffix]=0;

            for (int i = 1; i < lengthofinput; i++) {
                if (suffixarray[i].rank == prev_rank && suffixarray[i].nextRank == prev_next_rank) {
                    norepeated=false;
                    prev_rank=suffixarray[i].rank;
                    prev_next_rank=suffixarray[i].nextRank;
                    suffixarray[i].rank = rank;
                } else {
                    prev_rank=suffixarray[i].rank;
                    prev_next_rank=suffixarray[i].nextRank;
                    rank++;
                    suffixarray[i].rank = rank;
                }
                origIndex[suffixarray[i].suffix] = i;
            }
            for (int i=0;i<lengthofinput;i++) {
                int next=suffixarray[i].suffix+ k/2;
                if (next<lengthofinput) {
                    suffixarray[i].nextRank=suffixarray[origIndex[next]].rank;
                }else {
                    suffixarray[i].nextRank=-1;
                }
            }
            mergeSort(suffixarray,0,lengthofinput-1);
            // for (int i=0;i<lengthofinput;i++) {
            //     std::cout << suffixarray[i].suffix << "    "<<suffixarray[i].rank<<"  "<<suffixarray[i].nextRank<<std::endl;
            //
            // }
            // std::cout<<"//////////////////////////////////////////////////////////"<<std::endl;
        }

    }

    void Print() {
        for (int i=0;i<lengthofinput;i++) {
            std::cout << suffixarray[i].suffix << "    ";
        }
    }

};

int main() {
    SuffixArray t ("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8  10  5
    // The following is just illustration only
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // i      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
    // t      A  C  G  A  C  T  A  C  G  A  T  A  A  C  $
    // --------------------------------------------------
    // k=0    1  2  3  1  2  4  1  2  3  1  4  1  1  2  0
    // k=1    2  5  7  2  6  8  2  5  7  3  8  1  2  4  0
    // k=2    3  7 10  4  9 13  3  8 11  5 12  1  2  6  0
    // k=4    3  8 11  5 10 14  4  9 12  6 13  1  2  7  0
    // sa=   14 11 12  0  6  3  9 13  1  7  4  2  8 10  5
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}