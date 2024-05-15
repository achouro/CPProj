// ------------------------------------------------------------------//
// Djikstra algorith implementation                                  //
// @author Ivan                                                      //
// @date 17.3.2024                                                   //
// ------------------------------------------------------------------//

#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <limits>

#define ENABLE_DEBUG false

using std::cerr;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::priority_queue;
using std::set;
using std::vector;
using std::stack;
using std::string;

// Custom exceptions
class BaseException { };
class InvalidProbabilityException : public BaseException {};
class InvalidMetricRangeException : public BaseException {};

/**
 * Utility class.
 */ 
class CustomUtils {
    public:

        /**
         * Gets random double value from defined range.
         * 
         * @param from Start range.
         * @param to End range.
         * @return Random number from defined range.
         */ 
        static double getRand(double from, double to) {
            return ((double)rand() / RAND_MAX) * (to - from) + from;
        }

        /**
         * Prints specified number of spaces.
         * 
         * @param len Number of spaces.
         */
        static void printSpaces(unsigned int len) {
            for(unsigned int i = 0; i < len; i++) {
                cout << " ";
            }
        }
};

/**
 * Class representing graph connection with defined metric.
 */ 
class GraphEdge {
    public:
        GraphEdge(bool valid)
        {
            this->valid = valid;
            this->metric = 0;
        }

        GraphEdge(double metric = 0)
        {
            this->valid = true;
            this->metric = metric;
        }

        void setMetric(double metric)
        {
            this->metric = metric;
        }

        double getMetric()
        {
            return this->metric;
        }

        void setValid(bool valid)
        {
            this->valid = valid;
        }

        bool isValid()
        {
            return this->valid;
        }

        /**
         * Creates valid vertex with random metric from defined range.
         * 
         * @param from Start range.
         * @param to End range.
         * @return Valid vertex.
         */
        static GraphEdge *createRandomVertex(double from, double to)
        {
            return new GraphEdge(CustomUtils::getRand(from, to));
        }

        /**
         * Creates invalid vertex.
         * 
         * @return Invalid vertex.
         */
        static GraphEdge *createInvalidVertex()
        {
            return new GraphEdge(false);
        }

    private: 
        double metric;
        bool valid;
};

template <class V>
class Graph
{
    public:
        Graph(unsigned int size)
        {
            this->size = size;
        }

        ~Graph()
        {
            for (unsigned int i = 0; i < size; i++)
            {
                for (unsigned int j = 0; j < size; j++)
                {
                    delete p_edges[i][j];
                }
            }
        }

        /**
         * Initializes Graph based on provided properties.
         * 
         * @param connProb Probability with which the connection is created.
         * @param metricFrom Starting range for metric generation.
         * @param metricTo Ending range for metric generation.
         */
        void initialize(double connProb, double metricFrom, double metricTo)
        {
            // validation
            if (connProb < 0 || connProb > 1)
            {
                throw new InvalidProbabilityException();
            }

            if(metricFrom > metricTo)
            {
                throw new InvalidMetricRangeException();
            }

            createConnectionMatrix();
            clearConnectionMatrix();
            initializeConnections(connProb, metricFrom, metricTo);
        }

        /**
         * Returns set of neighbors associated with node id.
         * 
         * @param nodeId Node id for which we want its neighbors.
         * @return Set of neighbors.
         */ 
        set<unsigned int> getNeighbors(unsigned int nodeId)
        {
            set<unsigned int> result;
            for (unsigned int i = 0; i < this->size; i++)
            {
                if(i == nodeId) {
                    continue;
                }

                if (this->p_edges[nodeId][i]->isValid())
                {
                    result.insert(i);
                }
            }

            return result;
        }

