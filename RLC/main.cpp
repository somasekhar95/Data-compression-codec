#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

#define MAX_RLEN 1000

/* Returns the Run Length Encoded string for the
source string src */
char *encode(char *src)
{
int rLen;
char count[MAX_RLEN];
int len = strlen(src);

char *dest = (char *)malloc(sizeof(char)*(len*2 + 1));
int i, j = 0, k;
for(i = 0; i < len; i++)
{

	dest[j] = src[i];
	++j;
	rLen = 1;
	while(i + 1 < len && src[i] == src[i+1])
	{
	++rLen;
	++i;
	}

	sprintf(count, "%d", rLen);

	for(k = 0; *(count+k); k++, j++)
	{
	dest[j] = count[k];
	}
}

dest[j] = '\0';
return dest;
}


char * decode(char * dst,int len)
{
   int dec_len = strlen(dst);
   char * source = new char[len]();
   int i,j=0;
   int counter = 0;
   for(i=0;i<dec_len;++i)
   {
       source[j] = dst[i];
       char ch = source[j];
       ++j;
       ++i;
       char num = dst[i];
       counter = num - '1';
       //cout<<counter<<" ";
       for(;counter!=0;++j,--counter)
       {
           source[j] = ch;
           //printf("%c ", ch);
       }
   }
   //source[j] = '\0';
printf("%s", source);
return source;
}

/*driver program to test above function */
int main()
{
int length =0;
float compression = 0.0;
ifstream is ("text.dat", ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    cout<<"Input file length : "<<length<<endl;
    is.seekg (0, is.beg);

    // allocate memory:
    char * buffer = new char [length];

    is.read (buffer,length);
    is.close();

    char *res = encode(buffer);
    //printf("%s\n", res);

    char *original = decode(res,length);
    printf("%s\n", original);
    int len = strlen(res);
    // print content:

    char bFileName[] = "save.txt";
    ofstream  oFile(bFileName, ios::binary);
	// Saving the buffer iBuf in the file
	oFile.write(res,len);
	oFile.close();
	ifstream ofl ("save.txt", ifstream::binary);
    if (ofl) {
    ofl.seekg (0, is.end);
    int oplength = ofl.tellg();
	cout<<"Output file length : "<<oplength<<endl;
	compression = (float)oplength/(float)length;
	printf("Compression ratio : %.4f ",compression);
    }
    ofl.close();

	delete[] buffer;


  }

}

