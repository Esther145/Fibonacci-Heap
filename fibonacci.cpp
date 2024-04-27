#include <cmath>
#include <cstdlib>
#include <iostream>
#include <malloc.h>
using namespace std;
struct node 
{
	node* p;
    int degree; 
    int key; 
    int mark;
	node* left; 
	node* right; 
	node* child; 
    char c;
};
struct node* H = NULL;
int n_nodes = 0;
int found=0;
void display(struct node* heap)
{
	node* start=heap;
	if (start == NULL||n_nodes==0)
		cout << "The Heap is Empty" << endl;
	else {
		do
		{	
            if(start->p==NULL||start->p==start)
            {
                 cout<<"\nRoot Node:"<<start->key<<"->";

            }
            else
            {
                cout<<"\nNode:"<<start->key<<"-- Parent:"<<(start->p)->key<<endl;
            }
			if(start->child!=NULL&&start->child!=start&&start->p!=start->child)
			{
				display(start->child);	
			}
			start = start->right;
		} while (start!=heap&&start!=NULL);		
	}
}
void display_list(struct node* heap)
{
	node* start=heap;
	if (start == NULL||n_nodes==0)
		cout << "The Heap is Empty" << endl;
	else {
		do
		{	
           cout<<start->key<<" ";
		   
		   if(start->right==NULL)
		   {
			cout<<endl;
			start=heap->child;
		   }
		   else
		   {
			start=start->right;
		   }
		} while (start!=heap&&start!=NULL);		
		
	}

}
void fibHEAPlink(struct node* p2, struct node* p1)
{
	(p2->left)->right = p2->right;
	(p2->right)->left = p2->left;
	if (p1->right == p1)
		H = p1;
	p2->left = p2;
	p2->right = p2;
	p2->p = p1;
	if (p1->child == NULL)
		p1->child = p2;
	p2->right = p1->child;
	p2->left = (p1->child)->left;
	((p1->child)->left)->right = p2;
	(p1->child)->left = p2;
	if (p2->key < (p1->child)->key)
		p1->child = p2;
	p1->degree=(p1->degree)+1;
}

void Consolidate()
{
	int d;
	float actuald = (log(n_nodes)) / (log(2));
	int maxd = actuald;
	struct node* A[maxd+1];
	struct node* T[maxd+1];
	int flag=0;
	for (int i = 0; i <= maxd; i++)
	{
A[i] = NULL;
T[i]=NULL;
	}
		
	node* x = H;
	node* y;
	node* z;
	do 
    {
		for (int i = 0; i <= maxd; i++)
	{
T[i]=A[i];
	}
		d = x->degree;
		
		while (A[d] != NULL&&x!=A[d]) 
        {
			y = A[d];
			
			if (x->key > y->key) 
            {
				z = x;
				x = y;
				y = z;
			}
			if (y == H)
				H = x;
			fibHEAPlink(y, x);
			
			if (x->right == x)
				H = x;
			A[d] = NULL;
			d++;
		}
		A[d] = x;
		x = x->right;
		flag=0;
		for (int i = 0; i <= maxd; i++)
	{
		if(T[i]!=A[i])
		{
			flag=1;
		}
	}
	} while (flag==1);
    
    //Rebuilding the heap from the consolidated list of trees

    H = NULL;
	for (int j = 0; j <= maxd; j++) 
    {
		if (A[j] != NULL) 
        {
			A[j]->left = A[j];
			A[j]->right = A[j];
			if (H != NULL) 
            {
				(H->left)->right = A[j];
				A[j]->right = H;
				A[j]->left = H->left;
				H->left = A[j];
				if (A[j]->key < H->key)
					H = A[j];
			}
			else 
            {
				H = A[j];
			}
			if (H == NULL)
				H = A[j];
			else if (A[j]->key < H->key)
				H = A[j];
		}
	}
    
	
}
void fib_heap_insert(int x)
{
	struct node* node_new = new node();
    node_new->p = NULL;
    node_new->degree = 0;
	node_new->key = x;
	node_new->mark = 0;
	node_new->left = node_new;
	node_new->right = node_new;
	node_new->child = NULL;
	if (H == NULL) 
    {
        	H = node_new;
            //H.min=x
	}
	else 
    {
        (H->left)->right = node_new;
		node_new->right = H;
		node_new->left = H->left;
		H->left = node_new;
		if (node_new->key < H->key)
        {
            H = node_new;
        }
	}
	n_nodes++;
    
}

void Extract_min()
{
	if (H == NULL)
		cout << "The heap is empty" << endl;
	else 
    {
		node* z = H;
		node* pntr;
		pntr = z;
		node* x = NULL;
		if (z->child != NULL) 
        {

			x = z->child;
			do 
            {
				pntr = x->right;
				(H->left)->right = x;
				x->right = H;
				x->left = H->left;
				H->left = x;
				if (x->key < H->key)
					H = x;
				x->p = NULL;
				x = pntr;
			} while (pntr != z->child);
		}
		(z->left)->right = z->right;
		(z->right)->left = z->left;
		H = z->right;
		if (z == z->right && z->child == NULL)
			H = NULL;
		else 
        {
			H = z->right;
			cout<<"\nDeleted: Going to consolidate\n";
			Consolidate();
		}
		n_nodes--;
		cout<<"\nExtracted\n";
	}
}
// Cutting a node in the heap to be placed in the root list
void Cut(struct node* x, struct node* y)
{
	if (x == x->right)
		y->child = NULL;

	(x->left)->right = x->right;
	(x->right)->left = x->left;
	if (x == y->child)
		y->child = x->right;

	y->degree = y->degree - 1;
	x->right = x;
	x->left = x;
	(H->left)->right = x;
	x->right = H;
	x->left = H->left;
	H->left = x;
	x->p = NULL;
	x->mark = 1;
    /*
    CUT(H, x, y)
        1 remove x from the child list of y, decrementing y.degree
        2 add x to the root list of H
        3 x.p equal to  NIL
        4 x.mark = FALSE
    */
}

