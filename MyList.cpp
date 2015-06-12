#include<iostream>
using namespace std;
template<class T> class MyList;
template<class T> MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2);
template<class T> MyList<T> operator + (const MyList<T> &l1, const T &item);
template<class T> ostream & operator<< (ostream &os, const MyList<T> &obj);


template<class T>
class MyList{
private:
	T *a;
	int size;
	int cur;
	void double_space();//When the list's space is not enough, double the space.
	void quicksort(T s[], int l, int r);
public:
	MyList(){
		size = 100;
		cur = -1;
		a = new T [size];
	}
	MyList(int num, const T &item);// make item repeats num times, then put it into list.
	MyList(const MyList &l);//copy other list l.
    MyList(T* arr, int len);//use one to the len elements of arr to make up a list.

	void push(const T &item);//put item to the end of MyList.
	T pop();//delete the last element of MyList and return it.
	void insert(int index, const T &item);//put item to the index place of MyList.
	void clean();//clean MyLIst.
	int get_size();// return the number of elements in MyList.
	void erase(int start, int end); //delete the start to the end elements of MYList.(include start and end)
	T get_item(int index);//return the NO.index element.
	MyList get_item(int start, int end);//return start to end of elements of MyList and allows to use negative number.
	int count(const T &item);//return the number of the elements that are the same as item.
	void remove(const T &item);//delete the first element the same as item in MyList.


	friend MyList operator + <>(const MyList &l1, const MyList &l2); //combine two MyLists.
    friend MyList operator + <>(const MyList &l1, const T &item); //the same as push(T item), return a new MyList.
	MyList &operator = (const MyList &l);//assignment
	MyList &operator += (const T &item);//the same as push(T item)
	MyList &operator += (const MyList &l);//add MyList l to the old MyList's end.
	T &operator [](int index);//return the NO.index element.
	friend ostream & operator<< <>(ostream &os, const MyList<T> &obj);//cout
	void sort(bool less=true);//a quicksort,if less=ture then from small to large, false the oppoes.
	void reverse();//reverse the elements in MyList.

	~MyList(){delete [] a;}
};
template<class T>
void MyList<T>::quicksort(T s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r;
		T x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x)  
				j--;
			if (i < j)
				s[i++] = s[j];
			while (i < j && s[i] < x)   
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		MyList<T>::quicksort(s, l, i - 1); 
		MyList<T>::quicksort(s, i + 1, r);
	}
}



template<class T>
void MyList<T>::double_space() //When the list's space is not enough, double the space.
{
	T *b;
	int i;
	b = new T[size];
	for (i = 0; i < size; ++i)
	{
		b[i] = a[i];
	}
	delete[] a;
	a = new T[2 * size];
	for (i = 0; i < size; ++i)
	{
		a[i] = b[i];
	}
	size = size * 2;
	delete[] b;
}

template<class T>
MyList<T>::MyList(int num, const T &item) // make item repeats num times, then put it into list.
{
	try
	{
		if(num<=0) throw num;
		size = num;
		cur = num - 1;
		a = new T[size];
		for (int i = 0; i < size; ++i)
		{
			a[i] = item;
		}
	}
	catch(int)
	{
		cout<<"num is less than 0.";
	}
}

template<class T>
MyList<T>::MyList(const MyList &l) //copy other list l.
{
	int i;
	size = l.size;
	cur = l.cur;
	a = new T[size];
	for (i = 0; i < cur + 1; ++i)
	{
		a[i] = l.a[i];
	}
}

template<class T>
MyList<T>::MyList(T* arr, int len) //use one to the len elements of arr to make up a list.
{
	try
	{
		if(len<=0) throw len;
		size = len;
		cur = len - 1;
		a = new T[size];
		for (int i = 0; i < size; ++i)
		{
			a[i] = arr[i];
		}
	}
	catch(int)
	{
		cout<<"len is less than 0.";
	}
}

template<class T>
void MyList<T>::push(const T &item) //put item to the end of MyList.
{
	T *b;
	int i;
	size++;
	cur++;
	b = new T[cur + 1];
	for (i = 0; i < cur; ++i)
	{
		b[i] = a[i];
	}
	b[cur] = item;
	delete[] a;
	a = new T[cur + 1];
	size = cur + 1;
	for (i = 0; i < size; ++i)
	{
		a[i] = b[i];
	}
	delete[] b;
}

template<class T>
T MyList<T>::pop() //delete the last element of MyList and return it.
{
	cur--;
	return a[cur + 1];
}

template<class T>
void MyList<T>::insert(int index, const T &item)//put item to the index place of MyList.
{
	try
	{
		if(index<0||index>cur) throw item;
		T *b;
		int i;
		size = cur + 1;
		b = new T[size + 1];
		for (i = 0; i < index; ++i)
		{
			b[i] = a[i];
		}
		b[index] = item;
		for (i = index; i < size; ++i)
		{
			b[i + 1] = a[i];
		}
		delete[] a;
		size = size + 1;
		a = new T[size];
		for (i = 0; i < size; ++i)
		{
			a[i] = b[i];
		}
		delete[] b;
		cur++;
	}
	catch(T)
	{
		cout<<"index is wrong.";
	}
}

template<class T>
void MyList<T>::clean() //clean MyLIst.
{
	cur = -1;
	delete[] a;
	size = 100;
	a = new T[100];
}

template<class T>
int MyList<T>::get_size() // return the number of elements in MyList.
{
	return cur+1;
}

