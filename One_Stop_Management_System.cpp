#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>

#define threshold 10
using namespace std;

class ticketNode
{
public:
    int ticketId;                         // Unique ID for each ticket
    string customerName;                   
    int priority;                          
    string serviceRequestDescription;      
    time_t creationTime;                   // Time when the ticket was created
    string status;                         // Current status of the ticket ("open" or "assigned/closed")
    time_t ticketCloseTime;                // Time when the ticket was closed (if applicable)
    static int count;                      // Static counter for generating unique ticket IDs
    ticketNode *next;                      

    
    ticketNode()
    {
        ticketId = ++count;
        customerName = " ";
        priority = 0;
        serviceRequestDescription = " ";
        creationTime = time(0);
        status = "open";
        next = NULL;
    }

    ticketNode(string name, int p, string srd)
    {
        ticketId = ++count;
        customerName = name;
        priority = p;
        serviceRequestDescription = srd;
        creationTime = time(0);
        status = "open";
        next = NULL;
    }
};
int ticketNode::count = 0;  // Initialize static ticket counter


class ticketLinkedList
{

public:
    ticketNode *head, *tail;
    vector<ticketNode> ticketQueue;

    ticketLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    void addTicket()
    {
        string name, srd;
        int p;
        cout << "\nEnter the customer name: ";
        getline(cin, name);
        cout << "Enter the priority(1,2 or 3): ";
        cin >> p;
        cin.ignore();
        cout << "Enter the service request description: ";
        getline(cin, srd);
        ticketNode *n = new ticketNode(name, p, srd);
        if (head == NULL)
        {
            head = n;
            tail = n;
        }
        else
        {
            tail->next = n;
            tail = n;
        }
    }

    void removeTicket(int id)
    {
        ticketNode *temp = head;
        if (head == NULL)
        {
            cout << "No tickets to remove" << endl;
        }
        else
        {
            if (temp->ticketId == id)
            {
                head = head->next;
                delete temp;
                cout << "Ticket removed" << endl;
            }
            else
            {
                int flag = 0;
                while (temp->next != NULL)
                {
                    if (temp->next->ticketId == id)
                    {
                        ticketNode *temp2 = temp->next;
                        temp->next = temp->next->next;
                        delete temp2;
                        cout << "Ticket removed" << endl;
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }
                if (flag == 0)
                {
                    cout << "Ticket not found, thus cannot remove ticket" << endl;
                }
            }
        }
    }

    /*Returning those tickets whose status is open*/
    vector<ticketNode> getOpenTickets()
    {
        vector<ticketNode> openTickets;
        ticketNode *temp = head;
        while (temp != NULL)
        {
            if (temp->status == "open")
            {
                openTickets.push_back(*temp);
            }
            temp = temp->next;
        }
        return openTickets;
    }

    /*Display function for open tickets
      which is to be used in reporting an analytics in main menu*/
    void displayOpenTickets()
    {
        if (head == NULL)
        {
            cout << "\nNo tickets to display" << endl;
            return;
        }
        vector<ticketNode> openTickets = getOpenTickets();
        int n = openTickets.size();
        bubbleSort(openTickets);
        for (int i = 0; i < n; i++)
        {
            cout << "\nTicket ID: " << openTickets[i].ticketId << endl;
            cout << "Customer Name: " << openTickets[i].customerName << endl;
            cout << "Priority: " << openTickets[i].priority << endl;
            cout << "Service Request Description: " << openTickets[i].serviceRequestDescription << endl;
            cout << "Creation Time: " << ctime(&openTickets[i].creationTime);
            cout << "Status: " << openTickets[i].status << endl;
            cout << endl;
        }
        cout << "\nAll Open Tickets displayed after sorting! " << endl;
    }

    /*After this there are 5 functions for sorting and 2 for searching
      They will be implemented on user choice in sort and search functions*/
    void bubbleSort(vector<ticketNode> &tickets)
    {
        int n = tickets.size();
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (tickets[j + 1].priority < tickets[j].priority)
                {
                    swap(tickets[j + 1], tickets[j]);
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }
    }

    void selectionSort(vector<ticketNode> &tickets)
    {
        int n = tickets.size();
        for (int i = 0; i < n; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (tickets[j].priority < tickets[minIndex].priority)
                {
                    minIndex = j;
                }
            }
            swap(tickets[i], tickets[minIndex]);
        }
    }

