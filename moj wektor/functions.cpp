#include "functions.h"

template<class T>
fm::Vector<T>::Const_iterator::Const_iterator(T* p) : p(p) {}


template<class T>
typename fm::Vector<T>::Const_iterator& fm::Vector<T>::Const_iterator::operator++()
{
	p++;
	return *this;
}


template<class T>
typename fm::Vector<T>::Const_iterator& fm::Vector<T>::Const_iterator::operator++(int)
{
	Const_iterator it = *this;
	++(*this);
	return it;
}


template<class T>
typename fm::Vector<T>::Const_iterator fm::Vector<T>::Const_iterator::operator+(const size_t var)
{
	for (size_t i = 0; i < var; i++)
	{
		p++;
	}
	return *this;
}


template<class T>
typename fm::Vector<T>::Const_iterator& fm::Vector<T>::Const_iterator::operator--()
{
	p--;
	return *this;
}


template<class T>
typename fm::Vector<T>::Const_iterator& fm::Vector<T>::Const_iterator::operator--(int)
{
	Const_iterator it = *this;
	--(*this);
	return it;
}


template<class T>
typename fm::Vector<T>::Const_iterator fm::Vector<T>::Const_iterator::operator-(const size_t var)
{
	for (size_t i = 0; i < var; i++)
	{
		p--;
	}
	return *this;
}


template<class T>
bool fm::Vector<T>::Const_iterator::operator == (const Const_iterator& it) const
{
	return p == it.p;
}


template<class T>
bool fm::Vector<T>::Const_iterator::operator != (const Const_iterator& it) const
{
	return p != it.p;
}


template<class T>
const T& fm::Vector<T>::Const_iterator::operator * () const
{
	return p->data;
}


template<class T>
const T& fm::Vector<T>::Const_iterator::operator -> () const
{
	return p->data;
}


template<class T>
fm::Vector<T>::Iterator::Iterator(T* p) : Const_iterator(p) {}


template<class T>
typename fm::Vector<T>::Iterator& fm::Vector<T>::Iterator::operator++()
{
	++(this->p);
	return *this;
}


template<class T>
typename fm::Vector<T>::Iterator fm::Vector<T>::Iterator::operator++(int)
{
	Iterator it = *this;
	++(*this);
	return it;
}


template<class T>
typename fm::Vector<T>::Iterator fm::Vector<T>::Iterator::operator+(const size_t var)
{
	for (size_t i = 0; i < var; i++)
	{
		++(this->p);
	}
	return *this;
}


template<class T>
typename fm::Vector<T>::Iterator& fm::Vector<T>::Iterator::operator--()
{
	--(this->p);
	return *this;
}


template<class T>
typename fm::Vector<T>::Iterator fm::Vector<T>::Iterator::operator--(int)
{
	Iterator it = *this;
	--(*this);
	return it;
}


template<class T>
typename fm::Vector<T>::Iterator fm::Vector<T>::Iterator::operator-(const size_t var)
{
	for (size_t i = 0; i < var; i++)
	{
		--(this->p);
	}
	return *this;
}


template<class T>
T& fm::Vector<T>::Iterator::operator * ()
{
	return this->p->data;
}


template<class T>
T& fm::Vector<T>::Iterator::operator -> ()
{
	return this->p->data;
}


//Operator przypisania
template<class T>
fm::Vector<T>& fm::Vector<T>::operator = (const Vector& vec)
{
	if (&vec != this)
	{
		current = vec.current;
		capacity = vec.capacity;
		delete[] data;
		data = new T[capacity];
		for (size_t i = 0; i < current; ++i)
		{
			data[i] = vec[i];
		}
	}
	return *this;
}


//Operator przeniesienia
template<class T>
fm::Vector<T>& fm::Vector<T>::operator = (Vector&& vec)
{
	if (&vec != this)
	{
		current = vec.current;
		capacity = vec.capacity;
		delete[] data;
		data = new T[capacity];
		data = vec.data;
		vec.data = nullptr;
		vec.~Vector();
	}
	return *this;
}


template<class T>
bool fm::Vector<T>::operator == (const Vector& vector) const
{
	if (Current() != vector.Current())
	{
		return false;
	}

	for (size_t i = 0; i < Current(); i++)
	{
		if (data[i] != vector[i])
		{
			return false;
		}
	}
	return true;
}


