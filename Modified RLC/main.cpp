#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;

#define MAX_RLEN 50

/* Returns the Run Length Encoded string for the
source string src */
char *encode(char *src,int block)
{
int rLen;
int len = strlen(src);
char compare[block] = {};
char *dest = (char *)malloc(sizeof(char)*(len*2 + 1));
int i, j = 0;
char src_blk [block] = {};
char dest_blk[block] = {};
int k,m,g,t,p;
/* traverse the input string one by one */
for(i = 0; i < len; i=i+block)
{
	/* Copy the first occurrence of the new character */
	for(k=0,m=0;k<block;++k)
    {
        m=i+k;
        src_blk[k] = src[m];
        dest_blk[k] = src_blk[k];
        //printf("current block %c",src_blk[k]);
    }
    for(g=0;g<block;++g)
    {
        dest[j+g] = dest_blk[g];
        //printf("%d",j+g);
    }

     j = j+block;
        //printf("\n");
	//if(dest[j]=='8')
    //{
     //   dest[j+1]='8';
      //  dest[j+2]='1';
    //}
    int next = i;
    next=next+block;
    int incr = 0;
    for(p=0;p<block;++p)
    {
        compare[p] = src[next+p];
    }
    //printf("current - %s  next - %s \n", src_blk,compare);
	/* Count the number of occurrences of the block */
    rLen = 1;
    k=i;
	   while(k+block<len && src_blk == compare)
            ++rLen;
      // printf("repeat %d",rLen);
	if(rLen>1)
    {
        dest[j]='8';
        //dest[j]=ch;
        ++j;
        dest[j]='0'+rLen;
        ++j;
    }
	//sprintf(count, "%d", rLen);
	/* Copy the count[] to destination */
	//for(k = 0; *(count+k); k++)
	//{
	 //   if(count[k]!=1)
      //  {
       //   dest[j] = count[k];
        //  ++j;
        //}
	//}
}

/*terminate the destination string */
dest[j] = '\0';
//printf("full script %s", dest);
return dest;
}


char * decode(char * dst,int len,int block)
{
   //printf("debug");
   int enc_len = strlen(dst);
   char * source = new char[len]();
   int i,j=0;
   for(i=0;i<enc_len;)//encoded file
   {
       char ch[block] = {};
       if(dst[i]!='8')
       {
        for (int p=0;p<block;++p)
        {
            source[j+p] = dst[i+p];
            //printf("%c,%c\n",dst[i],source[j]);
            ch[p] = source[j+p];
        }


       }
              //cout<<ch<<endl;
       if(dst[i]=='8')
       {
            ++i;
            int counter = 0;
            counter = dst[i] - '1';
            ++i;
            //cout<<counter<<endl;
            for(int p=0;counter>0;++p,++j,--counter)
                source[j+p] = ch[p];
       }
   }
   //source[j] = '\0';
return source;
}

/*driver program to test above function */
int main()
{
float compression = 0.0;
int block_size = 5;
ifstream is ("image.dat", ifstream::binary);
  if (is) {
    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    cout<<"Input file length : "<<length<<endl;
    is.seekg (0, is.beg);

    // allocate memory:
    char * buffer = new char [length];
    // read data as a block:
    is.read (buffer,length);
    is.close();

    char *res = encode(buffer,block_size);
    //printf("%s\n", res);

    int len = strlen(res);
    // print content:

    char bFileName[] = "save.txt";

	ofstream  oFile(bFileName, ios::binary);
	// Saving the buffer iBuf in the file
	oFile.write(res,len);
	oFile.close();
	ifstream ofl ("save.txt", ifstream::binary);
  if (ofl) {
    // get length of file:
    ofl.seekg (0, is.end);
    int oplength = ofl.tellg();
	cout<<"Output file length : "<<oplength<<endl;
	compression = (float)oplength/(float)length;
	printf("Compression ratio : %.4f ",compression);
  }
  ofl.close();

	delete[] buffer;
	char *original = decode(res,length,block_size);
    //printf("decode\n");
    //printf("%s\n", original);

  }

}

