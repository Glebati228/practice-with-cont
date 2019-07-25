#pragma once

#include <iostream>
#include "gErrors.h"
#include "gCont.h"

using namespace std;

#ifndef GINTARRAY
#define GINTARRAY

class gIntArray;
class gIntArrays;

class gIntArray : public IgContainble
{
public:
	explicit gIntArray(size_t s) : _size(s), _data(new int[s])
	{
		for(size_t i = 0; i < s; i++)
			_data[i] = 0;
	}

	gIntArray(gIntArray const & g) : _size(g._size), _data(new int[g._size])
	{
		for (size_t i = 0; i < g._size; i++)
		{
			_data[i] = g._data[i];
		}
	}

	~gIntArray()
	{
		delete[] _data;
	}

	gIntArray & operator=(gIntArray const & g)
	{
		if(this != &g)
		{
			delete[] _data;
			_size = g._size;
			_data = new int[_size];

			for (size_t i = 0; i < _size; i++)
			{
				_data[i] = g._data[i];
			}
		}
		return *(this);
	}

	gIntArray & operator +(gIntArray const & g) // TODO: override all operators
	{
		size_t _nSize = (g._size > _size) ? _size : g._size;

		for(size_t i = 0; i < _nSize; i++)
			_data[i] += g._data[i];

		return *this;
	}

	gIntArray & operator -(gIntArray const & g)
	{
		size_t _nSize = (g._size > _size) ? _size : g._size;

		for (size_t i = 0; i < _nSize; i++)
			_data[i] -= g._data[i];

		return *this;
	}

	gIntArray & operator *(gIntArray const & g)
	{
		size_t _nSize = (g._size > _size) ? _size : g._size;

		for (size_t i = 0; i < _nSize; i++)
			_data[i] *= g._data[i];

		return *this;
	}

	gIntArray & operator /(gIntArray const & g)
	{
		size_t _nSize = (g._size > _size) ? _size : g._size;

		for (size_t i = 0; i < _nSize; i++)
			_data[i] /= g._data[i];

		return *this;
	}

	//also very primitive checking on sorted array
	bool CheckSorting()
	{
		for (size_t i = 0; i < _size - 1; i++)
			if (_data[i] > _data[i + 1])
				return false;

		return true;
	}

	//Very primitive sorting
	//will be deleted soon
	void BubbleSortRaw() 
	{
		while (!CheckSorting())
		{
			for (size_t i = 0; i < _size - 1; i++)
				if (_data[i] > _data[i + 1])
					std::swap(_data[i], _data[i + 1]);
		}
	}

	gIntArray & BubbleSort() // TODO: Make Full optimized bubble sort (a little bit greater them Raw version) 
	{
		size_t k = _size - 1;
		int flag = 1;
		while (flag == 1)
		{
			flag = 0;
			for (size_t i = 0; i < k; i++)
				if (_data[i] > _data[i + 1])
				{
					flag = 1;
					std::swap(_data[i], _data[i + 1]);
				}
			--k;
		}
		return *this;
	}

	int * gBegin() const override 
	{
		return &_data[0];
	}

	int * gEnd() const override
	{
		return &_data[_size];
	}

	//Swap size add references on dynamic arrays
	void Swap(gIntArray & g)
	{
		const size_t _tempSize = _size;
		_size = g._size;
		g._size = _tempSize;

		int * const _tempData = _data;
		_data = g._data;
		g._data = _tempData;
	}

	int get(size_t i) const
	{
		if(i > _size)
			return OUT_OF_BOUNDARY;

		return _data[i];
	}

	int * getPtr(size_t i) 
	{
		if (i > _size)
			return &_data[_size];

		return &_data[i];
	}

	int setOnIndex(size_t &s, int &i)
	{
		if (s > _size)
			return OUT_OF_BOUNDARY;

		_data[s] = i;

		return SUCCESS_EXIT;
	}

	int setOnIndex(const size_t s, const int i)
	{
		if (s > _size)
			return OUT_OF_BOUNDARY;
		_data[s] = i;

		return SUCCESS_EXIT;
	}

	size_t size() const
	{
		return _size;
	};

	//gIntArrays ConvertToArrays(size_t x, size_t y) // TODO: fix problem with gIntArray class object // 2
	//{
	//	gIntArrays g(x, y);

	//	for (size_t i = 0; i < x; i++)
	//	{
	//		for (size_t k = 0; k < y; k++)
	//		{
	//			*(g.getPtr(x, y)) = _data[i * x + k];
	//		}
	//	}
	//	return g;
	//}

	void gClear()
	{
		for (size_t i = 0; i < _size; i++)
			_data[i] = 0;
	}

	inline void ShowArray()
	{
		printf("\n");
		for (size_t i = 0; i < _size; i++)
			printf("%d ", _data[i]);
		printf("\n");
	}

	void resize(size_t _tSize) // TODO: optimize this method (gIntArray not deleting (memory leak)) pog
	{
		gIntArray g(_tSize); 
		size_t _tempSize = (_tSize > _size) ? _size : _tSize;

		for (size_t i = 0; i < _tempSize; i++)
		{
			g._data[i] = _data[i];
		}
		Swap(g);
	}

private:
	size_t _size;
	int * _data;

};

//simple 2d array, in future will be maked a universal arr
class gIntArrays 
{
public:

	gIntArrays(size_t x, size_t y) : g_x(x), g_y(y), g_data(new int*[x])
	{
		for (size_t i = 0; i < x; i++)
		{
			g_data[i] = new int[y];

			for (size_t k = 0; k < y; k++)
				g_data[i][k] = 0;
		}
	}

