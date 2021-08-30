#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <set>

using namespace std;

struct Node
{
    string value;
    int cost = 0;
    Node* parent = nullptr;
    vector<Node*> children;

};

class Compare
{
    public:
        bool operator() (Node* child1, Node* child2)
        {
            if (child1->cost > child2->cost)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

};

void findChildren(Node* n, vector<Node*>&children)
{
    string board = n->value;

    for (int i = 0; i < board.length(); i++)
    {
        if (board[i] == '#')
        {
            if ( i != 0 && i != 1 && i != 2) // MOVING UP
            {
                string puzzle = board;
                char temp = puzzle[i];
                puzzle[i] = puzzle[i-3];
                puzzle[i-3] = temp;

                Node* child = new Node();
                child->value = puzzle; 
                child->cost = n->cost + 5;
                children.push_back(child);

            }

           if ( i != 6 && i != 7 && i != 8) //MOVING DOWN
           {
                string puzzle = board;

                char temp = puzzle[i];
                puzzle[i] = puzzle[i+3];
                puzzle[i+3] = temp;

                Node* child = new Node();
                child->value = puzzle; 
                child->cost = n->cost + 1;
                children.push_back(child);
           }

           if (i % 3 > 0) // MOVE LEFT
           {
                string puzzle = board;

                char temp = puzzle[i];
                puzzle[i] = puzzle[i-1];
                puzzle[i-1] = temp;

                Node* child = new Node();
                child->value = puzzle; 
                child->cost = n->cost + 1;
                children.push_back(child);
           }

           if (i % 3 < 2) //MOVING RIGHT
           {
                string puzzle = board;

                char temp = puzzle[i];
                puzzle[i] = puzzle[i+1];
                puzzle[i+1] = temp;

                Node* child = new Node();
                child->value = puzzle;
                child->cost = n->cost + 1;
                children.push_back(child);  
           }


        }
    }
}

Node* BFS(Node* root, string goal)
{
    if (root->value == goal)
    {
        return root;
    }
    else
    {
        Node* node = root;
        
        queue<Node*>frontier;
        frontier.push(node);

        set<string> explored;

        while (!frontier.empty())
        {
            node = frontier.front();
            frontier.pop();
            explored.insert(node->value);

            findChildren(node, node->children);

            for (int i = 0; i < node->children.size(); i++)
            {
                Node* child = node->children[i];
                child->parent = node;

                bool checkExplored = explored.find(child->value) != explored.end();

                if (checkExplored == false)
                {
                    if (child->value == goal)
                    {
                        return child;
                    }
                    frontier.push(child);
                }
            }
        }

    }

}

Node* UniformCost(Node* root, string goal)
{
    Node* node = root;
    
    priority_queue<Node*, vector<Node*>, Compare> frontier;
    frontier.push(node);

    set<string> explored;
    

    while (!frontier.empty())
    {
        node = frontier.top();
        frontier.pop();

        if (node->value == goal)
        {
            return node;
        }
    
        
            explored.insert(node->value);
            
            findChildren(node, node->children);

            for (int i = 0; i < node->children.size(); i++)
            {
                Node* child = node->children[i];
                child->parent = node;

                bool checkExplored = explored.find(child->value) != explored.end();

                if (checkExplored == false)
                {
                    frontier.push(child);
                }


                
            }

        
    }


}

int main(){


    string FirstValues, SecondValues;

    cin >> FirstValues; 
    cin >> SecondValues;

    Node* root = new Node();
    root->value = FirstValues;

    Node* resultBFS = BFS(root, SecondValues);

    int count = 0;
    while(resultBFS->parent != nullptr)
    {
        resultBFS = resultBFS->parent;
        count++;
    }
    cout << "Cost of Breadth First Search: " << count << endl;

    cout << endl;

    Node* resultUCS = UniformCost(root, SecondValues);
    cout << "Cost of Uniform Search: " << resultUCS->cost << endl;

    return 0;
}