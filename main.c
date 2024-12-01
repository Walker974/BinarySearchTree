#include<stdio.h>
#include<stdlib.h>
typedef struct tag{
  int N; 
  struct tag*left; 
  struct tag*right;
}node; 

void menu(void){
  printf("\n\t\t----------- Let's Practice BST ------------\n");
  printf("\n\t\t1. Add a new node\n");
  printf("\n\t\t2. Search if N Exists\n");
  printf("\n\t\t3. Delete a node\n");
  printf("\n\t\t4. Traverse the Tree InOrder\n");
  printf("\n\t\t5. Compute Tree Height\n");
  printf("\n\t\t6. Check if Tree is balanced or not\n");
  printf("\n\t\t7. Check if Tree is completely balanced or not\n");
  printf("\n\t\t8. Compute the number of possible paths\n");
  printf("\n\t\t9. QUIT\n");
  printf("\n\t\t--------------------------------------------\n");
  printf("\n\t\tYour choice:"); 
}
node* create_node(int N){
  node*new_node; 
  new_node= (node*)malloc(sizeof(node));
  new_node->N=N;
  new_node->left=NULL;
  new_node->right=NULL; 
  return(new_node);
}
int search_element(node*root,int N){
  if(root==NULL)
    return(0); 
  else if (root->N ==N)
    return(1); 
  else if(N<root->N)
    return(search_element(root->left,N));
  else
   return(search_element(root->right,N));
}
node* add_node(node*root,node*ToAdd){
 if(root==NULL)
   root=ToAdd; 
 else if(ToAdd->N < root->N)
   root->left= add_node(root->left,ToAdd);
 else
   root->right= add_node(root->right,ToAdd);

return(root);
}
node* create_initial_BST(FILE*infp,node*root){
  node* new_node; 
  int N,x;
  fseek(infp,0,0);
  while(!feof(infp)){
    fscanf(infp,"%d",&N);
    x=search_element(root,N); 
    if(x==0){
      new_node=create_node(N);
      root=add_node(root,new_node); 
    }
  }
  return(root);
}
void traverse_inOrder(node*root){
  if(root==NULL)
    return; 
  else{
    traverse_inOrder(root->left); 
	printf("\t%d ", root->N); 
	traverse_inOrder(root->right); 
  }
 }
node* find_min(node*root){
   if(root->left==NULL)
     return(root); 
   else
     return(find_min(root->left));
}
node* delete_node(node*root,int toDelete){
 node*temp; 
  if(root==NULL)
    return(root);
  else if (toDelete < root->N)
     root->left= delete_node(root->left,toDelete);
  else if(toDelete > root->N)
     root->right= delete_node(root->right,toDelete);
  //Element was found in the BST
  //Check if it is a node with two kids or not
  else if(root->left!=NULL && root->right!=NULL){
    //Let's find the number to replace it in the right sub-tree
    temp=find_min(root->right);
    //Replace the value of the element by the min value
	root->N = temp->N; 
	//Adjust the right sub-tree
	root->right= delete_node(root->right, root->N);
    }
  else{
   	temp=root;
   //Node is either a leaf or a node with 1 kid
      if(root->left==NULL)
        root=root->right; 
	  else if(root->right==NULL)
	    root=root->left;  
	  free(temp);
	  }
return(root);
}
int compute_height(node*root){
  int left_height, right_height;
  if(root==NULL)
    return(-1);
  else{
    left_height=compute_height(root->left);
    right_height=compute_height(root->right);
    if(left_height>right_height)
      return(left_height+1);
    else
      return(right_height+1);
  }
}
int isTreeBalanced(node*root){
  int left_height, right_height;
  if(root==NULL)
    return(1);
  else{
    left_height=compute_height(root->left);
    right_height=compute_height(root->right);
    if(abs(left_height-right_height)<=1 && isTreeBalanced(root->left) && isTreeBalanced(root->right))
      return(1);
    else
      return(0);
  }
}
int isTreeCompletelyBalanced(node*root){
  int left_height, right_height;
  if(root==NULL)
    return(1);
  else{
    left_height=compute_height(root->left);
    right_height=compute_height(root->right);
    if(left_height==right_height && isTreeCompletelyBalanced(root->left) && isTreeCompletelyBalanced(root->right))
      return(1);
    else
      return(0);
  }
}
int possiblePaths(node*root){
  if(root==NULL)
    return(0);
  else if(root->left==NULL && root->right==NULL)
    return(1);
  else
    return(possiblePaths(root->left)+possiblePaths(root->right));
};
int main(void){ 
  FILE*infp; 
  int choice,N,status, height, isBalanced, isCompletelyBalanced, paths;
  node* root=NULL, *new_node;
  int i,status_b, h; 
  int number; 
  infp= fopen("data.txt","r");
  if(infp==NULL)
    {
    	printf("\n\t\tSORRY! Could not open the file!\n\t\tProgram will end!\n\t\t");
    	return(0);
	}
   else{
   root=create_initial_BST(infp,root);
   	do{
      menu();
      scanf("%d",&choice);
      switch(choice){
      case 1:
        printf("\n\t\tInput the value of N:"); 
        scanf("%d",&N);
        //We are not inserting duplicates so let's search if the element is in the tree 
        status=search_element(root,N);
        if(status==0)
        { //only if not found 
          new_node=create_node(N);
          root=add_node(root,new_node);
          printf("\n\t\t%d was added to the BST!\n",N);
        } 
        else
          printf("\n\t\t%d was not added to the BST as it already exists!\n",N);
            break; 
      case 2:
        printf("\n\t\tInput a number to search for:");
        scanf("%d",&N); 
        status=search_element(root,N); 
        if(status==0)
          printf("\n\t\t%d was not found in the BST!\n",N); 
        else
          printf("\n\t\t%d was found in the BST!\n",N); 
        break; 
      case 3:
        printf("\n\t\tPlease input the number to delete:");
          scanf("%d",&N);
          status=search_element(root, N); 
          if(status==0)
            printf("\n\t\t%d was NOT FOUND in the BST!\n",N);
          else{
            root=delete_node(root,N); 
            printf("\n\t\t%d was deleted from the BST!\n",N);
          }
        break; 
      case 4:
        if(root==NULL)
          printf("\n\t\tBST is EMPTY!\n");
        else{ 
          printf("\n\t\t Your BST has the following numbers:\n\t");
          traverse_inOrder(root);
          printf("\n");
        }
        break; 
      case 5:
        height=compute_height(root);
        printf("\n\t\tThe height of the BST is: %d\n",height);
        break;
      case 6:
        isBalanced=isTreeBalanced(root);
        if(isBalanced==1)
          printf("\n\t\tThe BST is balanced!\n");
        else
          printf("\n\t\tThe BST is NOT balanced!\n");
        break;
      case 7:
        isCompletelyBalanced=isTreeCompletelyBalanced(root);
        if(isCompletelyBalanced==1)
          printf("\n\t\tThe BST is completely balanced!\n");
        else
          printf("\n\t\tThe BST is NOT completely balanced!\n");
      case 8: 
        paths=possiblePaths(root);
        printf("\n\t\tThe number of possible paths in the BST is: %d\n",paths);
      default: printf("\n\t\tWRONG CHOICE!!\n");
      case 9: 
        printf("\n\t\tDecided to QUIT....\n\n\t\tBYE\n\n\t\t");
        break; 
    }
    }while(choice!=7);     
   }
return(0);
}
