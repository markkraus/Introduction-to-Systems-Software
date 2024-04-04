/* >​< >‌‌‌<
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  (queue_t*) malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL){
      return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
  if(q == NULL){
    return;
  }

  list_ele_t *curr = q->head;
   while(curr != NULL){
    list_ele_t *next = curr->next;
    free(curr->value);
    free(curr);
    curr = next;

   }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    /* What should you do if the q is NULL? */
    if(q == NULL){
      return false;
    }

    /* What if either call to malloc returns NULL? */
    newh = (list_ele_t*) malloc(sizeof(list_ele_t));
    if(newh == NULL){
      return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    newh->value = (char*) malloc(strlen(s) + 1);
    if(newh->value == NULL){
      free(newh);
      return false;
    }

    strcpy(newh->value, s); /* copies s into newh value */
    newh->value[strlen(s)] = '\0'; /* copies sentinal value into last piece of string */



    /* You must do the cleanup of anything left behind */
    newh->next = q->head;
    if(!q->head){
      q->tail = newh;
    }
    q->head = newh;

    q->size++;


    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if(!q){
      return false;
    }

    list_ele_t * newt = malloc(sizeof(list_ele_t));
    if(!newt){
      return false;
    }

    newt->value = (char*) malloc(strlen(s) + 1);
    if(!newt->value){
      free(newt);
      return false;
    }


    strcpy(newt->value, s);
    newt->value[strlen(s)] = '\0';

    newt->next = NULL;

   if (q->head == NULL) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
    }

    q->tail = newt;

    q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{

    if(q == NULL || q->head == NULL){
      return false;
    }
    list_ele_t * remove = q->head;
      q->head = q->head->next;

    if(sp != NULL){
      strncpy(sp, remove->value, bufsize - 1);
      sp[bufsize - 1] = '\0';
    }

    free(remove->value);
    free(remove);

    q->size--;

    if (!q->head) {
        q->tail = NULL;
    }

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
   if (!q) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
  if(q == NULL || q->head == NULL){
    return;
  }
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    list_ele_t *next = curr->next;

    while (next != NULL) {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }

    curr->next = prev;
    q->tail = q->head;
    q->head = curr;
}
