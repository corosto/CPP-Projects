#pragma once
#include <iostream>

namespace fm
{
	template <class T>
	class Vector
	{
		//capacity - calkowity rozmiar wektora; current - liczba elementow w wektorze
		size_t capacity, current;
		T* data;
	public:

		class Const_iterator
		{
		protected:
			T* p;
		public:

			Const_iterator(T* p);
			Const_iterator& operator++();
			Const_iterator& operator++(int);
			Const_iterator operator+(const size_t var);
			Const_iterator& operator--();
			Const_iterator& operator--(int);
			Const_iterator operator-(const size_t var);
			bool operator != (const Const_iterator& it) const;
			bool operator == (const Const_iterator& it) const;
			const T& operator * () const;
			const T& operator -> () const;
		};

		class Iterator : public Const_iterator
		{
		public:

			Iterator(T* p);
			Iterator& operator++();
			Iterator operator++(int);
			Iterator operator+(const size_t var);
			Iterator& operator--();
			Iterator operator--(int);
			Iterator operator-(const size_t var);
			T& operator * ();
			T& operator -> ();
		};

		Vector<T>& operator = (const Vector& vector);		//operator  przypisania
		Vector<T>& operator = (Vector&& vector);				//operator przeniesienia
		bool operator == (const Vector& vector) const;		//operator porownania
		bool operator != (const Vector& vector) const;		//operator nierownosci
		const T& operator[](size_t index) const;					//operator indeksowy const
		T& operator[](const size_t index);							//operator indeksowy


		size_t Current() const noexcept;								//ilosc zajetych komorek w wektorze
		size_t Capacity() const noexcept;							//wielkosc wektora
		bool Empty() const noexcept;									//sprawdzanie czy wektor jest pusty


		Const_iterator Begin() const;
		Const_iterator End() const;
		Iterator Begin();
		Iterator End();


		Vector();																	//konstruktor bezargumentowy
		Vector(const Vector& vec);										//konstruktor kopiujacy
		Vector(Vector&& prev_vec) noexcept;						//konstruktor przenoszacy
		Vector(const size_t current, const T& value);			//konstruktor dwuargumentowy z wartoscia i wielkoscia wektora
		~Vector() noexcept;													//destruktor


		void Push_back(const T& value);							//dodaje element na koniec wektora
		void Push_here(const T& value, size_t index);		//dodaje element w wskazane miejsce
		void Delete_element(size_t index);							//usuwanie elementu na wskazanym miejscu; 'przesuwa element poza wektor
		void Delete_all();														//usuwanie wsyztskich elemetnow
		T* Find(const T& value);											//wyszukuje w jakim miejscu znajduje sie element

																						//operator wypisania
		friend std::ostream& operator <<(std::ostream& ostr, const Vector& vec)
		{
			for (size_t i = 0; i < vec.current; i++)
			{
				ostr << vec.data[i] << " ";
			}
			ostr << std::endl;
			return ostr;
		}
	};
}