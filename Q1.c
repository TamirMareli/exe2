
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//Q1.1a
typedef struct Worker {
	unsigned int Id;
	char* name;
	unsigned long sallery;
	char Year[7];
}Worker;
//Q1.c
typedef struct WorkerList {
	Worker* data;
	struct WorkerList* next;
}WorkerList;

void PrintWorker(Worker* worker);
void printListWorkers(WorkerList* head);
Worker* CreateWorker();
WorkerList* addWorker(WorkerList* head, Worker* w);
int indexLoop(WorkerList* head, long unsigned Id);
int indexRecursia(WorkerList* head, long unsigned Id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float precent);
WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);

void main() {
	printf("Check the reateWorker and print functions:\n ");
	Worker* w1 = CreateWorker();
	Worker* w2 = CreateWorker();
	Worker* w3 = CreateWorker();
	Worker* w4 = CreateWorker();
	Worker* w5 = CreateWorker();
	PrintWorker(w1);
	PrintWorker(w2);
	PrintWorker(w3);
	PrintWorker(w4);
	PrintWorker(w5);
	printf("Check the addWorker function:\n ");
	WorkerList* wL=NULL;
	wL=addWorker(wL, w1);
	wL = addWorker(wL, w2);
	wL = addWorker(wL, w3);
	wL = addWorker(wL, w4);
	wL = addWorker(wL, w5);
	printListWorkers(wL);
	printf("Check the indexLoop function:\n ");
	printf("The result:%d\n", indexLoop(wL, 206862146));
	printf("Check the indexRecursia function:\n ");
	printf("The result:%d\n", indexRecursia(wL, 206862146,0));
    printf("Check the deleteWorstWorker function:\n ");
	wL=deleteWorstWorker(wL);
	printListWorkers(wL);
	printf("Check the updateWorker function:\n ");
	update_worker(wL, 0.5);
	printListWorkers(wL);
	printf("Check the reverse function:\n ");
	wL=reverse(wL);
	printListWorkers(wL);
	printf("Check the freeWorker  function:\n ");
	freeWorkers(wL);
}
//Q1.b
Worker* CreateWorker() {
	Worker* ptr = (Worker*)malloc(sizeof(Worker));
	if (!ptr) { printf("allocation failed\n"); exit(0); };
	printf("Enter Id:");
	scanf("%u", &(ptr->Id));
	ptr->name = (char*)malloc(20);
	if (!ptr->name) { printf("allocation failed\n"); exit(0); };
	printf("Enter name:");
	scanf("%19s", ptr->name);
	ptr->name = realloc(ptr->name, strlen(ptr->name)+1);
	printf("Enter sallery:");
	scanf("%ul", &ptr->sallery);
	printf("Enter year:");
	scanf("%6s", ptr->Year);
	return ptr;
}

void PrintWorker(Worker* worker) {
	if (worker == NULL) {
		printf("error\n");
		return;
	}
	printf("Id:%d\nname:%s\nsallery:%lu\nYears:%s\n\n", worker->Id, worker->name, worker->sallery, worker->Year);
}


