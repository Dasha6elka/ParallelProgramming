class Node {
public:
	int field;
	class Node *ptr;
	friend class List;
};