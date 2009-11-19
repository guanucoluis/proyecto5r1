#ifndef FIR24_1_2_H
#define FIR24_1_2_H

extern FIRFilterStructure fir24_1_2Filter;

#endif /* FIR24_1_2_H */

/* The following C-code fragment demonstrates how to call the filter routine
#include "FIR_Filter.h"
#include "fir24_1_2.h"

// NUM_SAMPLES defines the number of samples in one block of input data.
// This value should be changed as needed for the application
#define NUM_SAMPLES 100

{
   // Declare input and output sample arrays.
   int  inSamples[NUM_SAMPLES], outSamples[NUM_SAMPLES];


   // Call the FIRFilterInit routine to zero out the delay line
   FIRFilterInit( &fir24_1_2Filter );

   // Call BlockFIRFilter for each block of input samples
   // This routine would normally be called inside a FOR or a DO-WHILE loop
   // Only one instance has been shown
   BlockFIRFilter( &fir24_1_2Filter, &inSamples, &outSamples, NUM_SAMPLES );
}
*/