    void insertionSort(vector<ticketNode> &tickets)
    {
        int n = tickets.size();
        for (int i = 1; i < n; i++)
        {
            ticketNode key = tickets[i];
            int j = i - 1;
            while (j >= 0 && tickets[j].priority > key.priority)
            {
                tickets[j + 1] = tickets[j];
                j--;
            }
            tickets[j + 1] = key;
        }
    }

    void mergeSort(vector<ticketNode> &tickets)
    {
        int n = tickets.size();
        if (n <= 1)
        {
            return;
        }
        int mid = tickets.size() / 2;
        vector<ticketNode> leftArr(mid);
        vector<ticketNode> rightArr(n - mid);
        int j = 0;
        for (int i = 0; i < n; i++)
        {
            if (i < mid)
            {
                leftArr[i] = tickets[i];
            }
            else
            {
                rightArr[j] = tickets[i];
                j++;
            }
        }
        mergeSort(leftArr);
        mergeSort(rightArr);
        merge(tickets, leftArr, rightArr);
    }

    void merge(vector<ticketNode> &tickets, vector<ticketNode> &leftArr, vector<ticketNode> &rightArr)
    {
        int leftSize = leftArr.size();
        int rightSize = rightArr.size();
        int i = 0, l = 0, r = 0;

        while (l < leftSize && r < rightSize)
        {
            if (leftArr[l].priority < rightArr[r].priority)
            {
                tickets[i] = leftArr[l];
                l++;
                i++;
            }
            else
            {
                tickets[i] = rightArr[r];
                i++;
                r++;
            }
        }
        while (l < leftSize)
        {
            tickets[i] = leftArr[l];
            i++;
            l++;
        }
        while (r < rightSize)
        {
            tickets[i] = rightArr[r];
            i++;
            r++;
        }
    }

    void quickSort(vector<ticketNode> &tickets, int low, int high)
    {
        if (low >= high)
        {
            return;
        }
        else
        {
            int pivot = partition(tickets, low, high);
            quickSort(tickets, low, pivot - 1);
            quickSort(tickets, pivot + 1, high);
        }
    }

    int partition(vector<ticketNode> &tickets, int low, int high)
    {
        int pivot = tickets[high].priority;
        int i = low - 1;

        for (int j = low; j < high; j++)
        {
            if (tickets[j].priority < pivot)
            {
                i++;
                swap(tickets[i], tickets[j]);
            }
        }
        i++;
        swap(tickets[i], tickets[high]);
        return i;
    }

    void binarySearch(vector<ticketNode> &tickets, int low, int high, int id)
    {
        if (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (tickets[mid].ticketId == id)
            {
                cout << "\nTicket found! " << endl;
                cout << "Ticket ID: " << tickets[mid].ticketId << endl;
                cout << "Customer Name: " << tickets[mid].customerName << endl;
                cout << "Priority: " << tickets[mid].priority << endl;
                cout << "Service Request Description: " << tickets[mid].serviceRequestDescription << endl;
                cout << endl;
            }
            else if (tickets[mid].ticketId < id)
            {
                binarySearch(tickets, mid + 1, high, id);
            }
            else
            {
                binarySearch(tickets, low, mid - 1, id);
            }
        }
        else
        {
            cout << "Ticket not found! " << endl;
        }
    }

    void interpolationSearch(vector<ticketNode> &tickets, int id)
    {
        int n = tickets.size();
        int low = 0, high = n - 1;

        // Ensure the tickets are sorted by ticketId
        if (n == 0 || tickets[low].ticketId > id || tickets[high].ticketId < id)
        {
            cout << "Ticket not found!" << endl;
            return;
        }

        while (low <= high && id >= tickets[low].ticketId && id <= tickets[high].ticketId)
        {
            // Prevent division by zero and ensure valid position
            if (tickets[high].ticketId == tickets[low].ticketId)
            {
                if (tickets[low].ticketId == id)
                {
                    cout << "\nTicket found! " << endl;
                    cout << "Ticket ID: " << tickets[low].ticketId << endl;
                    cout << "Customer Name: " << tickets[low].customerName << endl;
                    cout << "Priority: " << tickets[low].priority << endl;
                    cout << "Service Request Description: " << tickets[low].serviceRequestDescription << endl;
                    cout << endl;
                    return;
                }
                break; // Exit if no match found
            }

            // Calculate the position
            int pos = low + static_cast<int>((static_cast<double>(high - low) / (tickets[high].ticketId - tickets[low].ticketId)) * (id - tickets[low].ticketId));

            // Ensure pos is within bounds
            if (pos < low || pos > high)
            {
                break;
            }

            if (tickets[pos].ticketId == id)
            {
                cout << "\nTicket found! " << endl;
                cout << "Ticket ID: " << tickets[pos].ticketId << endl;
                cout << "Customer Name: " << tickets[pos].customerName << endl;
                cout << "Priority: " << tickets[pos].priority << endl;
                cout << "Service Request Description: " << tickets[pos].serviceRequestDescription << endl;
                cout << endl;
                return;
            }
            else if (tickets[pos].ticketId < id)
            {
                low = pos + 1;
            }
            else
            {
                high = pos - 1;
            }
        }

        cout << "Ticket not found!" << endl; // Feedback if ticket isn't found
    }

