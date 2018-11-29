

//class definition

template <typename T>
class Node {
public:
	Node();
	~Node();
	Node(const T& data);
	void setData(const T& data);
	T getData();
protected:
	T data;
};

//implementation

template <typename T>
Node<T> ::Node() {}
template <typename T>
Node<T> :: ~Node() {}

template <typename T>
Node<T> :: Node(const T& data) {
	this->data = data;
}

template <typename T>
void Node<T> ::setData(const T& data) {
	this->data = data;
}

template <typename T>
T Node<T> :: getData() {
	return data;
}
