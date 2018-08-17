#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;


struct treenodes
{
unsigned char data;
unsigned freq;
treenodes *leftchild, *rightchild;
treenodes(unsigned char data, unsigned freq)
{
leftchild = rightchild = NULL;
this->data = data;
this->freq = freq;
}
};

vector<string> codetable;
int symbolindex[512];
// Prints huffman codes from the root of Huffman Tree.
void codegen(struct treenodes* root, string str)
{
    if (!root)
     return;
    int counter = 0;
    if (root->data != '#')
    {
    cout << root->data << ": " << str << "\n";
    codetable.push_back(str);
    ++counter;
    symbolindex[root->data] = counter;
    //cout<<"index of symbols "<<symbolindex[root->data]<<endl;
    }
codegen(root->leftchild, str + "0");
codegen(root->rightchild, str + "1");

int index = 0;
unsigned char ch='\0';
ifstream finput("audio.dat", ifstream::in);
ofstream myfile;
 myfile.open ("save.txt",ios::out);
while (finput >> noskipws >> ch)
 {
 index = symbolindex[ch];
 cout << index;
 myfile << codetable[index];
 }
 myfile.close();
}

struct compare
{
bool operator()(treenodes* l, treenodes* r)
{
return (l->freq > r->freq);
}
};
void HuffmanCodes(unsigned char data[], int freq[], int size)
{
struct treenodes *leftchild, *rightchild, *top;
priority_queue<treenodes*, vector<treenodes*>, compare> heapsort;
for (int i = 0; i < size; ++i)
heapsort.push(new treenodes(data[i], freq[i]));
while (heapsort.size() != 1)
{

leftchild = heapsort.top();
heapsort.pop();
rightchild = heapsort.top();
heapsort.pop();

top = new treenodes('#', leftchild->freq + rightchild->freq);
top->leftchild = leftchild;
top->rightchild = rightchild;
heapsort.push(top);
}

codegen(heapsort.top(), "");


}

int main()
{
int occur[255] = {0};
unsigned char alpha;
int h=0;
unsigned char ch;
ifstream fin("text.dat", ifstream::in);
int Count = 0;
unsigned char arr1[512] = {};
int frequency[512] = {0};
while (fin >> noskipws >> ch)
 {
 ++occur[ch];
 printf("%c",ch);
 }

 for(h=0; h<255;++h)
 {
 alpha = '\0';
 if(occur[h]!=0)
 {
 alpha = h;
 arr1[Count] = alpha;
 cout<<arr1[Count]<<endl;
 cout<<"character "<<alpha<<" occured";
 frequency[Count] = occur[h];
 cout<<frequency[Count]<<endl;
 ++Count;
 }
 }


HuffmanCodes(arr1, frequency, Count);


return 0;
}
