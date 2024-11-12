#include <stdio.h>
int main()
{
int referenceString[10], pageFaults = 0, m, n, s, pages, frames;
printf("\nEnter the number of Pages:\t");
scanf("%d", &pages);
printf("\n What are the total number of frames:\t");
{
scanf("%d", &frames);
}
printf("\nEnter reference string values:\n");
for(m=0;m<pages;m++)
{
printf("Value No. [%d]:\t", m + 1);
scanf("%d", &referenceString[m]);
}

int temp[frames];
for(m = 0; m < frames; m++)
{
temp[m] = -1;
}

for(m = 0; m < pages; m++)
{
s = 0;
for(n = 0; n < frames; n++)
{
if(referenceString[m] == temp[n])
{
s++;
pageFaults--;
}
}
pageFaults++;
if((pageFaults <= frames) && (s == 0))
{
temp[m] = referenceString[m];
}
else if(s == 0)
{
temp[(pageFaults - 1) % frames] = referenceString[m];
}

printf("\n");
for(n = 0; n < frames; n++)
{
printf("%d\t", temp[n]);
}
}
printf("\nTotal Page Faults:\t%d\n", pageFaults);
return 0;
}


//
// Inputs as follow
// Enter the number of Pages:    10
// What are the total number of frames:    3
// Enter reference string values:
// Value No. [1]:    7
// Value No. [2]:    0
// Value No. [3]:    1
// Value No. [4]:    2
// Value No. [5]:    0
// Value No. [6]:    3
// Value No. [7]:    0
// Value No. [8]:    4
// Value No. [9]:    2
// Value No. [10]:   3