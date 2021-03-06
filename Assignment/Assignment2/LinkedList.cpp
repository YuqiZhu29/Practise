struct ListNode{
	int label;
	ListNode* next, *arbit;
	ListNode(int l) : label(l), next(NULL), arbit(NULL) {}
};
//Q1
//we can also use dfs to solve this, but it is not a O(n) time solution.
ListNode* copyList(ListNode* head){
	if(!head)
		return NULL;
	ListNode* move = head;
	//make duplicate nodes like: 1->2->3 to 1->1'->2->2'->3->3'
	while(move){
		ListNode* dup = new ListNode(move->label);
		dup->next = move->next;
		move->next = dup;
		move = move->next->next;
	}
	//copy arbit
	move = head;
	while(move){
		if(move->arbit)
			move->next->arbit = move->arbit->next;
		move = move->next->next;
	}
	//rebuild list
	ListNode* dummy = new ListNode(0);
	ListNode* dup = dummy;
	move = head;
	while(move){
		dup->next = move->next;
		move->next = move->next->next;
		move = move->next;
		dup = dup->next;
	}
	return dummy->next;
}

//Q2
//return the start point of loop, and print the length of loop
ListNode* listLoop(ListNode* head){
	if(!head)
		return NULL;
	ListNode* slow = head, * fast = head;
	do{
		if(!fast || !fast->next)
			return NULL;
		slow = slow->next;
		fast = fast->next->next;
	}while(slow != fast);
	slow = head;
	while(slow != fast){
		slow = slow->next;
		fast = fast->next;
	}
	int length = 0;
	do{
		length++;
		slow = slow->next;
	}while(slow != fast);
	cout<<length<<endl;
	return slow;
}

//Q3
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
	if(!l1 || !l2)
		return !l1 ? l2 : l1;
	ListNode* dummy = new ListNode(0);
	//I use node* curr to build the new list
	//every time I pick a node from l1 or l2, let curr->next = this node;
	ListNode* curr = dummy;
	while(l1 || l2){
	//when l1 point to NULL, which mean we only get node form l2 list, otherwise from l1 list
		if(!l1){
			curr->next = l2;
			l2 = l2->next;
		}
		else if(!l2){
			curr->next = l1;
			l1 = l1->next;
		}
	//or we pick a smaller node from l1 and l2
		else{
			if(l1->label > l2->label){
				curr->next = l2;
				l2 = l2->next;
			}
			else{
				curr->next = l1;
				l1 = l1->next;
			}
		}
	//curr move to the next position
		curr = curr->next;
	}
	return dummy->next;
}

//Q4
ListNode* removeNthFromEnd(ListNode* head, int n){
	if(!head || !head->next)
		return NULL;
	if(!n)
		return head;
	int length = 0;
	ListNode* dummy = new ListNode(0);
	dummy->next = head;
	ListNode* move = head;
	while(move){
		length++;
		move = move->next;
	}
	if(n > length)
		n %= length;
	move = dummy;
	for(int i = 0; i < length - n; i++){
		move = move->next;
	}
	move->next = move->next->next;
	return dummy->next;
}

//Q5  
Node* flattenList(Node* head) {
	if(!head)
		return NULL;
	Node* dummy = new Node(0);
	Node* builder = dummy;
	Node* nextLevel = new Node(0);
	Node* nextLevelBuilder = nextLevel;
	while(head) {
		while(head) {
			if(head->child) {
				Node* temp = head->child;
				//apart two level
				head->child = NULL;
				while(temp) {
					nextLevelBuilder->next = temp;
					nextLevelBuilder = temp;
					temp = temp->next;
				}
			}
			builder->next = head;
			builder = head;
			head = head->next;
		}
		head = nextLevel->next;
		nextLevel->next = NULL;
		nextLevelBuilder = nextLevel;
	}
	return dummy->next;
}




































