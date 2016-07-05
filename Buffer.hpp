template <class bufType>
class Buffer {
public:
	Buffer();
	Buffer(size_t size);
	~Buffer();

	bool init(bufType* datas, size_t size);
	bool init(bufType value, size_t size);

	size_t getSize();

	// Position-related functions
	bool advance(size_t delta = 1);
	bool retreat(size_t delta = 1);

	bool moveTo(size_t pos);

	size_t getPos();

	// Value-related functions
	bool increment(size_t delta = 1);
	bool decrement(size_t delta = 1);

	bufType get();
	bufType getNextTo(signed long delta);
	bufType getAt(size_t pos);

	void set(bufType value);
	bool setAt(size_t pos, bufType value);


private:
	bufType* m_buf;
	size_t m_pos;
	size_t m_size;
};

template <class bufType>
Buffer<bufType>::Buffer()
: m_buf(nullptr)
, m_pos(0)
, m_size(0)
{

}

template <class bufType>
Buffer<bufType>::Buffer(size_t size)
: m_buf(new bufType[size])
, m_pos(0)
, m_size(size)
{

}

template <class bufType>
Buffer<bufType>::~Buffer()
{
	delete m_buf;
}

template <class bufType>
bool Buffer<bufType>::init(bufType* datas, size_t size)
{
	m_buf = new bufType[size];
	if (m_buf == nullptr)
		return false;
	for (size_t data = 0 ; data < size ; data++) {
		m_buf[data] = *datas;
		datas += sizeof(bufType);
	}
	m_size = size;
	return true;
}

template <class bufType>
bool Buffer<bufType>::init(bufType value, size_t size)
{
	m_buf = new bufType[size];
	if (m_buf == nullptr)
		return false;
	for (size_t data = 0 ; data < size ; data++) {
		m_buf[data] = value;
	}
	m_size = size;
	return true;
}

template <class bufType>
size_t Buffer<bufType>::getSize()
{
	return m_size;
}

template <class bufType>
bool Buffer<bufType>::advance(size_t delta)
{
	bool passedEnd = false;
	for (size_t i = 0 ; i < delta ; i++) {
		m_pos++;
		if (m_pos == 0 // Overflow
			|| m_pos >= m_size) {
			passedEnd = true;
			m_pos = 0;
		}
	}
	return !passedEnd;
}

template <class bufType>
bool Buffer<bufType>::retreat(size_t delta)
{
	bool passedStart = false;
	for (size_t i = 0 ; i < delta ; i++) {
		m_pos--;
		if (m_pos >= m_size) { // Underflow
			m_pos = m_size - 1;
		}
	}
	return !passedStart;
}

template <class bufType>
bool Buffer<bufType>::moveTo(size_t pos)
{
	if (pos < m_size) {
		m_pos = pos;
		return true;
	}

	m_pos = m_size - 1;
	return false;
}

template <class bufType>
size_t Buffer<bufType>::getPos()
{
	return m_pos;
}

template <class bufType>
bool Buffer<bufType>::increment(size_t delta)
{
	bufType old = m_buf[m_pos];
	m_buf[m_pos] += delta;
	return old <= m_buf[m_pos] || delta <= m_buf[m_pos];
}

template <class bufType>
bool Buffer<bufType>::decrement(size_t delta)
{
	bufType old = m_buf[m_pos];
	m_buf[m_pos] -= delta;
	return old >= delta;
}

template <class bufType>
bufType Buffer<bufType>::get()
{
	return m_buf[m_pos];
}

template <class bufType>
bufType Buffer<bufType>::getNextTo(signed long delta)
{
	return m_buf[m_pos + delta];
}

template <class bufType>
bufType Buffer<bufType>::getAt(size_t pos)
{
	return m_buf[pos];
}

template <class bufType>
void Buffer<bufType>::set(bufType value)
{
	m_buf[m_pos] = value;
}

template <class bufType>
bool Buffer<bufType>::setAt(size_t pos, bufType value)
{
	if (pos >= m_size)
		return false;
	m_buf[pos] = value;
	return true;
}
