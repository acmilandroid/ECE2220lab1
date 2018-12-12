/* lab1.c
 * Basil Lin
 * basill
 * ECE 2220, Fall 2016
 * MP1
 *
 * NOTE:  You must update all of the following comments!
 *
 * Purpose: To review C programming by detecting input greater than specified correlation threshold and minimum correlation values
 *
 * Assumptions: User will input valid sample values that are numbers and not characters or stings
 *
 * Bugs: None
 *
 * See the ECE programming guide for requirements
 *
 * Are you unhappy with the way this code is formatted?  You can easily
 * reformat (and automatically indent) your code using the astyle
 * command.  If it is not installed use the Ubuntu Software Center to
 * install astyle.  Then in a terminal on the command line do
 *     astyle --style=kr lab1.c
 *
 * See "man astyle" for different styles.  Replace "kr" with one of
 * ansi, java, gnu, linux to see different options.  Or, set up your
 * own style.
 *
 * To create a nicely formated PDF file for printing install the enscript
 * command.  To create a PDF for "file.c" in landscape with 2 columns do:
 *     enscript file.c -G2rE -o - | ps2pdf - file.pdf
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//notice there is no semi-colon at the end of a #define
#define MAXLINE 100
#define MAXSAMPLES 500
#define STOPCOUNT 3
#define MINTHRESH 3

int main() {
    char line[MAXLINE];
    int corr_thresh = -1;
    int min_corr = -1; //minimum correlation value
    int pos = -1;
    int val = -1;
    int count = 0;
    int sample[MAXSAMPLES];
    int sample2[MAXSAMPLES]; //used to sort sample data
    int samp_pos = 0; //number of array positions
    int check_count = 0; //counts number of appearances
    int i; //loop counters
    int j;
    int k = 1;
    int status = 0; //status for printf
    int swap; //temp variable to hold swap values

    do{
        printf("\nWhat is the correlation threshold? ");

        /* You are REQUIRED to use fgets() and sscanf().
         * Use of scanf() is prohibited!
         */
        fgets(line, MAXLINE, stdin);
        sscanf(line, "%d", &corr_thresh);
        if (corr_thresh == -1) {
            printf("\nGoodbye\n\n");
            return 0;
        }
        printf("\nThe correlation threshold is equal to: %d\n", corr_thresh);

        // You have to fix this
        if (corr_thresh < MINTHRESH )
            printf("\nThat is not a valid correlation threshold!\n");
            // figure out if you exit the program and ask for a valid value
    } while (corr_thresh < MINTHRESH);

    // Next read the the minimum correlation value.
    do {
        printf("\nWhat is the minimum correlation value? ");
        fgets(line, MAXLINE, stdin);
        sscanf(line, "%d", &min_corr);
        if (min_corr == -1) {
            printf("\nGoodbye\n\n");
            return 0;
        }
        printf("\nThe minimum correlation value is equal to: %d\n", min_corr);
	if (min_corr <= 0)
		printf("\nThat is not a valid minimum correlation value. Please enter a positive number.\n");
    } while(min_corr <= 0);

    //loops until user enters -1 to cause break
    while (1 == 1) {
	//redeclaring variables for each loop
        pos = -1;
        val = -1;
        count = 0;
        samp_pos = 0; //number of array positions
        check_count = 0; //counts number of appearances
        k = 1; //loop counter

        // Next collect the samples.
        printf("\nPlease enter the sample values.\n");
        do {
            fgets(line, MAXLINE, stdin);
            sscanf(line, "%d", &sample[samp_pos]);
            if (sample[0] == -1) {
                printf("\nGoodbye\n\n");
                return 0;
            }
            if (sample[samp_pos] == 0)
                check_count++;
            else
                check_count = 0;
            if (check_count == STOPCOUNT)
                break;
            samp_pos++;
        } while (samp_pos < MAXSAMPLES); //stops loop when MAXSAMPLES reached

	//copies array
        for (i=0; i<samp_pos-2; i++) {
            sample2[i] = sample[i];
        }

	//sorts sample2 array
        for (i = 0; i < samp_pos-2; i++) {
            for (j = 0; j < samp_pos-2-i; j++) {
                if (sample2[j] > sample2[j+1]) {
                    swap = sample2[j];
                    sample2[j] = sample2[j+1];
                    sample2[j+1] = swap;
                }
            }
        }

        val = sample2[samp_pos-2]; //sets val to largest value in array

	//detection algorithm
        do {
            count = 0;
            if (val>=min_corr) {
                for (i=0; i<samp_pos-2; i++) {
                    if (sample[i] == val)
                        count++; //counts number of times val appears
                }
                if (count>=corr_thresh)
                    status = 1;
                else {
                    val = sample2[samp_pos-2-k];
                    k++;
                }
            }
            else {
                status = 2;
                break;
            }
        } while (count<corr_thresh);
	//finds pos
        for (i=0; i<samp_pos-2; i++) {
            if (sample[i] == val) {
                pos = i+1;
                break;
            }
        }

        //
        // Use one of the following prints
        // you must use exactly these prints and you cannot change the text
        if (status == 1)
            printf("\nWaveform detected at position %d with value %d and appears %d times\n", pos, val, count);
        if(status == 2)
            printf("\nNo waveform detected\n");
    }
    exit(0);
}