    /*This search function will take user choice for search and then search ticket based on choice
       It will also display the time complexities for the algorithms*/
    void searchTicket(string searchType, int id)
    {
        vector<ticketNode> tickets = getOpenTickets();
        int n = tickets.size();
        if (n == 0)
        {
            cout << "No tickets to search! " << endl;
            return;
        }
        if (searchType == "binary")
        {
            binarySearch(tickets, 0, n - 1, id);
            cout << "\nTicket searched using Binary Search which has time complexity as follows: " << endl;
            cout << "Best Case: O(1) " << endl;
            cout << "Average Case: O(log n) " << endl;
            cout << "Worst Case: O(log n) " << endl;
        }
        else if (searchType == "interpolation")
        {
            interpolationSearch(tickets, id);
            cout << "\nTicket searched using Interpolation Search which has time complexity as follows: " << endl;
            cout << "Best Case: O(1) " << endl;
            cout << "Average Case: O(log log n) " << endl;
            cout << "Worst Case: O(n) " << endl;
        }
        else
        {
            cout << "Invalid search type! " << endl;
        }
    }

    /*This sort function will take user choice for sort and then sort tickets based on choice
       and then display the sorted tickets.
       It will also display the time complexities for the algorithms*/
    void sortTickets(string sortType)
    {
        vector<ticketNode> tickets = getOpenTickets();
        if (tickets.size() == 0)
        {
            cout << "No tickets to sort! " << endl;
            return;
        }
        if (sortType == "bubble")
        {
            bubbleSort(tickets);
            cout << "\nTickets sorted using Bubble Sort which has time complexity as follows: " << endl;
            cout << "Best Case: O(n) " << endl;
            cout << "Average Case: O(n^2) " << endl;
            cout << "Worst Case: O(n^2) " << endl;
        }
        else if (sortType == "selection")
        {
            selectionSort(tickets);
            cout << "\nTickets sorted using Selection Sort which has time complexity as follows: " << endl;
            cout << "Best Case: O(n^2) " << endl;
            cout << "Average Case: O(n^2) " << endl;
            cout << "Worst Case: O(n^2) " << endl;
        }
        else if (sortType == "insertion")
        {
            insertionSort(tickets);
            cout << "\nTickets sorted using Insertion Sort which has time complexity as follows: " << endl;
            cout << "Best Case: O(n) " << endl;
            cout << "Average Case: O(n^2) " << endl;
            cout << "Worst Case: O(n^2) " << endl;
        }
        else if (sortType == "merge")
        {
            mergeSort(tickets);
            cout << "\nTickets sorted using Merge Sort which has time complexity as follows: " << endl;
            cout << "Best Case: O(n log n) " << endl;
            cout << "Average Case: O(n log n) " << endl;
            cout << "Worst Case: O(n log n) " << endl;
        }
        else if (sortType == "quick")
        {
            quickSort(tickets, 0, tickets.size() - 1);
            cout << "\nTickets sorted using Quick Sort which has time complexity as follows: " << endl;
            cout << "Best Case: O(n log n) " << endl;
            cout << "Average Case: O(n log n) " << endl;
            cout << "Worst Case: O(n^2) " << endl;
        }
        else
        {
            cout << "Invalid sort type! " << endl;
        }
        for (int i = 0; i < tickets.size(); i++)
        {
            cout << "\nTicket ID: " << tickets[i].ticketId << endl;
            cout << "Customer Name: " << tickets[i].customerName << endl;
            cout << "Priority: " << tickets[i].priority << endl;
            cout << "Service Request Description: " << tickets[i].serviceRequestDescription << endl;
            cout << "Creation Time: " << ctime(&tickets[i].creationTime);
            cout << "Status: " << tickets[i].status << endl;
            cout << endl;
        }
    }

