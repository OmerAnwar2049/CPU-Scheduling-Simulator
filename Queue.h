


class Queue
{

private:
	Node* front;
	Node* rear;
	int size;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
		size = 0;
	}

	void enqueue(Node &copy)
	{
		Node* new_node = new Node(copy);
		
		new_node->next = NULL;
		if (rear)
			rear->next = new_node;
		else
			front = new_node;
		rear = new_node;
		size++;
	}
	bool dequeue()
	{
		if (rear == NULL)
		{
			cout << "No Element Exists in the Queue to return" << endl;
			return false;
		}
		Node* temp = front;
		
		front = front->next;
		if (front == NULL)
		rear = NULL;
		delete temp;
		size--;
		return false;
	}



	void clear()
	{
		if (front != NULL)
		{
			Node* temp = front->next;
			while (temp)
			{
				delete front;
				front = temp;
				temp = temp->next;
			}
		}
		rear = NULL;
		front = NULL;
		size = 0;
	}
	void Print()
	{
		cout<<endl;
		for (Node* a = front; a != NULL; a = a->next)
		{
			a->Display();
			
		}
		
	}

	bool isEmpty()
	{
		if (size == 0)
			return true;
		return false;
	}



	void I_WT()
	{
        Node *curr;
        curr=front;
        if(front==NULL){
           // cout<<"Queue is empty";
	return;
        }
        else{
            while(curr!=NULL){
                
                curr->Waitng_time += 1;
                curr=curr->next;
		    }
		}
    	}
	

	Node*& getFront()
    	{
        return front;
    	}

	~Queue()
	{
		if (front != NULL)
		{
			Node* temp = front->next;
			while (temp)
			{
				delete front;
				front = temp;
				temp = temp->next;
			}
		}
	}



};