template<class T>
bool fm::Vector<T>::operator != (const Vector& vector) const
{
	return !(*this == vector);
}


template<class T>
const T& fm::Vector<T>::operator[](size_t index) const
{
	return data[index];
}


template<class T>
T& fm::Vector<T>::operator[](const size_t index)
{
	return data[index];
}


template<class T>
size_t fm::Vector<T>::Current() const noexcept
{
	return current;
}


template<class T>
size_t fm::Vector<T>::Capacity() const noexcept
{
	return capacity;
}


template<class T>
bool fm::Vector<T>::Empty() const noexcept
{
	return current == 0;
}


template<class T>
typename fm::Vector<T>::Const_iterator fm::Vector<T>::Begin() const
{
	return Const_iterator(data);
}


template<class T>
typename fm::Vector<T>::Const_iterator fm::Vector<T>::End() const
{
	return Const_iterator(data + current);
}


template<class T>
typename fm::Vector<T>::Iterator fm::Vector<T>::Begin()
{
	return Iterator(data);
}


template<class T>
typename fm::Vector<T>::Iterator fm::Vector<T>::End()
{
	return Iterator(data + current);
}


//konstruktor bezargumentowy
template<class T>
fm::Vector<T>::Vector() : capacity(1), current(0)
{
	data = new T[capacity];
}

//konstruktor dwuargumentowy z wartoscia i wielkoscia wektora
template<class T>
fm::Vector<T>::Vector(const size_t current, const T& value) : capacity(current), current(current)
{
	data = new T[current];
	for (size_t i = 0; i < current; i++)
	{
		data[i] = value;
	}
}

//konstruktor kopiujacy
template<class T>
fm::Vector<T>::Vector(const Vector& vec) : capacity(vec.capacity), current(vec.current)
{
	data = new T[vec.capacity];
	for (size_t i = 0; i < current; i++)
	{
		data[i] = vec.data[i];
	}
}

//konstruktor przenoszacy
template<class T>
fm::Vector<T>::Vector(Vector&& prev_vec) noexcept : current(prev_vec.current), capacity(prev_vec.capacity), data(prev_vec.data)
{
	prev_vec.data = nullptr;
	prev_vec.current = 0;
	prev_vec.capacity = 1;
}

//destruktor
template<class T>
fm::Vector<T>::~Vector() noexcept
{
	if (data != nullptr)
	{
		delete[] data;
	}
}



//dodaje element na koniec wektora
template<class T>
void fm::Vector<T>::Push_back(const T& value)
{
	if (current < capacity)
	{
		data[current] = value;
	}
	else
	{
		capacity *= 2;
		T* temp_data = new T[capacity];

		for (size_t i = 0; i < current; i++)
		{
			temp_data[i] = data[i];
		}

		temp_data[current] = value;
		delete[] data;
		data = temp_data;
	}
	current += 1;
}


//dodaje element w wskazane miejsce
template<class T>
void fm::Vector<T>::Push_here(const T& value, size_t index)
{
	if (current != capacity)
	{
		for (size_t i = current - 1; i >= index; i--)
		{
			data[i + 1] = data[i];
		}
		data[index] = value;
		current += 1;
	}
	else
	{
		capacity *= 2;
		T* temp_data = new T[capacity];

		for (size_t i = 0; i < current; i++)
		{
			temp_data[i] = data[i];
		}

		delete[] data;
		data = temp_data;
		fm::Vector<T>::Push_here(&value, index);
	}
}


//usuwanie elementu na wskazanym miejscu; 'przesuwa element poza wektor'
template<class T>
void fm::Vector<T>::Delete_element(size_t index)
{
	for (size_t i = index; i < current - 1; i++)
	{
		data[i] = data[i + 1];
	}
	current -= 1;
}


//usuwanie wszystkich elementow
template<class T>
void fm::Vector<T>::Delete_all()
{
	delete[] data;
	current = 0;
	capacity = 1;
	data = new T[capacity];
}


//wyszukuje w jakim miejscu znajduje sie element
template<class T>
T* fm::Vector<T>::Find(const T& value)
{
	for (size_t i = 0; i < current; i++)
	{
		if (data[i] == value)
		{
			return &data[i];
		}
	}
}