    /*This function retrieves a vector of open tickets from the linked list.
     It first clears any existing tickets in the ticketQueue, then traverses
     the linked list starting from the head. For each ticket that is marked as "open",
     it adds that ticket to the ticketQueue . After collecting all open tickets,
     it sorts them by priority. Finally, it returns the sorted vector of open tickets. 
     So this will work just like a QUEUE as it will return the tickets in FIFO order */
    vector<ticketNode> &getTicketQueue()
    {
        ticketQueue.clear(); // Clear the queue first

        ticketNode *temp = head;
        while (temp != NULL)
        {
            if (temp->status == "open")
            {
                ticketQueue.push_back(*temp);
            }
            temp = temp->next;
        }

        int n = ticketQueue.size();
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (ticketQueue[j + 1].priority < ticketQueue[j].priority)
                {
                    swap(ticketQueue[j + 1], ticketQueue[j]);
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }
        return ticketQueue;
    }

    void markTicketAsAssigned(int ticketId)
    {
        ticketNode *temp = head;
        while (temp != NULL)
        {
            if (temp->ticketId == ticketId)
            {
                temp->status = "assigned";
                return;
            }
            temp = temp->next;
        }
    }
};

class agent
{

public:
    int agentId;
    string name;
    vector<ticketNode> assignedTickets;
    bool available;
    static int count;

    agent(string n)
    {
        agentId = ++count;
        name = n;
        available = true;
    }
};
int agent::count = 0;

class agentManager
{

public:
    vector<agent> agents;
    vector<ticketNode> resolutionLogStack; // This is a Stack to store resolved tickets in LIFO order

    void addAgent()
    {
        string name;
        cout << "Enter the agent's name: ";
        getline(cin, name);
        agent *a = new agent(name);
        agents.push_back(*a);
    }

    /* Assigns open tickets to available agents in a round-robin manner so that a single ticket can be assigned to an agent
     at a time .
     Retrieves open tickets; exits if none are available or if there are no agents.
     Agents are sorted based on the number of currently assigned tickets, 
     ensuring those with fewer assigned tickets are prioritized. 
     The function iterates through open tickets, assigning them to available agents 
     until all tickets are assigned or agents reach their maximum of 5 tickets.
     If all agents are maxed out, it notifies about unassigned tickets. */
    void assignOpenTickets(ticketLinkedList &t)
    {
        vector<ticketNode> &openTickets = t.getTicketQueue();

        if (openTickets.empty())
        {
            cout << "No open tickets to assign!" << endl;
            return;
        }
        if (agents.empty())
        {
            cout << "No agents to assign tickets to!" << endl;
            return;
        }

        // Sort agents based on the number of tickets they currently have assigned
        int n = agents.size();
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (agents[j + 1].assignedTickets.size() < agents[j].assignedTickets.size())
                {
                    swap(agents[j + 1], agents[j]);
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }

        int size = openTickets.size();
        int j = 0;
        for (int i = 0; i < size; /* increment inside loop */)
        {
            // Check if there are available agents
            bool allMaxedOut = true;
            for (int k = 0; k < agents.size(); k++)
            {
                if (agents[k].available)
                {
                    allMaxedOut = false;
                    break;
                }
            }
            if (allMaxedOut)
            {
                cout << "All agents have reached the maximum number of tickets assigned!" << endl;
                cout << "Tickets left unassigned: " << size - i << endl;
                break;
            }

            // Assign tickets only if the agent is available
            if (agents[j].available)
            {
                agents[j].assignedTickets.push_back(openTickets[i]);
                cout << "Ticket ID: " << openTickets[i].ticketId << " assigned to Agent " << agents[j].name << endl;

                // Mark ticket as assigned and remove it from openTickets
                t.markTicketAsAssigned(openTickets[i].ticketId); // Mark as assigned in the linked list
                openTickets.erase(openTickets.begin() + i);
                size--; // Decrease size as we've removed an item

                // Check if agent reached max ticket limit
                if (agents[j].assignedTickets.size() == 5)
                {
                    agents[j].available = false;
                    cout << "Agent " << agents[j].name << " has reached the maximum number of tickets assigned!" << endl;
                }
            }
            else
            {
                i++; // Only increment if agent couldn't take the ticket
            }

            // Rotate to the next agent
            j = (j + 1) % n;
        }
    }