template<class T>
void MyList<T>::erase(int start, int end) //delete the start to the end elements of MYList.(include start and end)
{
	try
	{
		if(start>cur||end>cur||end<start) throw 1;
		T *b;
		int i,x=0;
		cur = cur - end + start - 1;
		b = new T[cur + 1];
		for (i = 0; i < start; ++i)
		{
			b[x++] = a[i];
		}
		for (i = end; i < cur + 1; ++i)
		{
			b[x++] = a[i];
		}
		delete[] a;
		a = new T[cur + 1];
		for (i = 0; i < cur + 1; ++i)
		{
			a[i] = b[i];
		}
		delete[] b;
	}
	catch(int)
	{
		cout<<"start or end is wrong.";
	}
}

template<class T>
T MyList<T>::get_item(int index) //return the NO.index element.
{
	try
	{
		if(index<0||index>cur) throw index;
		return a[index];
	}
	catch(int)
	{
		cout<<"index is beyond the bound.";
	}
}

template<class T>
MyList<T> MyList<T>::get_item(int start, int end) //return start to end of elements of MyList and allows to use negative number.
{
	
	if (start < 0)	start += (cur+1);
	if (end < 0) end += (cur+1);
	try
	{
		if(start>cur||end>cur) throw 1;
		MyList<T> tmp;
		int i;
		if (start > end ) return tmp;
		else {
			while (tmp.size <= (end - start)){
				tmp.double_space();
			}
			for (i = start; i <=  end; ++i){
				++tmp.cur;
				tmp[tmp.cur] = a[i];
			}
		return tmp;
		}
	}
	catch(int)
	{
		cout<<"start or end is wrong.";
	}
}

template<class T>
int MyList<T>::count(const T &item) //return the number of the elements that are the same as item.
{
	int i,x=0;
	for (i = 0; i < cur + 1; ++i)
	{
		if (a[i] == item) x++;
	}
	return x;
}

template<class T>
void MyList<T>::remove(const T &item) //delete the first element the same as item in MyList.
{
	int i, index;
	for (i = 0; i < cur + 1; ++i)
	{
		if (a[i] == item)
		{
			index = i;
			break;
		}
	}
	for (i = index + 1; i < cur + 1; ++i)
	{
		a[i - 1] = a[i];
	}
	cur--;
	size = cur + 1;
}

template<class T>
MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2) //combine two MyLists.
{
	MyList<T> l;
	while (l.size < (l1.cur + l2.cur + 2)){
		l.double_space();
	}
	int i;
	l.size = l1.cur + l2.cur + 2;
	l.cur = l.size - 1;
	for (i = 0; i <= l1.cur; ++i)
	{
		l.a[i] = l1.a[i];
	}
	for (i = 0; i <= l2.size; ++i)
	{
		l.a[l1.cur + 1 + i] = l2.a[i];
	}
	return l;
}

template<class T>
MyList<T> operator + (const MyList<T> &l1, const T &item)  //the same as push(T item), return a new MyList.
{
	MyList<T> l;
	while (l.size < (l1.cur + 1)){
		l.double_space();
	}
	l.cur = l1.cur;
	int i;
	for (i = 0; i < l1.cur + 1; ++i)
	{
		l.a[i] = l1.a[i];
	}
	l.push(item);
	return l;
}

template<class T>
MyList<T> &MyList<T>::operator= (const MyList &l) //assignment
{
	while(size < l.cur + 1)
	{
		double_space();
	}
	cur = l.cur;
	int i;
	for (i = 0; i < l.cur + 1; ++i)
	{
		a[i] = l.a[i];
	}
	return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const T &item) //the same as push(T item)
{
	push(item);
	return *this;
}

template<class T>
MyList<T> &MyList<T>::operator += (const MyList &l) //add MyList l to the old MyList's end.
{
	while (size < cur + 2 + l.cur)
	{
		double_space();
	}
	int i;
	for (i = 0; i < l.cur + 1; ++i)
	{
		a[cur + i + 1] = l.a[i];
	}
	cur = cur + l.cur + 1;
	return *this;
}

template<class T>
T &MyList<T>::operator [](int index) //return the NO.index element.
{
	try
	{
		if(index<0||index>cur) throw index;
		return a[index];
	}
	catch(int)
	{
		cout<<"index is beyond the bound.";
	}
}

template<class T>
ostream & operator<<(ostream &os, const MyList<T> &obj) //cout
{
	int i;
	if(obj.cur==-1) os<<"["<<"]";
	else
	{
		os << "["<<obj.a[0];
		for (i = 1; i < obj.cur + 1; ++i)
		{
			os << "," << " " << obj.a[i];
		}
		os << "]";
	}
	return os;
}

template<class T>
void MyList<T>::sort(bool less) //a quicksort,if less=ture then from small to large, false the oppoes.
{
	quicksort(a, 0, cur);
	if (!less)
	{
		reverse();
	}
}

template<class T>
void MyList<T>::reverse()//reverse the elements in MyList.
{
	T *b;
	b = new T[cur + 1];
	int i;
	for (i = 0; i < cur + 1; ++i)
	{
		b[i] = a[cur-i];
	}
	delete[] a;
	a = new T[cur + 1];
	for (i = 0; i < cur + 1; ++i)
	{
		a[i] = b[i];
	}
	delete[] b;
}



int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
	// a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = []
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		cout<<a.get_item(i)<<endl;
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	
	return 0;
}
