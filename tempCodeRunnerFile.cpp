#include <iostream>
using namespace std;
class fifo {
int first; // position of first element
int ncrt; // current number of elements
int nmax; // maximum number of elements == the dimension of the array
double *elem; // pointer for allocation of memory
public:
fifo(int n=10); //initialize the list - sets nmax and allocates the necessary memory
//for the array elements
~fifo() // dealocate memory
{
delete []elem;
}
int is_full(); // tests if the list is full
int is_empty(); // tests if the list is empty
int push(double); // add a value in list - at the end of the list
int pop(double &); // extract a value from the list - the first element
void print(); // display the content of the list
};
fifo::fifo(int n)
{
 nmax=n;
 first=0;
 ncrt=0;
 elem=new double[nmax];
}
int fifo::is_full()
{
return (ncrt==nmax);
}
int fifo::is_empty()
{
return (ncrt==0);
}
int fifo::push(double k)
{
if (!is_full())
{
 elem[(first+ncrt)%nmax]=k;
 ncrt++;
 return 1;
}
else
{
 cout<<"The list is full!";
 return 0;
}
}
int fifo::pop(double &k)
{
 if (!is_empty())
 {
k=elem[first];
first=(first+1)%nmax;
ncrt--;
return 1;
 }
 else
 {
cout<<" The list is empty!";
return 0;
 }
}
void fifo::print()
{
if(!is_empty())
 {
 cout<<"\nThe list has "<<ncrt<<" elements";
 cout<<"\nThe elements are:";
 for(int i=0; i<ncrt; i++)
 cout<<"\n"<< elem[(first+i)%nmax];
 }
else
cout<<"The list is empty!";
cout<<endl;
}