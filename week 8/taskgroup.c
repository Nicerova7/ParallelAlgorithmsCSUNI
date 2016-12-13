/*
* A 10-node tree is initialized with random integers between 1 and 50.
* The start_Background_work () function computes the sum of the values 
* of the tree nodes.
* The compute_tree() function traverses the tree in postorden and raise
* the values to the square.
*/

#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

int s = 0;

struct node
{
	int data;
	struct node* left;
	struct node* right;
};
	
struct node* newNode(int data)
{
	struct node* node = (struct node*)	//Create node
	malloc(sizeof(struct node));		//Memory
	node->data = data;	
	node->left = NULL;	
	node->right = NULL;
	return(node);
}

void printPostorder(struct node *p)
{
	#pragma omp task
	if(p->left) printPostorder(p->left);
	#pragma omp task
	if(p->right) printPostorder(p->right);
	#pragma omp taskwait
		printf("%d \n",p->data);
	#pragma omp barrier
}

int aleatorio(void)	//range 1-50
{
	int i;
	i = ( rand() / (float)RAND_MAX )*49+1;
}

void compute_something(struct node *p)
{
	int t;
	t = p->data;
	p->data = t*t;
}


void compute_tree(struct node*p)
{	
	#pragma omp task
	if(p->left) compute_tree(p->left);
	#pragma omp task
	if(p->right) compute_tree(p->right);

	#pragma omp taskwait
	compute_something(p);
	#pragma omp barrier
}

int start_background_work(struct node*p)
{	
	
	#pragma omp task
	if(p->left) start_background_work(p->left);
	#pragma omp task
	if(p->right) start_background_work(p->right);
	#pragma omp taskwait
		s += p->data;
}

int main(int argc,char *argv[])
{
	int so;	
	srand(time(NULL));
	struct node*root = newNode(aleatorio());
	root->left 	 = newNode(aleatorio());
	root->right	 = newNode(aleatorio());
	root->left->left =  newNode(aleatorio());
	root->left->right = newNode(aleatorio());
	root->right->left = newNode(aleatorio());
	root->right->right = newNode(aleatorio());
	root->left->left->left = newNode(aleatorio());
	root->left->left->right = newNode(aleatorio());
	root->left->right->left = newNode(aleatorio());
	omp_set_num_threads(4);
	#pragma omp parallel
	#pragma omp single
	printf("\nPostorder is \n");
	printPostorder(root);
	
	#pragma omp task
	printf("\nThe sum is: %d\n",start_background_work(root));

	#pragma omp taskgroup
	{
	#pragma omptask
         printf("\nAfter the function compute_tree: \n");
	 compute_tree(root);
	}
	 printPostorder(root);
	return 0;
}

