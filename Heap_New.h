/////PRIORITY QUEUE
class PriorityQueue
{
private:
    
    Node* front;

public:

    int size;

    PriorityQueue()
    {
        front=NULL;
	size = 0;
     
    }

    void enqueue(char t[],char N[],int Arrival,int burst,int Q=0){
      //prio is arrival time here
        Node* temp = new Node(t,N,Arrival,burst,Q);
        Node* curr;
        
        if(this->front==NULL || this->front->Arrival_T > Arrival){
            temp->next=front;
            front=temp;
        }
        else{
            curr=front;
            while(curr->next!=NULL && curr->next->Arrival_T <= Arrival){
                curr=curr->next;
            }
            temp->next=curr->next;
            curr->next=temp;
        }
	size++;
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
	size--;
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
