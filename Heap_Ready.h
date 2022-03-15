/////PRIORITY QUEUE
class PriorityQueue
{
private:
    
    Node* front;

public:
    PriorityQueue()
    {
        front=NULL;

    }

    void enqueue(Node& copy){
      //prio is arrival time here
        Node* temp = new Node(copy);
        Node* curr;
        
        if(this->front==NULL || this->front->Burst > temp->Burst){
            temp->next=front;
            front=temp;
        }
        else{
            curr=front;
            while(curr->next!=NULL && curr->next->Burst <= temp->Burst){
                curr=curr->next;
            }
            temp->next=curr->next;
            curr->next=temp;
        }
    }
    
    bool dequeue(){
        int value=0;
        Node *temp;
        if(front==NULL){
            cout<<"Queue empty";
            return false;
        }
        else{
            temp=front;
	        
            front=front->next;
        }
        delete temp;
        return true;
    }
     
    bool isEmpty(){
        if(front==NULL){
            return true;
        }
        return false;
    }

    Node*& getFront()
    {
        return front;
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




    void Display(){
        Node *curr;
        curr=front;
        if(front==NULL){
            cout<<"Queue is empty";
        }
        else{
            while(curr!=NULL){
               
                curr->Display();
                curr=curr->next;
            }
        }
    }
};

//////////////////////////////////////////////////////////////