	gIntArrays(gIntArrays const & g) : g_x(g.g_x), g_y(g.g_y), g_data(new int*[g.g_x])
	{
		for (size_t i = 0; i < g.g_x; i++)
		{
			g_data[i] = new int[g.g_y];
			for (size_t k = 0; k < g.g_y; k++)
			{
				g_data[i][k] = g.g_data[i][k];
			}
		}
	}

	gIntArrays & operator=(gIntArrays const & g)
	{
		if(this != &g)
		{
			for (size_t i = 0; i < g_x; i++)
				delete[] g_data[i];
			delete[] g_data;

			g_x = g.g_x;
			g_y = g.g_y;

			g_data = new int*[g.g_x];

			for (size_t i = 0; i < g.g_x; i++)
			{
				g_data[i] = new int[g.g_y];
				for (size_t k = 0; k < g.g_y; k++)
					g_data[i][k] = g.g_data[i][k];
			}
		}
		return *this;
	}

	//simple matrix operations
	gIntArrays & operator+(gIntArrays const & g)
	{
		size_t x = (g.g_x > g_x) ? g_x : g.g_x;
		size_t y = (g.g_y > g_y) ? g_y : g.g_y;

		for (size_t i = 0; i < x; i++)
			for (size_t k = 0; k < y; k++)
				g_data[i][k] += g.g_data[i][k];

		return *this;

	}

	gIntArrays & operator-(gIntArrays const & g)
	{
		size_t x = (g.g_x > g_x) ? g_x : g.g_x;
		size_t y = (g.g_y > g_y) ? g_y : g.g_y;

		for (size_t i = 0; i < x; i++)
			for (size_t k = 0; k < y; k++)
				g_data[i][k] -= g.g_data[i][k];

		return *this;

	}

	int SetOnIndex(size_t x, size_t y, int v)
	{
		if (x > g_x || y > g_y || x < 0 || y < 0)
			return OUT_OF_BOUNDARY;

		g_data[x][y] = v;
		return SUCCESS_EXIT;
	}

	size_t gSizeX() const
	{
		return g_x;
	}

	size_t gSizeY() const
	{
		return g_y;
	}

	void Swap(gIntArrays & g)
	{
		const size_t x = g_x;
		const size_t y = g_y;

		g_x = g.g_x;
		g_y = g.g_y;

		g.g_x = x;
		g.g_y = y;

		int ** const _temp = g_data;

		g_data = g.g_data;
		g.g_data = _temp;
	}

	void Resize(size_t x, size_t y)
	{
		gIntArrays g(x, y);

		size_t nx = (x > g_x) ? g_x : x;
		size_t ny = (y > g_y) ? g_y : y;

		for (size_t i = 0; i < nx; i++)
			for (size_t k = 0; k < ny; k++)
				g.g_data[i][k] = g_data[i][k];

		Swap(g);
	}

	gIntArray ConvertToArray()
	{
		gIntArray g(g_x * g_y);
		
		for(size_t i = 0; i < g_x; i++)
			for (size_t k = 0; k < g_y; k++)
				*(g.getPtr(i * g_x + k)) = g_data[i][k];

		return g;
	}

	inline gIntArrays const & FullSort()
	{
		//return this->ConvertToArray().BubbleSort().ConvertToArrays(g_x, g_y);
	}

	gIntArrays & LineSort() // TODO: release simple sort // 2
	{	
		size_t l = g_y - 1;
		int flag = 1;
		while (flag == 1)
		{
			flag = 0;
			for (size_t i = 0; i < g_x; ++i)
				for (size_t k = 0; k < l; ++k)
					if (g_data[i][k] > g_data[i][k + 1])
					{
						flag = 1;
						std::swap(g_data[i][k], g_data[i][k + 1]);
					}
			--l;
		}
		return this->ColumnSort();
	}

	gIntArrays & ColumnSort()
	{
		size_t l = g_x - 1;
		int flag = 1;
		while (flag == 1) 
		{
			flag = 0;
			for (size_t k = 0; k < g_y; ++k)
				for (size_t i = 0; i < l; ++i)
					if (g_data[i][k] > g_data[i + 1][k])
					{
						flag = 1;
						std::swap(g_data[i][k], g_data[i + 1][k]);
					}
			--l;
		}
		return *this;
	}

	void gClear() // TODO: make clear func // 2
	{
		for (size_t i = 0; i < g_x; i++)
			for (size_t k = 0; k < g_y; k++)
				g_data[i][k] = 0;
	}

	int get(size_t x, size_t y) const
	{
		if (x > g_x || y > g_y)
			return OUT_OF_BOUNDARY;

		return g_data[x][y];
	}

    int * getPtr(size_t x, size_t y)
	{
		if (x > g_x || y > g_y)
			return &g_data[g_x][g_y];

		return &g_data[x][y];
	}

	//temp func for debug
	void ShowArr()
	{
		printf("\n");
		for (size_t i = 0; i < g_x; i++) 
		{
			for (size_t k = 0; k < g_y; k++)
				printf("%d\t", g_data[i][k]);
			printf("\n");
		}
		printf("\n");
	}

	~gIntArrays() 
	{
		for(size_t i = 0; i < g_x; i++)
			delete[] g_data[i];

		delete[] g_data;
	}

private:
	size_t g_x;
	size_t g_y;
	int **g_data;

};

//universal container
template<typename T>
class gArray
{
public:
	gArray(const T& val_ = T())
		: val(val_)
	{

	}

	template <class U>
	gArray(const gArray<U>& rhs)
		: val(static_cast<T>(rhs.val))
	{

	}
private:
	T val;

	template <class U>
	friend class gArray;
};

// TODO: make universal containers such like this containers // 3
#endif // !GINTARRAY