    /* Resolves a ticket by ID, marking it as closed and updating the agent's status.
     Searches through assigned tickets of each agent; if found, it updates the ticket's 
     status to "closed", logs the resolution, removes the ticket from the agent's list, 
     and removes it from the ticket list. If the ticket is not found, it notifies the user.*/
    void resolveTicket(int id, ticketLinkedList &t)
    {
        int n = agents.size();
        for (int i = 0; i < n; i++)
        {
            int m = agents[i].assignedTickets.size();
            for (int j = 0; j < m; j++)
            {
                if (agents[i].assignedTickets[j].ticketId == id)
                {
                    agents[i].assignedTickets[j].status = "closed";
                    agents[i].assignedTickets[j].ticketCloseTime = time(0);
                    resolutionLogStack.push_back(agents[i].assignedTickets[j]);
                    agents[i].assignedTickets.erase(agents[i].assignedTickets.begin() + j);
                    agents[i].available = true;
                    cout << "Ticket resolved! " << endl;
                    t.removeTicket(id);
                    return;
                }
            }
        }
        cout << "Ticket not found! " << endl;
    }

    /* Displays information about agents, including their assigned tickets.
     First, it sorts agents by the number of tickets assigned (in ascending order).
     Then, it prints each agent's ID, name, and details of assigned tickets. 
     If an agent has no tickets, it indicates that as well. */
    void displayAgents()
    {
        int n = agents.size();
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - 1 - i; j++)
            {
                if (agents[j + 1].assignedTickets.size() < agents[j].assignedTickets.size())
                {
                    swap(agents[j + 1], agents[j]);
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }
        for (int i = 0; i < n; i++)
        {
            cout << "\nAgent ID: " << agents[i].agentId << endl;
            cout << "Agent Name: " << agents[i].name << endl;
            cout << "Tickets Assigned: " << endl
                 << endl;
            int m = agents[i].assignedTickets.size();
            if (m == 0)
            {
                cout << "No tickets assigned to this agent yet! " << endl;
            }
            else
            {
                for (int j = 0; j < m; j++)
                {
                    cout << "Ticket ID: " << agents[i].assignedTickets[j].ticketId << endl;
                    cout << "Customer Name: " << agents[i].assignedTickets[j].customerName << endl;
                    cout << "Priority: " << agents[i].assignedTickets[j].priority << endl;
                    cout << "Service Request Description: " << agents[i].assignedTickets[j].serviceRequestDescription << endl;
                    cout << "Creation Time: " << ctime(&agents[i].assignedTickets[j].creationTime);
                    cout << "Status: " << agents[i].assignedTickets[j].status << endl;
                    cout << endl;
                }
            }
        }
    }

    /* Displays the resolution log stack of tickets in LIFO order just as stack, showing details of resolved tickets.
     Like a stack, it iterates from the most recently resolved ticket to the oldest.
     So it will display the most recent resolved ticket first and then the oldest.
     If no tickets are resolved, it informs the user. Otherwise, it prints each ticket's
     ID, customer name, priority, service request description, creation time,
     status, and close time, iterating from the most recently resolved to the oldest. */
    void displayResolutionLog()
    {
        int n = resolutionLogStack.size();
        if (n == 0)
        {
            cout << "No tickets resolved yet! \nHence no tickets in resolution log Stack" << endl;
            return;
        }
        cout << "\nResolution Log Stack: " << endl;
        for (int i = n - 1; i >= 0; i--)
        {
            cout << "\nTicket ID: " << resolutionLogStack[i].ticketId << endl;
            cout << "Customer Name: " << resolutionLogStack[i].customerName << endl;
            cout << "Priority: " << resolutionLogStack[i].priority << endl;
            cout << "Service Request Description: " << resolutionLogStack[i].serviceRequestDescription << endl;
            cout << "Creation Time: " << ctime(&resolutionLogStack[i].creationTime);
            cout << "Status: " << resolutionLogStack[i].status << endl;
            cout << "Close Time: " << ctime(&resolutionLogStack[i].ticketCloseTime);
            cout << endl;
        }
    }
};

    /* Reads configuration settings from 'config.txt' to set default sorting and searching options.
     If the file cannot be opened, it prints an error message. It looks for specific lines in the
     file and extracts the corresponding values for default element sorting, advanced sorting,
     and searching based on the prefixes specified. */
void readConfig(string &defaultElemenSort, string &defaultAdvSort, string &defaultSearch)
{
    ifstream file("config.txt");
    if (!file)
    {
        cerr << "Unable to open config file!" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.find("DefaultElemenSort:") != string::npos)
        {
            defaultElemenSort = line.substr(line.find(":") + 2);
        }
        else if (line.find("DefaultAdvSort:") != string::npos)
        {
            defaultAdvSort = line.substr(line.find(":") + 2);
        }
        else if (line.find("DefaultSearching:") != string::npos)
        {
            defaultSearch = line.substr(line.find(":") + 2);
        }
    }

    file.close();
}

