#ifndef DNAREPAIRER_H
#define DNAREPAIRER_H

#include "DNAElement.h"
#include "LinkedList.h"

class DNARepairer {
private:
    LinkedList<LinkedList<DNAElement>> DNAStorage;
    // DNA storage for all DNAs

public:
    LinkedList<LinkedList<DNAElement>> &getDNAStorage(void);

    /*
     * Returns the DNAStorage
     */

    void readFile(string filename);

    /*
     * Load the DNA samples to DNAStorage
     * TIP: don't forget to close the stream
     */

    void repairDNA(void);

    /*
     * Repair all DNA samples.
     */

    void printDNAStorage(void);
    /*
     * Prints the content of DNAStorage to console.
     */
};

#endif