        /**
         * Returns edge associated with defined node ids.
         * 
         * @param fromNodeId Source node id.
         * @param toNodeId Destination node id.
         * @return Edge associated with node ids.
         */ 
        GraphEdge *getEdge(unsigned int fromNodeId, unsigned int toNodeId)
        {
            if (fromNodeId >= this->size || toNodeId >= this->size || fromNodeId == toNodeId)
            {
                return nullptr;
            }

            GraphEdge *p_edge = this->p_edges[fromNodeId][toNodeId];
            if(!p_edge->isValid()){
                return nullptr;
            }

            return p_edge;
        }

        /**
         * Returns all nodes.
         */ 
        set<unsigned int> getAllNodes()
        {
            set<unsigned int> allNodes;
            for (unsigned int i = 0; i < this->size; i++) {
                allNodes.insert(i);
            }
            return allNodes;
        }

        /**
         * Prints Graph matric with generated transition metrics.
         */
        void printGraph()
        {
            cout << "\t";
            for (unsigned int i = 0; i < size; i++)
            {
                cout << "<" << i << ">\t";
            }
            cout << endl;
            for (unsigned int i = 0; i < size; i++)
            {
                cout << "<" << i << ">\t";
                for (unsigned int j = 0; j < size; j++)
                {
                    if (i == j)
                    {
                        cout << "X" << "\t";
                        continue;
                    }

                    GraphEdge *p_edge = p_edges[i][j];
                    if (p_edge == nullptr || !p_edge->isValid())
                    {
                        cout << "X" << "\t";
                        continue;
                    }

                    cout << p_edge->getMetric() << "\t";
                }
                cout << endl;
            }
            cout << endl;
        }

        /**
         * Getter for graph size.
         * 
         * @return Size of graph.
         */ 
        unsigned int getSize()
        {
            return this->size;
        }

    private:

        /**
        * Creates empty 2D array for GraphVertices.
        */
        void createConnectionMatrix()
        {
            p_edges = new GraphEdge **[size];
            for (unsigned int i = 0; i < size; i++)
                p_edges[i] = new GraphEdge *[size];
        }

        /**
        * Creates empty 2D array for GraphVertices.
        */ 
        void clearConnectionMatrix() 
        {
            for (unsigned int i = 0; i < size; i++)
            {
                for (unsigned int j = 0; j < size; j++)
                    p_edges[i][j] = nullptr;
            }
        }

        /**
         * Initializes connections. Creates connection based on defined probability and metric value based on
         * defined rande.
         * 
         * @param connProb Connection probability.
         * 
         */
        void initializeConnections(double connProb, double metricFrom, double metricTo)
        {
            for (unsigned int i = 0; i < size; i++)
            {
                for (unsigned int j = 0; j < size; j++)
                {
                    if (i == j)
                        continue;

                    if (p_edges[i][j] != nullptr)
                        continue;

                    if (CustomUtils::getRand(0, 1) < connProb)
                        p_edges[i][j] = p_edges[j][i] = GraphEdge::createRandomVertex(metricFrom, metricTo);
                    else
                        p_edges[i][j] = p_edges[j][i] = GraphEdge::createInvalidVertex();
                }
            }
        }
       
        GraphEdge ***p_edges;
        unsigned int size;
};

/**
 * Wrapper class to hold data for djikstras algorithm.
 */
class NodeShortestPreviousPair
{
    public:
        NodeShortestPreviousPair(unsigned int nodeId, double shortestDistance = 0, unsigned int previousNodeId = 0)
        {
            this->nodeId = nodeId;
            this->shortestDistance = shortestDistance;
            this->visited = false;
            this->previousNodeId = previousNodeId;
        }

        double getShortestDistance()
        {
            return this->shortestDistance;
        }

        void setShortestDistance(double shortestDistance)
        {
            this->shortestDistance = shortestDistance;
        }

        unsigned int getPreviousNode()
        {
            return this->previousNodeId;
        }

        void setPreviousNodeId(unsigned int previousNodeId)
        {
            this->previousNodeId = previousNodeId;
        }

        bool isVisited()
        {
            return this->visited;
        }

        void setVisited(bool visited){
            this->visited = visited;
        }

        unsigned int getNodeId()
        {
            return this->nodeId;
        }

