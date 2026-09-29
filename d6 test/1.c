/*
 * Move every node whose value is greater than the last node's value to the
 * end of a doubly linked list, walking the list once from the head.
 *
 * Sample Input:
 *   (no input is read; the list 4 9 2 7 5 is hard-coded in main)
 *
 * Sample Output:
 *   before: 4 9 2 7 5
 *   after : 4 2 5 9 7
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;

void insert_node(node *ptr, node **h){
  node *last = *h;
  while(last->next != NULL){
    last = last->next;
  }
  last -> next = ptr;
  ptr -> next = NULL;
  ptr -> prev = last;
}

void delete_greater(node **h){
  if(*h == NULL || (*h) -> next == NULL){
    return ;
  }
  node *last = *h;
  while(last->next != NULL){
    last = last->next;
  }
  node *u1 = *h;
  while (u1 != last){
    if( u1 -> data > last -> data){
      if( u1 == *h ){
        node *ptr = *h;
        *h = ptr -> next;
        ptr->next->prev = NULL;
        insert_node(ptr, h);
        u1 = *h;
      }
      else {
        node *ptr = u1;
        u1 = ptr->next;
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
        insert_node(ptr, h);
      }
    }
    else{
      u1 = u1->next;
    }
  }
}

node *make_node(int val){
  node *n = malloc(sizeof(node));
  n->data = val;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

node *build_list(int *vals, int count){
  node *h = NULL;
  for(int i = 0; i < count; i++){
    node *n = make_node(vals[i]);
    if(h == NULL){
      h = n;
    }
    else{
      insert_node(n, &h);
    }
  }
  return h;
}

void print_list(node *h){
  for(node *p = h; p != NULL; p = p->next){
    printf("%d ", p->data);
  }
  printf("\n");
}


int main(){
  int vals[] = {4, 9, 2, 7, 5};
  node *h = build_list(vals, sizeof(vals)/sizeof(vals[0]));

  printf("before: ");
  print_list(h);

  delete_greater(&h);

  printf("after : ");
  print_list(h);

  return 0;
}