// Recursive cascade cutting function
void Cascase_cut(struct node* y)
{
	node* z = y->p;
	if (z != NULL) {
		if (y->mark == 0) {
			y->mark = 1;
		}
		else {
			Cut(y, z);
			Cascase_cut(z);
		}
	}
}
void Decrease_key(struct node* x, int k)
{
	if (H == NULL)
		cout << "HEAP EMPTY!!!" << endl;

	if (x == NULL)
		cout << "No NODE LIKE THAT IN THE HEAP!!!" << endl;

	x->key = k;

	struct node* y = x->p;
	if (y != NULL && x->key < y->key) 
    {
		Cut(x, y);
		Cascase_cut(y);
	}
	if (x->key < H->key)
		H = x;
}

void dec(struct node* H, int old_key, int new_key )
{
	struct node* hit = NULL;
	node* x = H;
	x->c = 'Y';
	node* hit_ptr = NULL;
	int flag;
	if (x->key == old_key) 
    {

		hit_ptr = x;
		x->c = 'N';
		hit = hit_ptr;
		Decrease_key(hit, new_key);
		found=1;
		
	}
	if (hit_ptr == NULL) {
		if (x->child != NULL)
			dec(x->child, old_key, new_key);
		if ((x->right)->c != 'Y')
			dec(x->right, old_key, new_key);
	}
	x->c = 'N';
	hit = hit_ptr;
	
}
void Deletion(int k)
{
	if (H == NULL)
		cout << "The heap is empty" << endl;
	else {
	

		found=0;
		dec(H, k, 0);
	
		if(found==1)
		{
			cout<<"Key found";
			Extract_min();
			
		}
		else
		{
			cout<<"Key NOT found";
		}
	
		
	}
}


int main()
{
	cout << "Creating an initial heap" << endl;
	
	
	
	/*
fib_heap_insert(12);
	fib_heap_insert(34);
	fib_heap_insert(9);
	fib_heap_insert(3);
	fib_heap_insert(98);
	fib_heap_insert(104);
	fib_heap_insert(4);
	fib_heap_insert(6);
	fib_heap_insert(2);
	fib_heap_insert(5);
	fib_heap_insert(7);
	fib_heap_insert(8);
	fib_heap_insert(18);




fib_heap_insert(912);
	fib_heap_insert(934);
	fib_heap_insert(99);
	fib_heap_insert(93);
	fib_heap_insert(998);
	fib_heap_insert(9104);
	fib_heap_insert(94);
	fib_heap_insert(96);
	fib_heap_insert(92);
	fib_heap_insert(95);
	fib_heap_insert(97);
	fib_heap_insert(98);




	
fib_heap_insert(35);
fib_heap_insert(21);
fib_heap_insert(25);
fib_heap_insert(32); 
fib_heap_insert(31);
fib_heap_insert(51);
fib_heap_insert(41);
fib_heap_insert(61);
fib_heap_insert(52);
fib_heap_insert(71);
fib_heap_insert(4);
fib_heap_insert(13);
fib_heap_insert(2);
	*/
	

	
    int choice,key,okey;
    do
    {

    cout<<"\n MENU:"<<endl;
    cout<<"1. Insert into Heap \n 2. Delete a key  \n 3. Extract the Minimum node \n 4. Decrease a key \n5. Display Heap \n 6. Exit\n";
    cin>>choice;
    switch (choice)
    {
    case 1: cout<<"Enter the Value to be inserted"<<endl;
            cin>>key;
            fib_heap_insert(key);
			cout<<key<<" has been inserted"<<endl;    
			    
            break;
    case 2:if(n_nodes!=0)
	{
	cout<<"Enter the Value to be deleted"<<endl;
            cin>>key;
            Deletion(key);
	}
	else
	{
		cout<<"\nThe Heap is Empty\n";
	}
            
          
            break;
    case 3:if(n_nodes!=0)
	{
		Extract_min();
	}
	else
	{
		cout<<"\nThe Heap is Empty\n";
	}
            
			
            break;
    case 4:if(n_nodes!=0)
	{
	cout<<"Enter the Value to be decreased"<<endl;
            cin>>okey;
           cout<<"Enter the value the new value"<<endl;
           cin>>key;
		   if(okey>key)
		   {
			found=0;       
		   dec(H,okey,key);
		   if(found==1)
		   {
			cout<<"\nKEY DECREASED\n";
		   }
		   
		   else
		   {
			cout<<"\nKEY NOT FOUND \n";
		   }
		   }
		   else
		   {
			cout<<"\nNumber CANNOT be decreased\n";
		   }
	}
	else
	{
		cout<<"\nThe Heap is Empty\n";
	}
		   break;
    case 5:
	
	cout<<"\nDisplaying the Heap\n"<<endl;
	cout<<"Number of Nodes:"<<n_nodes<<endl;
	if(n_nodes!=0)
	{
		Consolidate();
		display(H);
	}
	else
	{
		cout<<"\nThe Heap is Empty\n";
	}
		
        break;
        case 6: cout<<"\nExiting!!\n";
        break;
    default:cout<<"\nWrong Choice! Try Again!!"<<endl;
        break;
    }
    } while (choice!=6);
	cout<<"DONE!!\n";
	return 0;
}