    private:
        unsigned int nodeId;
        double shortestDistance;
        unsigned int previousNodeId;
        bool visited;
};

/**
 * Priority queue to sort neighboring edges based on path cost.
 */
class PriorityQueueComparator
{
    public:
        bool operator()(NodeShortestPreviousPair *p_edge1, NodeShortestPreviousPair *p_edge2)
        {
            return (p_edge1->getShortestDistance() > p_edge2->getShortestDistance());
        }
};

/**
 * Djikstras algorithm implementation class.
 */
class DjikstraCalculator {
    public:

        DjikstraCalculator(Graph<int> *p_graph)
        {
            this->p_graph = p_graph;
        }

        ~DjikstraCalculator()
        {
            for(NodeShortestPreviousPair *p_node : this->shortestDistance)
            {
                delete p_node;
            }
        }

        /**
         * Calculates shortest distance table for node specified as parameter.
         * 
         * @param sourceNodeId Source node id.
         * @return Sequence of node ids from source node to destination node.
         */ 
        void calculateBestPathTable(unsigned int sourceNodeId)
        {
            // Initialization
            set<unsigned int> unvisitedNodes = this->p_graph->getAllNodes();
            set<unsigned int> visitedNodes;

            this->sourceNodeId = sourceNodeId;
            this->shortestDistance = getInitialShortestDistanceTable(sourceNodeId);
            unsigned int deep = 0;
            calculateDistance(sourceNodeId, visitedNodes, unvisitedNodes, deep);

            // Print final table
            if(ENABLE_DEBUG)
                printTable();
        }

        /**
         * Returns shortest distance and returns sequence of nodes and distance as output parameter.
         * 
         * @param len Length of returned sequence of node ids (output parameter).
         * @param distance Distance to destination node.
         * @return Sequence of node ids from source node to destination node.
         */ 
        void getBestPath(unsigned int destinationNodeId, stack<unsigned int> &path)
        {
            unsigned int previousNodeId = this->shortestDistance.at(destinationNodeId)->getPreviousNode();
            path.push(previousNodeId);

            if(previousNodeId != this->sourceNodeId) {
                getBestPath(previousNodeId, path);
            }
        }

        /**
         * Returns distance from source node id to destination node id.
         * 
         * @param destinationNodeId Destination node id.
         * @return Distance from source node id to destination node id.
         */
        double getDistance(unsigned int destinationNodeId)
        {
            return this->shortestDistance.at(destinationNodeId)->getShortestDistance();
        }

        /**
         * Prints table of calculated shortest distances from defined source node id.
         */
        void printTable()
        {
            cout << endl;
            cout << "FINAL PATH TABLE FOR SOURCE NODE ID: " << this->sourceNodeId << endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++" << endl;
            for (unsigned int i = 0; i < this->shortestDistance.size(); i++) {
                NodeShortestPreviousPair *p_a = this->shortestDistance[i];
                cout << i << "\t" << p_a->isVisited() << "\t" << p_a->getPreviousNode() << "\t" << p_a->getShortestDistance() << "\t" << endl;
            }
        }

    private:

        vector<NodeShortestPreviousPair *> getInitialShortestDistanceTable(unsigned int sourceNodeId)
        {
            vector<NodeShortestPreviousPair *> shortestDistance;
            for (unsigned int i = 0; i < p_graph->getSize(); i++)
            {
                shortestDistance.push_back(new NodeShortestPreviousPair(i, (i == sourceNodeId) ? 0 : numeric_limits<double>::infinity(), 0));
            }
            return shortestDistance;
        }

