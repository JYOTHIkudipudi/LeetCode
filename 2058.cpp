class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        
        vector<int> ans = {-1, -1};

        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return ans;

        ListNode* prevNode = head;
        ListNode* curr = head->next;

        int pos = 1;
        int first = -1;
        int prevCritical = -1;

        int minDist = INT_MAX;
        int maxDist = 0;

        while (curr->next != nullptr) {
            
            int prevVal = prevNode->val;
            int currVal = curr->val;
            int nextVal = curr->next->val;

            // Check if current node is a critical point
            bool isCritical =
                (currVal > prevVal && currVal > nextVal) ||
                (currVal < prevVal && currVal < nextVal);

            if (isCritical) {
                
                if (first == -1) {
                    // First critical point
                    first = pos;
                } 
                else {
                    // Distance from previous critical point
                    minDist = min(minDist, pos - prevCritical);

                    // Distance from first critical point
                    maxDist = max(maxDist, pos - first);
                }

                prevCritical = pos;
            }

            prevNode = curr;
            curr = curr->next;
            pos++;
        }

        if (first == -1 || first == prevCritical)
            return {-1, -1};

        return {minDist, maxDist};
    }
};
