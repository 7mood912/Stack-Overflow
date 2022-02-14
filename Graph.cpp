#include <iostream>
#include <vector>

class Edge
{
private:
    int destVertexID;
    int weight;
    Edge *next;

public:
    Edge() : destVertexID(-1), weight(-1), next(NULL) {}
    Edge(const Edge &E) : destVertexID(E.destVertexID), weight(E.weight), next(E.next) {}
    Edge(const int &destID, const int &w) : destVertexID(destID), weight(w), next(NULL) {}
    const Edge &operator=(const Edge &E)
    {
        const Edge &edge(E);
        return edge;
    }
    void set_destVertexID(const int &destID)
    {
        destVertexID = destID;
    }
    void set_Weight(const int &w)
    {
        weight = w;
    }
    void set_next(Edge *p)
    {
        next = p;
    }
    int get_Weight()
    {
        return weight;
    }
    int get_destVertexID()
    {
        return destVertexID;
    }
    Edge *get_next()
    {
        return next;
    }
};

class List
{
private:
    Edge *head;

public:
    List() : head(NULL) {}
    List(const List &L) : head(L.head) {}
    const List &operator=(const List &L)
    {
        const List &list(L);
        return L;
    }
    void InsertEdge(const int &destID, const int &weight)
    {
        Edge *newEdge = new Edge;
        newEdge->set_destVertexID(destID);
        newEdge->set_Weight(weight);
        newEdge->set_next(head);
        head = newEdge;
    }

    bool FindEdge(const int &destID)
    {
        if (head == NULL)
            return false;
        Edge *currEdge = head;
        while (currEdge != NULL)
        {
            if (currEdge->get_destVertexID() == destID)
                return true;
            currEdge = currEdge->get_next();
        }
        return false;
    }

    void DeleteEdge(const int &destID)
    {
        if (head == NULL)
            return;

        Edge *currEdge = head;
        Edge *prevEdge = NULL;
        while (currEdge != NULL)
        {
            if (currEdge->get_destVertexID() == destID)
                break;
            prevEdge = currEdge;
            currEdge = currEdge->get_next();
        }
        if (currEdge != NULL)
        {
            if (prevEdge == NULL)
            {
                head = currEdge->get_next();
                delete currEdge;
            }
            else
            {
                prevEdge->set_next(currEdge->get_next());
                delete currEdge;
            }
        }
    }

    void PrintEdgeList()
    {
        if (head == NULL)
        {
            std::cout << "[ ]\n";
            return;
        }
        Edge *currEdge = head;
        std::cout << "[";
        while (currEdge != NULL)
        {
            std::cout << currEdge->get_destVertexID() << "(" << currEdge->get_Weight() << ") --> ";
            currEdge = currEdge->get_next();
        }
        std::cout << "]\n";
    }
};

class Vertex
{
private:
    int stateID;
    std::string stateName;
    List edgeList;

public:
    Vertex() : stateID(-1), stateName("NULL") {}
    Vertex(const Vertex &V) : stateID(V.stateID), stateName(V.stateName), edgeList(V.edgeList) {}
    Vertex(const int &ID, const std::string &name) : stateID(ID), stateName(name) {}
    const Vertex &operator=(const Vertex &V)
    {
        const Vertex &vertex(V);
        return V;
    }

    void set_stateID(int ID)
    {
        stateID = ID;
    }

    void set_stateName(const std::string &name)
    {
        stateName = name;
    }

    int get_stateID()
    {
        return stateID;
    }

    std::string get_stateName()
    {
        return stateName;
    }

    List &get_edgeList()
    {
        return edgeList;
    }

    bool checkEdge(const int &destID)
    {
        return edgeList.FindEdge(destID);
    }

    void addEdge(const int &destID, const int &weight)
    {
        edgeList.InsertEdge(destID, weight);
    }
};

