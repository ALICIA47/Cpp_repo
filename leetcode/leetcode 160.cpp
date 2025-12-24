class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            if(headA==NULL||headB==NULL)return NULL;
            if(headA==NULL&&headB==NULL)return NULL;
            
            int lenA=longlen(headA),lenB=longlen(headB);
            ListNode*a=headA;
            ListNode*b=headB;
            if(lenA>lenB){
                while(lenA>lenB){
                    a=a->next;
                    lenA--;
                }
            }
            if(lenA<lenB){
                while(lenA<lenB){
                    b=b->next;
                    lenB--;
                }
            }
            while(a!=b){
                a=a->next;
                b=b->next;
            }
            return a;
        }
    private:
        int longlen(ListNode*head){
                ListNode*p=head;
                int len=0;
                while(p!=NULL){
                    p=p->next;
                    len++;
                }
                return len;
            }
    };