#include <iostream>
#include <vector>
#include <string>
using namespace std;
struct Victim 
{
    int id;
    string name;
    string location;
    int severity;
    int age;
    string gender;
};
struct RescueTeam 
{
    int teamID;
    string type;
    int capacity;
    bool isBusy;
};
struct LogNode 
{
    string message;
    LogNode* next;
};
void mySwap(Victim& a, Victim& b) 
{
    Victim temp=a;
    a=b;
    b=temp;
}
class ManualLogList 
{
private:
    LogNode* head;
    LogNode* tail;
public:
    ManualLogList() 
    {
        head=nullptr;
        tail=nullptr;
    }
    void addLog(string msg) 
    {
        LogNode* newNode=new LogNode;
        newNode->message=msg;
        newNode->next=nullptr;
        if (head==nullptr) 
        {
            head=newNode;
            tail=newNode;
        } 
        else 
        {
            tail->next=newNode;
            tail=newNode;
        }
    }
    void displayLogs() 
    {
        if (head==nullptr) 
        {
            cout<<"No logs recorded yet."<<endl;
            return;
        }
        cout<<"--- SYSTEM LOGS ---"<<endl;
        LogNode* temp=head;
        while (temp!=nullptr) 
        {
            cout<<">> "<<temp->message<<endl;
            temp=temp->next;
        }
        cout<<"-------------------"<<endl;
    }
};
class VictimPriorityQueue 
{
private:
    vector<Victim> heap;
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i)+1; }
    int right(int i) { return (2*i)+2; }
    void heapifyDown(int i) {
        int l=left(i);
        int r=right(i);
        int smallest=i;
        if (l<heap.size() && heap[l].severity<heap[smallest].severity)
            smallest=l;
        if (r<heap.size() && heap[r].severity<heap[smallest].severity)
            smallest=r;
        if (smallest!=i) 
        {
            mySwap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }
    void heapifyUp(int i) 
    {
        if (i && heap[parent(i)].severity>heap[i].severity) 
        {
            mySwap(heap[i], heap[parent(i)]);
            heapifyUp(parent(i));
        }
    }
public:
    void push(Victim v) 
    {
        heap.push_back(v);
        heapifyUp(heap.size() - 1);
    }
    void pop() 
    {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    Victim top() 
    {
        if (!heap.empty()) return heap[0];
        Victim v={-1, "", "", 0, 0, ""};
        return v;
    }
    bool isEmpty()
    {
        return heap.empty();
    }
    int size() 
    {
        return heap.size();
    }
    void displayQueue() 
    {
        if (heap.empty()) 
        {
            cout<<"Emergency Queue is Empty."<<endl;
            return;
        }
        cout<<"Current Emergency Queue (Min-Heap Structure):"<<endl;
        for (int i=0; i<heap.size(); i++) 
        {
            cout<<"ID: "<<heap[i].id<<endl;
            cout<<"Sev: "<<heap[i].severity<<endl;
            cout<<"Loc: "<<heap[i].location<<endl;
        }
    }
};
struct BSTNode 
{
    RescueTeam data;
    BSTNode* left;
    BSTNode* right;
};
class TeamBST 
{
private:
    BSTNode* root;
    BSTNode* insertRec(BSTNode* node, RescueTeam team) 
    {
        if (node==nullptr) 
        {
            BSTNode* newNode=new BSTNode;
            newNode->data=team;
            newNode->left=nullptr;
            newNode->right=nullptr;
            return newNode;
        }
        if (team.teamID < node->data.teamID)
            node->left = insertRec(node->left, team);
        else if (team.teamID > node->data.teamID)
            node->right = insertRec(node->right, team);
        return node;
    }
    void inorderRec(BSTNode* node) 
    {
        if (node != nullptr) 
        {
            inorderRec(node->left);
            cout<<"Team ID: " << node->data.teamID << endl;
            cout<<"Type: " << node->data.type<<endl;
            cout<<"Status: " << (node->data.isBusy ? "BUSY" : "AVAILABLE") << endl;
            inorderRec(node->right);
        }
    }
    BSTNode* searchRec(BSTNode* node, int id) 
    {
        if (node == nullptr || node->data.teamID == id)
            return node;
        if (id < node->data.teamID)
            return searchRec(node->left, id);
        return searchRec(node->right, id);
    }
    RescueTeam* findAvailableRec(BSTNode* node) 
    {
        if (node == nullptr) 
        return nullptr;
        if (!node->data.isBusy) 
        return &(node->data);
        RescueTeam* leftRes = findAvailableRec(node->left);
        if (leftRes != nullptr) 
        return leftRes;
        return findAvailableRec(node->right);
    }
public:
    TeamBST() 
    { 
        root=nullptr; 
    }
    void insert(RescueTeam team) 
    {
        root=insertRec(root, team);
    }
    void displayTeams() 
    {
        if (root==nullptr) 
        {
            cout<<"No teams registered."<<endl;
            return;
        }
        inorderRec(root);
    }
    RescueTeam* search(int id) 
    {
        BSTNode* res=searchRec(root, id);
        if (res!=nullptr) return &(res->data);
        return nullptr;
    }
    RescueTeam* findFirstAvailable() 
    {
        return findAvailableRec(root);
    }
};
struct CityNode 
{
    string name;
    int id;
};
struct Edge 
{
    int toIndex;
    bool isBlocked;
};
class CityGraph 
{
private:
    vector<CityNode> nodes;
    vector<vector<Edge>> adj;
    int getNodeIndex(string name) 
    {
        for (int i=0; i<nodes.size(); i++) 
        {
            if (nodes[i].name==name) 
            return i;
        }
        return -1;
    }
public:
    void addLocation(string name) 
    {
        if (getNodeIndex(name) != -1) 
        return;
        CityNode newNode;
        newNode.name=name;
        newNode.id=nodes.size();
        nodes.push_back(newNode);
        vector<Edge> e;
        adj.push_back(e);
    }
    void addRoad(string u, string v)
    {
        int uIdx=getNodeIndex(u);
        int vIdx=getNodeIndex(v);
        if (uIdx==-1 || vIdx==-1) 
        {
            cout<<"Error: Invalid locations."<<endl;
            return;
        }
        Edge edge1={vIdx, false};
        Edge edge2={uIdx, false};
        adj[uIdx].push_back(edge1);
        adj[vIdx].push_back(edge2);
    }
    void setBlockage(string u, string v, bool status) 
    {
        int uIdx=getNodeIndex(u);
        int vIdx=getNodeIndex(v);
        if (uIdx==-1 || vIdx==-1) return;
        for (int i = 0; i < adj[uIdx].size(); i++) 
        {
            if (adj[uIdx][i].toIndex == vIdx) 
            {
                adj[uIdx][i].isBlocked = status;
                break;
            }
        }
        for (int i = 0; i < adj[vIdx].size(); i++) 
        {
            if (adj[vIdx][i].toIndex == uIdx) 
            {
                adj[vIdx][i].isBlocked = status;
                break;
            }
        }
    }
    vector<string> bfsPath(string start, string end) 
    {
        int s = getNodeIndex(start);
        int e = getNodeIndex(end);
        if (s == -1 || e == -1) 
        return {};
        vector<int> parent(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        vector<int> q;
        int head = 0;
        visited[s] = true;
        q.push_back(s);
        bool found = false;
        while(head < q.size()) 
        {
            int u=q[head++];
            if (u==e) 
            {
                found = true;
                break;
            }
            for (int i=0; i<adj[u].size(); i++) 
            {
                int v = adj[u][i].toIndex;
                if (!visited[v] && !adj[u][i].isBlocked) 
                {
                    visited[v]=true;
                    parent[v]=u;
                    q.push_back(v);
                }
            }
        }
        vector<string> path;
        if (found) 
        {
            int curr = e;
            while (curr != -1) 
            {
                path.push_back(nodes[curr].name);
                curr = parent[curr];
            }
            int n = path.size();
            for(int i=0; i<n/2; i++) 
            {
                string temp = path[i];
                path[i] = path[n-1-i];
                path[n-1-i] = temp;
            }
        }
        return path;
    }
    void displayCity() 
    {
        cout << "--- CITY INFRASTRUCTURE ---" << endl;
        for (int i=0; i<nodes.size(); i++) 
        {
            cout << nodes[i].name << " connects to: ";
            for (int j=0; j<adj[i].size(); j++) 
            {
                int neighborIdx = adj[i][j].toIndex;
                cout << nodes[neighborIdx].name;
                if (adj[i][j].isBlocked) cout << "(BLOCKED)";
                cout << ", ";
            }
            cout << endl;
        }
    }
};
class DisasterSystem 
{
private:
    VictimPriorityQueue victims;
    TeamBST teams;
    CityGraph city;
    ManualLogList logs;
    int victimCounter;
public:
    DisasterSystem() 
    {
        victimCounter=1;
        initDefaultCity();
    }
    void initDefaultCity() 
    {
        city.addLocation("HQ");
        city.addLocation("NorthZone");
        city.addLocation("SouthZone");
        city.addLocation("EastZone");
        city.addLocation("WestZone");
        city.addLocation("Hospital");
        city.addLocation("Airport");
        city.addLocation("ShelterA");
        city.addLocation("ShelterB");
        city.addRoad("HQ", "NorthZone");
        city.addRoad("HQ", "SouthZone");
        city.addRoad("HQ", "EastZone");
        city.addRoad("HQ", "WestZone");
        city.addRoad("NorthZone", "Hospital");
        city.addRoad("SouthZone", "Airport");
        city.addRoad("EastZone", "ShelterA");
        city.addRoad("WestZone", "ShelterB");
        city.addRoad("Hospital", "ShelterA");
        city.addRoad("Airport", "ShelterB");
        city.addRoad("NorthZone", "EastZone");
        city.addRoad("SouthZone", "WestZone");
        teams.insert({101, "Medical", 4, false});
        teams.insert({102, "Fire", 6, false});
        teams.insert({103, "Police", 2, false});
        teams.insert({104, "General", 10, false});
        logs.addLog("System Initialized with default map and teams.");
    }
    void registerVictim() 
    {
        string name, loc, gender;
        int sev, age;
        cin.ignore();
        cout << "Enter Victim Name: "; 
        getline(cin, name);
        cout << "Enter Location (Exact node name): "; 
        cin >> loc;
        cout << "Enter Severity (1-Critical to 10-Stable): "; 
        cin >> sev;
        cout << "Enter Age: "; 
        cin >> age;
        cout << "Enter Gender: "; 
        cin >> gender;
        Victim v;
        v.id = victimCounter++;
        v.name = name;
        v.location = loc;
        v.severity = sev;
        v.age = age;
        v.gender = gender;
        victims.push(v);
        logs.addLog("Victim Registered: " + name + " at " + loc);
        cout<<"Victim registered successfully with ID: "<<v.id<<endl;
    }
    void registerTeam() 
    {
        int id, cap;
        string type;
        cout<<"Enter Team ID: ";
        cin>>id;
        cout<<"Enter Type (Medical/Fire/Police): ";
        cin>>type;
        cout<<"Enter Capacity: ";
        cin>>cap;
        if (teams.search(id) != nullptr) 
        {
            cout<<"Error: Team ID already exists."<<endl;
            return;
        }
        RescueTeam t = {id, type, cap, false};
        teams.insert(t);
        logs.addLog("New Rescue Team Registered ID: " + to_string(id));
        cout<<"Team registered successfully."<<endl;
    }
    void dispatchRescue() 
    {
        if (victims.isEmpty()) 
        {
            cout<<"No victims to rescue."<<endl;
            return;
        }
        Victim v = victims.top();
        RescueTeam* t = teams.findFirstAvailable();
        if (t == nullptr) 
        {
            cout<<"ALERT: All rescue teams are currently busy!"<<endl;
            logs.addLog("Dispatch Failed: No teams available for Victim " + v.name);
            return;
        }
        cout<<"\n--- DISPATCHING MISSION ---"<<endl;
        cout<<"Target Victim: "<<v.name<<" (Severity: "<<v.severity << ")"<<endl;
        cout<<"Location: "<<v.location<<endl;
        cout<<"Assigned Team: "<<t->teamID<<" (" << t->type << ")"<<endl;
        vector<string> path=city.bfsPath("HQ", v.location);
        if (path.empty()) 
        {
            cout<<"CRITICAL: No reachable path to victim! Roads may be blocked."<<endl;
            logs.addLog("Dispatch Failed: No path to " + v.location);
            return;
        }
        cout<<"Route Calculated: ";
        for (int i=0; i<path.size(); i++) 
        {
            cout<<path[i];
            if (i<path.size() - 1) cout<<" -> ";
        }
        cout<<endl;
        t->isBusy = true;
        victims.pop(); 
        logs.addLog("Team " + to_string(t->teamID) + " dispatched to " + v.location);
        cout<<"Mission Started successfully."<<endl;
    }
    void teamReturning(int id) 
    {
        RescueTeam* t=teams.search(id);
        if (t==nullptr) 
        {
            cout<<"Team not found."<<endl;
            return;
        }
        if (!t->isBusy) 
        {
            cout<<"Team is not currently on a mission."<<endl;
            return;
        }
        t->isBusy = false;
        cout<<"Team "<<id<<" has returned to base and is now available."<<endl;
        logs.addLog("Team " + to_string(id) + " returned to base.");
    }
    void manageRoads() 
    {
        string u, v;
        int op;
        cout<<"1. Block Road\n2. Unblock Road\nChoose: ";
        cin>>op;
        cout<<"Enter Location 1: ";
        cin>>u;
        cout<<"Enter Location 2: ";
        cin>>v;
        
        if (op==1) 
        {
            city.setBlockage(u, v, true);
            logs.addLog("Road blocked: " + u + " - " + v);
            cout<<"Road blocked successfully."<<endl;
        } 
        else 
        {
            city.setBlockage(u, v, false);
            logs.addLog("Road unblocked: " + u + " - " + v);
            cout<<"Road opened successfully."<<endl;
        }
    }
    void viewLogs() 
    {
        logs.displayLogs();
    }
    void viewMap() 
    {
        city.displayCity();
    }
    void viewVictims() 
    {
        victims.displayQueue();
    }
    void viewTeams() 
    {
        teams.displayTeams();
    }
    void analyzeSystem() 
    {
        cout<<"\n--- SYSTEM ANALYSIS ---"<<endl;
        cout<<"Pending Victims: "<<victims.size()<<endl;
        cout<<"Check 'View Teams' for resource availability."<<endl;
    }
};
void showMenu() {
    cout<<"\n============================================="<<endl;
    cout<<"   DISASTER RESPONSE & PATH FINDING SYSTEM   "<<endl;
    cout<<"============================================="<<endl;
    cout<<"1. Report New Victim (Emergency Call)"<<endl;
    cout<<"2. Dispatch Rescue Team"<<endl;
    cout<<"3. Add New Rescue Team"<<endl;
    cout<<"4. Team Returned to Base"<<endl;
    cout<<"5. Manage Road Blockages"<<endl;
    cout<<"6. View Pending Victims (Priority Queue)"<<endl;
    cout<<"7. View Rescue Teams (BST)"<<endl;
    cout<<"8. View City Map Status (Graph)"<<endl;
    cout<<"9. View System Logs (Linked List)"<<endl;
    cout<<"10. Exit"<<endl;
    cout<<"============================================="<<endl;
    cout<<"Enter Choice: ";
}
int main() 
{
    DisasterSystem system;
    int choice;
    while(true) 
    {
        showMenu();
        if (!(cin>>choice)) 
        {
            cin.clear();
            string ignoreLine;
            getline(cin, ignoreLine);
            continue;
        }
        switch(choice) 
        {
            case 1:
                system.registerVictim();
                break;
            case 2:
                system.dispatchRescue();
                break;
            case 3:
                system.registerTeam();
                break;
            case 4:
                int tid;
                cout<<"Enter Team ID: ";
                cin>>tid;
                system.teamReturning(tid);
                break;
            case 5:
                system.manageRoads();
                break;
            case 6:
                system.viewVictims();
                break;
            case 7:
                system.viewTeams();
                break;
            case 8:
                system.viewMap();
                break;
            case 9:
                system.viewLogs();
                break;
            case 10:
                cout<<"Exiting Simulation. Stay Safe!"<<endl;
                return 0;
            default:
                cout<<"Invalid Choice!"<<endl;
        }
        cout<<"\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    return 0;
}