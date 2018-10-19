#ifndef CONTAINER_H_
#define CONTAINER_H_

template<typename T>
class Container {
	const int	maxItems;
	int			nItems;
	T*			items;
	static const int invalid = -1;
public:

	Container(int maxItems) : maxItems(maxItems), nItems(0), items(new T[maxItems])
	{
		for (int i = 0; i < maxItems; i++) items[i] = nullptr;
	}
	~Container()
	{
		while (nItems > 0) {
			remove(items[0]);
		}
		delete[] items;
	}

	int capacity() const { return maxItems; }

	int count() const { return nItems; }

	T at(int idx)
	{
		if (idx < 0 || nItems > maxItems) return nullptr;
		return items[idx];
	}

	T operator[](int idx)
	{
		return at(idx);
	}

	void add(T obj)
	{
		if (!obj) return;
		if (nItems >= maxItems) {
			delete obj;
			return;
		}
		for (int i = 0; i < maxItems; i++)
		{
			if (items[i] == nullptr) {
				items[i] = obj;
				nItems++;
				return;
			}
		}
		delete obj;
	}

	void remove(int i)
	{
		if (i == -1 || i < 0 || i >= maxItems) return;
		delete items[i];
		items[i] = nullptr;
		nItems--;
	}

	void remove(T obj)
	{
		int idx = indexOf(obj);
		if (idx == -1) {
			if (obj != nullptr)
				delete obj;
			return;
		}
		remove(idx);
	}

	int indexOf(T obj)
	{
		if (!obj) return -1;
		for (int i = 0; i < maxItems; i++) {
			if (items[i] == obj) return i;
		}
		return -1;
	}
};


#endif