        void calculateDistance(unsigned int sourceNodeId, set<unsigned int> &visitedNodes, set<unsigned int> &unvisitedNodes, unsigned int &deep)
        {
            if(ENABLE_DEBUG) {
                CustomUtils::printSpaces(deep);
                cout << "Entering node: " << sourceNodeId << endl;
            }

            NodeShortestPreviousPair *p_actualNode = shortestDistance.at(sourceNodeId);
            p_actualNode->setVisited(true);
            set<unsigned int> neighborNodes = this->p_graph->getNeighbors(sourceNodeId);
            priority_queue<NodeShortestPreviousPair *, vector<NodeShortestPreviousPair *>, PriorityQueueComparator> edgeQueue;
            double distance = p_actualNode->getShortestDistance();

            // Load neighboar edges to priority queue
            for (unsigned int const &neighborNodeId : neighborNodes)
            {
                GraphEdge *p_edge = this->p_graph->getEdge(sourceNodeId, neighborNodeId);

                NodeShortestPreviousPair *p_neighborActualDistance = this->shortestDistance.at(neighborNodeId);
                NodeShortestPreviousPair *p_neighborNewDistance = new NodeShortestPreviousPair(neighborNodeId, distance + p_edge->getMetric(), sourceNodeId);

                if (!p_neighborActualDistance->isVisited() || p_neighborActualDistance->getShortestDistance() > p_neighborNewDistance->getShortestDistance())
                {
                    p_neighborActualDistance->setPreviousNodeId(p_neighborNewDistance->getPreviousNode());
                    p_neighborActualDistance->setShortestDistance(p_neighborNewDistance->getShortestDistance());
                }
                if(ENABLE_DEBUG) {
                    CustomUtils::printSpaces(deep);
                    cout << "   Neighbor node: " << p_neighborNewDistance->getNodeId() << " added. Distance: " << p_neighborNewDistance->getShortestDistance() << endl;
                }
                edgeQueue.push(p_neighborNewDistance);
            }

            visitedNodes.insert(sourceNodeId);
            unvisitedNodes.erase(sourceNodeId);

            // Iterate neighbors
            while (!edgeQueue.empty())
            {
                NodeShortestPreviousPair *p_neighbor = edgeQueue.top();
                edgeQueue.pop();
                unsigned int neighborNodeId = p_neighbor->getNodeId();

                if(visitedNodes.find(neighborNodeId) != visitedNodes.end())
                    continue;

                deep++;
                calculateDistance(neighborNodeId, visitedNodes, unvisitedNodes, deep);

                if(unvisitedNodes.size() == 0) {
                    if(ENABLE_DEBUG) {
                        cout << "BREAK: No unvisited nodes!!!" << endl;
                    }
                    break;
                }
            }
        }

        vector<NodeShortestPreviousPair *> shortestDistance;
        Graph<int> *p_graph;
        unsigned int sourceNodeId;
};

int main(void)
{
    srand(time(NULL));

    unsigned int nodeCount = 50;

    Graph<int> *p_graph = new Graph<int>(nodeCount);
    unsigned int sourceNodeId = 1;
    unsigned int destinationNodeId = 2;
    double probabilities[3] = {0.2, 0.4, 0.5};

    for(unsigned int i = 0; i < 3; i++) {
        try{
            p_graph->initialize(probabilities[i], 1, 10);
        }catch(const InvalidMetricRangeException& e) {
            cerr << "Invalid metric range!";
        }catch(const InvalidProbabilityException& e) {
            cerr << "Invalid probability!";
        }

        if(ENABLE_DEBUG)
            p_graph->printGraph();

        DjikstraCalculator *p_djikstra_calc = new DjikstraCalculator(p_graph);
        p_djikstra_calc->calculateBestPathTable(sourceNodeId);

        double averageDistance = 0;
        double min = numeric_limits<double>::max();
        for(unsigned int j = 0; j < nodeCount; j++) {
            if(j == sourceNodeId) {
                continue;
            }
            double distance = p_djikstra_calc->getDistance(j);
            if(distance < min) {
                min = distance;
            }
            averageDistance += distance;
        }

        delete p_djikstra_calc;
        cout << "Average distance for probability " << probabilities[i] << " is " << averageDistance/(nodeCount - 1) << ", min is " << min << endl;
    }

    delete p_graph;
}
