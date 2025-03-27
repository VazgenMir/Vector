#include <iostream>

template <typename T>
class _vector {
    T *m_data;
    T *m_end;
    T *m_capacity;
    
public:

    _vector();
    _vector(int size);
    ~_vector();

    void _push_back(const T& value);
    void _pop_back();
    size_t _size() const;
    size_t _capacity() const;
    bool _empty() const;
    T& operator[](int index);
    T& _at(int index);
    void _reserve(int new_capacity);
    void _shrink_to_fit();
    void _resize(int new_size);
    void _clear();
    T& _front();
    T& _back();

    class _iterator {
        T* _it;
    public:
        _iterator(T* it) : _it(it) {}
        _iterator& operator++() {++_it; return *this; }
        bool operator!=(const _iterator& other) { return _it != other._it; }
        T& operator*() { return *_it; }
        friend std::ostream& operator<<(std::ostream& os, const _iterator& it) {
            os << it._it;
            return os;
        }
    };

    class _reverse_iterator {
        T* _it;
    public:
        _reverse_iterator(T* it) : _it(it) {}
        _reverse_iterator& operator++() {--_it; return *this; }
        bool operator!=(const _reverse_iterator& other) { return _it != other._it; }
        T& operator*() { return *_it; }
        friend std::ostream& operator<<(std::ostream& os, const _reverse_iterator& it) {
            os << it._it;
            return os;
        }
    };

    _iterator _begin();
    _iterator _end();
    _reverse_iterator _rbegin();
    _reverse_iterator _rend();
};

template <typename T>
_vector<T>::_vector() {
    m_data = new T[0];
    m_end = m_data;
}

template <typename T>
_vector<T>::_vector(int size) {
    if(size <= 2) {
        m_data = new T[size]; 
    } else {
        int i = 2;
        while(i <= size) {
            if(i % 2 == 0 && i * 2 >= size) {
                m_data = new T[i * 2];
                m_capacity = m_data + i * 2;
                break;
            }
            i = i * 2;
        }
    }
    m_end = m_data + size;
}

template <typename T>
_vector<T>::~_vector() {
    delete[] m_data;
}

template <typename T>
typename _vector<T>::_iterator _vector<T>::_begin() {
    return _iterator(m_data);
}

template <typename T>
typename _vector<T>::_iterator _vector<T>::_end() {
    return _iterator(m_end);
}

template <typename T>
typename _vector<T>::_reverse_iterator _vector<T>::_rbegin() {
    return _reverse_iterator(m_end - 1);
}

template <typename T>
typename _vector<T>::_reverse_iterator _vector<T>::_rend() {
    return _reverse_iterator(m_data - 1);
}

template <typename T>
size_t _vector<T>::_size() const {
    return m_end - m_data;
}

template <typename T>
size_t _vector<T>::_capacity() const {
    return m_capacity - m_data;
}

template <typename T>
void _vector<T>::_reserve(int size) {
    if(size > _capacity()) {
        int count = _size();
        T* begin = new T[size]; 
        for(int i = 0;i < _size(); i++) {
            begin[i] = m_data[i];
        }
        delete m_data;
        m_data = begin;
        m_end = m_data + count;
        m_capacity = m_data + size; 
    }
}

template <typename T>
void _vector<T>::_shrink_to_fit() {
    int count = _size();
    T* begin = new T[_size()]; 
    for(int i = 0;i < _size(); i++) {
        begin[i] = m_data[i];
    }
    delete m_data;
    m_data = begin;
    m_end = m_data + count;
    m_capacity = m_end; 
}

template <typename T>
T& _vector<T>::operator[](int index) {
    return m_data[index];
}

template <typename T>
T& _vector<T>::_at(int index) {
    if(_size() > index) {
        return m_data[index];
    } else {
        std::cerr << "terminate called after throwing an instance of 'std::out_of_range'\n what():  vector::_M_range_check: __n (which is " << index << ") >= this->size() (which is " << index << ")\nAborted (core dumped)"<<std::endl;
        exit(EXIT_FAILURE);
    }
}

template <typename T>
void _vector<T>::_push_back(const T& value) {
    if(_size() + 1 <= _capacity()) {
        m_data[_size()] = value;
        m_end++;
    } else {
        if(_size() + 1 <= 2) {
            _reserve(_size() + 1); 
        } else {
            int i = 2;
            while(i <= _size() + 1) {
                if(i * 2 >= _size() + 1) {
                    _reserve(i * 2);
                }
                i = i * 2;
            }
            m_data[_size()] = value;
            m_end++;
        }
    }
}

template <typename T>
void _vector<T>::_pop_back() {
    m_data[_size() - 1] = 0;
    m_end--;
}

template <typename T>
void _vector<T>::_clear() {
    m_end = m_data;
}

template <typename T>
void _vector<T>::_resize(int number) {
    if(_size() < number) {
        if(number <= 2) {
            _reserve(number); 
        } else {
            int i = 2;
            while(i <= number) {
                if(i % 2 == 0 && i * 2 >= _size()) {
                    _reserve(i * 2);
                }
                i = i * 2;
            }
            m_end = m_data + number;
        }
    } else {
        m_end = m_data + number;
    }
}

template <typename T>
bool _vector<T>::_empty() const {
    return _size() == 0;
}

template <typename T>
T& _vector<T>::_front() {
    return m_data[0];
}

template <typename T>
T& _vector<T>::_back() {
    return m_data[_size() - 1];
}

int main() {
    _vector<int> vector(10);
    _vector<int>::_reverse_iterator it = vector._rbegin();
    std::cout << "capacity:" << vector._capacity() << std::endl;
    std::cout << "size:" << vector._size() << std::endl;
    vector._shrink_to_fit();
    std::cout << "capacity:" << vector._capacity() << std::endl;
    std::cout << "front:" << vector._front() << " back:" << vector._back() << std::endl;
    for(int i = 0; i < vector._size(); i++) {
        vector[i] = i;
    }
    std::cout << "begin:" << vector._rbegin() << " it:" << it << std::endl;
    for(it = vector._rbegin(); it != vector._rend(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
    return 0;
}