//Q2.1c.1:
WorkerList* addWorker(WorkerList* head, Worker* w) {
	if (w == NULL) {//check if the worker is NULL
		printf("error");
		exit(1);
	}

	WorkerList* wL = (WorkerList*)malloc(sizeof(WorkerList));
	if (wL == NULL) { printf("allocation failed"); exit(1); };
	//pointer data's that we need from the worker to the new list
	wL->data = w;
	wL->next = NULL;

	if (head == NULL) {//If the list is empty
		return wL;
	}

	if (head->next == NULL) {//If in the list have only one object
		if (head->data->sallery <= w->sallery) {//if the first object is bigger then the new one
			wL->next = head;
			return wL;
		}
		else {//and the opposite
			head->next = wL;
			return head;
		}
	}
	WorkerList* temp = head;//pointer to the top of the list

	while (temp->next != NULL) {
		temp = temp->next;//return the temp to head of the list
	}
	if (head->data->sallery > temp->data->sallery) {//check if the list is big to small
		temp = head;
		if (temp->data->sallery <= w->sallery) {//if the sallery of new worker is bigger than sallery of the sallery head
			wL->next = temp;
			return wL;
		}
		while (temp->next != NULL) {
			if (temp->next->data->sallery <= w->sallery) {//chack the location of the new worker
				wL->next = temp->next;
				temp->next = wL;
				return head;
			}
			else {//if we are in the end of the list
				temp->next = wL;
				return head;
			}
			temp = temp->next;
		}
		temp->next = w;//if the new has the smallest sallery
		return head;
	}
	else {//if the list small to big
		temp = head;
		if (temp->data->sallery >= w->sallery) {//if the sallery of new worker is bigger than sallery of the sallery head
			wL->next = temp;
			return wL;
		}

		while (temp->next != NULL) {
			if (temp->next->data->sallery >= w->sallery) {//chack the location of the new worker
				wL->next = temp->next;
				temp->next = wL;
				return head;
			}
			else {//if we are in the end of the list
				temp->next = wL;
				return head;
			}
			temp = temp->next;
		}
		temp->next = w;//if the new worker has the biggest sallery
		return head;
	}

}

//Q2.1.c.2:
int indexLoop(WorkerList* head, long unsigned Id) {//In loop
	int count = 0;
	while (head != NULL) {//checking if the id is in the data
		count++;
		if (head->data->Id == Id) {
			return count;
		}
		head = head->next;
	}
	return -1;// if id is not in the list
}

int indexRecursia(WorkerList* head, long unsigned Id,int index) {//In recursia
	if (head == NULL) {// if id is not in the list
		return -1;
	}
	if (head->data->Id == Id) {//checking if the id is in the data
		return index+1;//the index is starting from 1
	}
	return indexRecursia(head->next, Id,index+1);
}

//Q2.1.c.3:
WorkerList* deleteWorstWorker(WorkerList* head) {
	WorkerList* temp = head;
	if (head == NULL)// if the list is empty we return Null
		return NULL;

	if (head->next == NULL) {// if there is only one object in the list we free him
		free(head);
		return NULL;
	}

	if (head->data->sallery > head->next->data->sallery) {//if the list is sort in a big-small order.
		while (temp->next->next != NULL) {//checking if we reach the point we want to extract
			temp = temp->next;
		}
		free(temp->next->data);
		//free(temp->next);
		temp->next = NULL;
	}
	else {//here is the order is from small-big
		head = head->next;
		free(temp->data);
		//free(temp);
	}
	return head;
}

//Q2.1.c4
void update_worker(WorkerList* head, float precent) {
	while (head != NULL) {
		head->data->sallery += (head->data->sallery) * precent;
		head = head->next;
	}
}

//Q2.1.c5
WorkerList* reverse(WorkerList* head) {
	if (head == NULL)// if the list is empty 
		return NULL;

	if (head->next == NULL)// if there is only one object in the list
		return head;

	WorkerList* top = head;
	WorkerList* mid = head->next;
	if (head->next->next == NULL) {//if there is two object in the va_list
		mid->next = top;
		top->next = NULL;
		head = mid;
		return head;
	}
	//if there is 3 objects and above
	WorkerList* bootom = head->next->next;
	while (bootom != NULL)
	{
		mid->next = top;
		top = mid;
		mid = bootom;
		bootom = bootom->next;
	}
	mid->next = top;
	head->next = NULL;
	head = mid;
	return head;
}

//Q2.1.c.6:
void freeWorkers(WorkerList* head) {
	if (head == NULL) {//if the list of workers is empty
		return;
	}

	if (head->next == NULL) {//if there is only one worker in the list.
		free(head->data);
		free(head);
	}

	WorkerList* temp = head->next;
	while (temp != NULL) {//a situation where we have two or more workers in the list.
		free(head->data);
		free(head);
		head = temp;
		temp = temp->next;
	}
	free(head->data);
	free(head);//setting free the last worker on the list.
}

//function that print the list of workers
void printListWorkers(WorkerList* head) {
	while (head!=NULL) {
		PrintWorker(head->data);
		head = head->next;
	}
}