int main()
{

    cout << "23K-2018 Syed Faiez Mehboob" << endl;
    cout << "\nWelcome to the One Stop Management System! " << endl;

    ticketLinkedList ticketSystem;
    agentManager agentSystem;
    string defaultElemenSort, defaultAdvSort, defaultSearch;

    /* Default sorting and searching options for tickets if not specified in the config file or if the file cannot be opened
       They are used as a fallback if the config file is not found or if the settings are not specified. 
       So that there's no runtime error etc  */
    defaultElemenSort = "bubble";
    defaultAdvSort = "merge";
    defaultSearch = "binary";
    // Read configuration settings
    readConfig(defaultElemenSort, defaultAdvSort, defaultSearch);

    int Mchoice;
    do
    {
        cout << "\n------Main Menu------\n";
        cout << "1. Ticket Management\n";
        cout << "2. Agent Management\n";
        cout << "3. Report And Analytics\n";
        cout << "0. Exit System\n";
        cout << "Enter Your Choice: ";
        cin >> Mchoice;
        cin.ignore();
        switch (Mchoice)
        {
        case 1:
        { // Ticket Management
            int choice;
            cout << "\n1. Add Ticket\n";
            cout << "2. Remove Ticket\n";
            cout << "3. Search Ticket\n";
            cout << "4. Sort Tickets\n";
            cout << "Enter Your Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                ticketSystem.addTicket();
                cout << "\nTicket added! " << endl;
                break;
            case 2:
            {
                int id;
                cout << "Enter Ticket ID to remove: ";
                cin >> id;
                ticketSystem.removeTicket(id);
                break;
            }
            case 3:
            {
                int id;
                string searchType;
                cout << "Type the Name of search algorithm you want to use: \n(binary, interpolation, default): ";
                getline(cin, searchType);
                cout << "Enter Ticket ID to search: ";
                cin >> id;
                if (searchType == "default")
                {
                    searchType = defaultSearch;
                }
                ticketSystem.searchTicket(searchType, id);
                break;
            }
            case 4:
            {
                /* Here I am taking user choice for sorting and then sorting tickets based on choice
                   If user typed default then use default methods taken from config file but check 
                   if tickets to be sorted are under threshold then use default elementary sort other advanced */
                string sortType;
                cout << "Type the name of Sorting algorithm you want to use: \n(bubble, selection, insertion, merge, quick, default): ";
                cin >> sortType;
                if (sortType == "default")
                {
                    if (ticketSystem.getOpenTickets().size() < threshold)
                        sortType = defaultElemenSort;
                    else
                        sortType = defaultAdvSort;
                }
                ticketSystem.sortTickets(sortType);
                cout << "\nTickets sorted by Priority!" << endl;
                break;
            }
            default:
                cout << "Invalid choice! Returning to main menu.\n";
                break;
            }
            break;
        }

        case 2:
        { // Agent Management
            int choice;
            cout << "\n1. Add Agent\n";
            cout << "2. Assign Tickets to Agents\n";
            cout << "3. Resolve Ticket\n";
            cout << "Enter Your Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                agentSystem.addAgent();
                cout << "\nAgent added! " << endl;
                break;
            case 2:
                cout << "\n";
                agentSystem.assignOpenTickets(ticketSystem);
                cout << "\nTickets have been assigned to agents according to their priority! " << endl;
                break;
            case 3:
            {
                int id;
                cout << "Enter Ticket ID to resolve: ";
                cin >> id;
                agentSystem.resolveTicket(id, ticketSystem);
                break;
            }
            default:
                cout << "Invalid choice! Returning to main menu.\n";
                break;
            }
            break;
        }

        case 3:
        { // Report And Analytics
            int choice;
            cout << "\n1. Display Resolution Logs\n";
            cout << "2. Display Agents\n";
            cout << "3. Display Open Tickets\n";
            cout << "Enter Your Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                agentSystem.displayResolutionLog();
                break;
            case 2:
                agentSystem.displayAgents();
                break;
            case 3:
                ticketSystem.displayOpenTickets();
                break;
            default:
                cout << "Invalid choice! Returning to main menu.\n";
                break;
            }
            break;
        }

        case 0:
            cout << "Exiting system. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice! Please select a valid option.\n";
        }
    } while (Mchoice != 0);

    return 0;
}