class Graph
{
private:
    std::vector<Vertex> vertices;

public:
    bool check_if_VertexExist(const int &ID)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_stateID() == ID)
                return true;
        }
        return false;
    }

    void InsertVertex(Vertex &newVertex)
    {
        bool check = check_if_VertexExist(newVertex.get_stateID());
        if (check == true)
        {
            std::cout << "\n-A vertex with ID(" << newVertex.get_stateID() << ") already exist!\n";
        }
        else
        {
            vertices.push_back(newVertex);
            std::cout << "\n-New vertex added successfully!\n";
        }
    }

    Vertex get_Vertex(const int &ID)
    {
        Vertex garbage;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_stateID() == ID)
                return vertices.at(i);
        }
        return garbage;
    }

    void deleteVertex(const int &ID)
    {
        int Index = -1;
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_stateID() == ID)
            {
                Index = i;
            }
            /* else
            {
                vertices.at(i).get_edgeList().DeleteEdge(ID);
            } */
        }
        if (Index == -1)
            std::cout << "\n-Error! Vertex DOES NOT exist!\n";

        else
        {
            vertices.erase(vertices.begin() + Index);
            std::cout << "-Vertex deleted successfully!\n";
        }
    }

    bool check_if_EdgeExist(const int &sourceID, const int &destID)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices.at(i).get_stateID() == sourceID)
            {
                bool check = vertices.at(i).checkEdge(destID);
                if (check == true)
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    void addEdge(const int &sourceID, const int &destID, const int &weight)
    {
        bool source_check = false, destination_check = false;
        bool edge_check = check_if_EdgeExist(sourceID, destID);
        Vertex source(get_Vertex(sourceID));
        Vertex dest(get_Vertex(destID));
        if (edge_check == true)
        {
            std::cout << "\n-Edge between " << source.get_stateName() << "(" << sourceID
                      << ") and " << dest.get_stateName() << "(" << destID << ") already exist!\n";
        }
        else if ((source.get_stateID() != -1) && (dest.get_stateID() != -1))
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                if (vertices.at(i).get_stateID() == sourceID)
                {
                    vertices.at(i).addEdge(destID, weight);
                    source_check = true;
                }
                else if (vertices.at(i).get_stateID() == destID)
                {
                    vertices.at(i).addEdge(sourceID, weight);
                    destination_check = true;
                }
                if (source_check == true && destination_check == true)
                {
                    std::cout << "\n-Edge between " << source.get_stateName() << "(" << sourceID
                              << ") and " << dest.get_stateName() << "(" << destID << ") is successfully added!\n";
                    break;
                }
            }
        }
        else
        {
            std::cout << "\n-Error! Vertex ID is invalid!\n";
        }
    }

    void deleteEdge(const int &sourceID, const int &destID)
    {
        bool check1, check2;
        check1 = check2 = check_if_EdgeExist(sourceID, destID);
        if (check1 == true)
        {
            for (int i = 0; i < vertices.size(); i++)
            {
                // List E(vertices.at(i).get_edgeList());
                if (vertices.at(i).get_stateID() == sourceID)
                {
                    vertices.at(i).get_edgeList().DeleteEdge(destID);
                    check1 = false;
                }
                else if (vertices.at(i).get_stateID() == destID)
                {
                    vertices.at(i).get_edgeList().DeleteEdge(sourceID);
                    check2 = false;
                }
                if (check1 == false && check2 == false)
                {
                    std::cout << "\n-Edge deleted successfully!\n";
                    break;
                }
            }
        }
        else
            std::cout << "\n-Error! The given edge DOES NOT exist!\n";
    }

    void PrintGraph()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            std::cout << vertices.at(i).get_stateName() << "(" << vertices.at(i).get_stateID() << "): ";
            vertices.at(i).get_edgeList().PrintEdgeList();
        }
    }
};

int main()
{
    using namespace std;
    Graph G;
    Vertex V;
    string stateName = "NULL";
    int sourceID = 0, destID = 0, Weight = 0, op_code = 0;
    bool check = false;
    do
    {
        cout << "What Operation Do You Want to Perform? "
             << " Select Option Number. Enter 0 to Exit.\n";
        cout << "1. Add Vertex\n";
        cout << "2. Delete Vertex\n";
        cout << "3. Add Edge\n";
        cout << "4. Delete Edge\n";
        cout << "5. Print Graph\n";
        cout << "0. Exit Program\n";

        cout << "\n-------------------------------\n";
        cout << "Your Choice: ";
        cin >> op_code;
        cout << "-------------------------------\n";
        switch (op_code)
        {
        case 0:
            break;
        case 1:
            cout << "ADD VERTEX OPERATION -\n";
            cout << "Enter State Name: ";
            cin >> stateName;
            cout << "Enter Vertex(State) ID: ";
            cin >> sourceID;
            V.set_stateName(stateName);
            V.set_stateID(sourceID);
            G.InsertVertex(V);
            break;
        case 2:
            cout << "DELETE VERTEX OPERATION -\n";
            cout << "Enter Vertex(State) ID: ";
            cin >> sourceID;
            G.deleteVertex(sourceID);
            break;
        case 3:
            cout << "ADD EDGE OPERATION -\n";
            cout << "Enter Source Vertex(State) ID: ";
            cin >> sourceID;
            cout << "Enter Destination Vertex(State) ID: ";
            cin >> destID;
            cout << "Enter Weight of Edge: ";
            cin >> Weight;
            G.addEdge(sourceID, destID, Weight);
            break;
        case 4:
            cout << "DELETE EDGE OPERATION -\n";
            cout << "Enter Source Vertex(State) ID: ";
            cin >> sourceID;
            cout << "Enter Destination Vertex(State) ID: ";
            cin >> destID;
            G.deleteEdge(sourceID, destID);
            break;
        case 5:
            cout << "PRINT GRAPH OPERATION -\n";
            G.PrintGraph();
            break;
        default:
            cout << "Error! Enter Proper Option Number!\n";
            break;
        }
        cout << "\n\n\n";

    } while (op_code != 0);
    return 0;
}
