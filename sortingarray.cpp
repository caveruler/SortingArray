#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;

void ShowArray(const int* array, int num_items);
void DebugPrintI(const int gArray[], int num_items);
void DebugPrintP(const int* cArray, int** sArray, int* gArray,
                 int numRows, int numCols, int pass);
void InsertSortedNonDec(int array[], int& used, int newValue);
bool match(const int array1[], const int array2[], int size);
void SortArray(int* gArray, int num_items);
void SeedRand();
int BoundedRandomInt(int lowerBound, int upperBound);

int main()
{
   int testCasesToDo = 990000,
       testCasesDone = 0,
       loSize = 1,
       hiSize = 20,
       loValue = 1,
       hiValue = 9999;
   int size,
       chkSize,
       newInt;
   int* gArray = 0;
   int* chkArray = 0;
   int* initArray = 0;

   // SeedRand(); // disabled for reproducible result
   do
   {
      ++testCasesDone;
      size = BoundedRandomInt(loSize, hiSize);
      gArray = new int [size];
      chkArray = new int [size];
      initArray = new int [size];
      chkSize = 0;
      for (int i = 0; i < size; ++i)
      {
         newInt = BoundedRandomInt(loValue, hiValue);
         InsertSortedNonDec(chkArray, chkSize, newInt);
         gArray[i] = newInt;
         initArray[i] = newInt;
      }
      SortArray(gArray, size);
      if ( !match(gArray, chkArray, size) )
      {
         cout << "Error detected for Test Case " << testCasesDone << ':' << endl;
         cout << "initial: ";
         ShowArray(initArray, size);
         cout << endl;
         cout << "ought2b: ";
         ShowArray(chkArray, size);
         cout << endl;
         cout << "outcome: ";
         ShowArray(gArray, size);
         cout << endl;
         exit(EXIT_FAILURE);
      }

      if (testCasesDone % 45000 == 0)
      {
            cout << "=============" << endl;
            cout << "array given : ";
            ShowArray(initArray, size);
            cout << endl;
            cout << "array sorted: ";
            ShowArray(gArray, size);
            cout << endl;
      }
      delete [] gArray;
      delete [] chkArray;
      delete [] initArray;
      gArray = chkArray = initArray = 0;
   }
   while (testCasesDone < testCasesToDo);
   cout << "\n================================" << endl;
   cout << "test program terminated normally" << endl;
   cout << "================================" << endl;

   return EXIT_SUCCESS;
}

// Function to seed the random number generator
// PRE:  none
// POST: The random number generator has been seeded.
void SeedRand()
{
   srand( (unsigned) time(NULL) );
}

// Function to generate a random integer between
// lowerBound and upperBound (inclusive)
// PRE:  lowerBound is a positive integer.
//       upperBound is a positive integer.
//       upperBound is larger than lowerBound
//       The random number generator has been seeded.
// POST: A random integer between lowerBound and upperBound
//       has been returned.
int BoundedRandomInt(int lowerBound, int upperBound)
{
   return ( rand() % (upperBound - lowerBound + 1) ) + lowerBound;
}

void InsertSortedNonDec(int array[], int& used, int newValue)
{
   int probeIndex = used;
   while (probeIndex > 0 && array[probeIndex - 1] > newValue)
   {
      array[probeIndex] = array[probeIndex - 1];
      --probeIndex;
   }
   array[probeIndex] = newValue;
   ++used;
}

void ShowArray(const int* array, int num_items)
{
   int maxInt, curInt;
   for (int i = 0; i < num_items; ++i)
   {
      curInt = array[i];
      if (i == 0)
         maxInt = curInt;
      else
         if (curInt > maxInt) maxInt = curInt;
   }
   int widthToSet = int( floor( log10(maxInt) ) + 1 ) + 1;
   for (int i = 0; i < num_items; ++i)
      cout << setw(widthToSet) << right << setfill('_') << array[i];
}

bool match(const int array1[], const int array2[], int size)
{
   for (int i = 0; i < size; ++i)
      if (array1[i] != array2[i]) return false;
   return true;
}

void DebugPrintI(const int gArray[], int num_items)
{
   cout << "\n=============";
   cout << "\ngArray @ 1st: ";
   ShowArray(gArray, num_items);
   cout << endl;
}

void DebugPrintP(const int* cArray, int** sArray, int* gArray,
                int numRows, int numCols, int pass)
{
   cout << "\narrays @ pass " << pass << ": ";
   cout << endl;
   int maxInt = -1, curInt;
   for (int i = 0; i < numRows; ++i)
   {
      for (int j = 0; j < cArray[i]; ++j)
      {
         curInt = sArray[i][j];
         if (maxInt == -1)
            maxInt = curInt;
         else
            if (curInt > maxInt) maxInt = curInt;
      }
   }
   int widthToSet = int( floor( log10(maxInt) ) + 1 ) + 1;
   for (int i = 0; i < numRows; ++i)
   {
      cout << "Row " << i << " -->" << setw(2) << setfill(' ')
           << cArray[i] << "x: ";
      for (int j = 0; j < cArray[i]; ++j)
         cout << setw(widthToSet) << right << setfill('_') << sArray[i][j];
      cout << endl;
   }
   cout << "\ngArray after: ";
   ShowArray(gArray, numCols);
   cout << endl;
}

void SortArray(int* gArray, int num_items)
{
   // to be implemented
}
