#include "netflow.hpp"
#include <vector>
#include <stack>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <limits.h>

#define TOO_FEW_VERTICES "Too few vertices."
#define TOO_FEW_EDGES "Too few edges."
#define EDGE_WEIGHT_ZERO "Detected edge weight of 0."
#define EDGE_BAD_ENDPOINT "Edge interacts with nonexistent vertex."
#define SELF_LOOP "At least one self-loop."
#define MULTI_EDGES "Detected multi-edges."
#define NOT_ONE_SRC "Zero or more than one source."
#define NOT_ONE_SINK "Zero or more than one sink."


bool DFS(std::vector<std::vector<Edge>> residual, std::vector<std::vector<Edge>> backwardEdge, unsigned source, unsigned sink, unsigned numVertices, std::vector<unsigned>& path, unsigned& bottleneck)
{
    bool discovered[numVertices];
    memset(discovered, false, sizeof(discovered));

    discovered[source] = true;
    std::stack<unsigned> q;
    unsigned curr_node = source;
    bool notFound = true;
    bool notNeighbor = false;

    /*
    for(unsigned i = 0; i < curr_node.size(); i++)
            std::cout << "from: " << curr_node[i].from << "to: " << curr_node[i].to << "weight: " << curr_node[i].weight << std::endl;
    */
    
    q.push( curr_node );


    while(!q.empty())
    {
        curr_node = q.top();
        /*
        for(unsigned i = 0; i < curr_node.size(); i++)
            std::cout << "from: " << curr_node[i].from << " to: " << curr_node[i].to << " weight: " << curr_node[i].weight << std::endl;
        

        std::cout << "curr node : " << curr_node << std::endl;

        if(path.size() > 0)
            std::cout << "last path elmnt: " << path[path.size()-1] << "\n";
        
        */

        q.pop();

        notFound = true;
        if(path.size() < 1)
        {
            notFound = false;
            path.push_back(curr_node);
        }else
        {
            for(unsigned i = 0; i < residual[path[path.size()-1]].size(); i++)
            {
                if(curr_node == residual[path[path.size()-1]][i].to && residual[path[path.size()-1]][i].weight > 0)
                {
                    notFound = false;
                    bottleneck = std::min(bottleneck, residual[path[path.size()-1]][i].weight);
                    //std::cout << "bottleneck(1) : " << bottleneck << std::endl;
                    path.push_back(curr_node);
                }
            }

            for(unsigned i = 0; i < backwardEdge[path[path.size()-1]].size(); i++)
            {
                if(curr_node == backwardEdge[path[path.size()-1]][i].to && backwardEdge[path[path.size()-1]][i].weight > 0)
                {
                    notFound = false;
                    bottleneck = std::min(bottleneck, backwardEdge[path[path.size()-1]][i].weight);
                    //std::cout << "bottleneck(2) : " << bottleneck << std::endl;
                    path.push_back(curr_node);
                }
            }
        }

        if(path.size() > 0)
        {
            while(curr_node != path[path.size()-1])
            {
                notNeighbor = true;

                if(q.size() > 0) 
                {
                    curr_node = q.top();
                    q.pop();
                }

noUpdate:

                for(unsigned i = 0; i < residual[path[path.size()-1]].size(); i++)
                {
                    if(curr_node == residual[path[path.size()-1]][i].to)
                    {
                        notNeighbor = false;
                        if(residual[path[path.size()-1]][i].weight > 0)
                        {
                            notFound = false;
                            bottleneck = std::min(bottleneck, residual[path[path.size()-1]][i].weight);
                            //std::cout << "bottleneck(1) : " << bottleneck << std::endl;
                            path.push_back(curr_node);
                        }
                    }
                }
    
                for(unsigned i = 0; i < backwardEdge[path[path.size()-1]].size(); i++)
                {
                    if(curr_node == backwardEdge[path[path.size()-1]][i].to)
                    {
                        notNeighbor = false;
                        if(backwardEdge[path[path.size()-1]][i].weight > 0)
                        {
                            notFound = false;
                            bottleneck = std::min(bottleneck, backwardEdge[path[path.size()-1]][i].weight);
                            //std::cout << "bottleneck(1) : " << bottleneck << std::endl;
                            path.push_back(curr_node);
                        }
                    }
                }

                if(notNeighbor)
                {
                    path.pop_back();
                    goto noUpdate;
                }

            }
        }

        if(notFound)
            continue;

        notFound = true;

        /*
        std::cout << "curr node : " << curr_node << std::endl;

        if(path.size() > 0)
            std::cout << "last path elmnt: " << path[path.size()-1] << "\n";

        for(unsigned i = 0; i < path.size(); i++)
            std::cout << path[i] << std::endl;
        std::cout << std::endl;

        */

        for(unsigned i = 0; i < residual[curr_node].size(); i++)  
        {
            if(discovered[residual[curr_node][i].to] == false && residual[curr_node][i].weight > 0)
            {
                notFound = false;
                if(residual[path[path.size()-1]][i].to == sink)
                {
                    bottleneck = std::min(bottleneck, residual[curr_node][i].weight);
                    //std::cout << "bottleneck(3) : " << bottleneck << std::endl;                   
                    path.push_back(sink);
                    return true;
                }

                discovered[residual[curr_node][i].to] = true;
                q.push(residual[curr_node][i].to);
            }
        } 

        for(unsigned i = 0; i < backwardEdge[curr_node].size(); i++)  
        {
            if(discovered[backwardEdge[curr_node][i].to] == false && backwardEdge[curr_node][i].weight > 0)
            {
                notFound = false;
                if(backwardEdge[path[path.size()-1]][i].to == sink)
                {
                    bottleneck = std::min(bottleneck, backwardEdge[curr_node][i].weight);
                    //std::cout << "bottleneck(4) : " << bottleneck << std::endl;
                    path.push_back(sink);
                    return true;
                }
                discovered[backwardEdge[curr_node][i].to] = true;
                q.push(backwardEdge[curr_node][i].to);
            }
        }

        if(notFound)
            path.pop_back(); 
    }

    return false;
}


std::vector<Edge> solveNetworkFlow(
    const std::vector<Edge>& flowNetwork,
    unsigned numVertices)
{

    if(numVertices < 2) //1
        throw std::runtime_error(TOO_FEW_VERTICES);

    if(flowNetwork.empty()) //2
        throw std::runtime_error(TOO_FEW_EDGES);

    bool sourceArr[numVertices];
    bool sinkArr[numVertices];
    memset(sourceArr, true, sizeof(sourceArr));
    memset(sinkArr, true, sizeof(sinkArr)); 

    std::vector<Edge> maxFlow;

    std::vector<std::vector<Edge>> residual;
    std::vector<std::vector<Edge>> backwardEdge;
    residual.resize(numVertices);
    backwardEdge.resize(numVertices);
    unsigned temp;

    for(unsigned i = 0; i < flowNetwork.size(); i++)
    {
        if(flowNetwork[i].weight == 0)  //3
            throw std::runtime_error(EDGE_WEIGHT_ZERO);
        else if(flowNetwork[i].from >= numVertices || flowNetwork[i].to >= numVertices) //4
            throw std::runtime_error(EDGE_BAD_ENDPOINT);
        else if(flowNetwork[i].from == flowNetwork[i].to)   //5
            throw std::runtime_error(SELF_LOOP);


        for(unsigned j = 0; j < residual[flowNetwork[i].from].size(); j++)
        {
            if(residual[flowNetwork[i].from][j].to == flowNetwork[i].to)
                throw std::runtime_error(MULTI_EDGES);
        }
        residual[flowNetwork[i].from].push_back( flowNetwork[i] );


        backwardEdge[flowNetwork[i].to].push_back( flowNetwork[i] );
        backwardEdge[flowNetwork[i].to][ backwardEdge[flowNetwork[i].to].size()-1 ].weight = 0;

        temp = backwardEdge[flowNetwork[i].to][ backwardEdge[flowNetwork[i].to].size()-1 ].to;
        backwardEdge[flowNetwork[i].to][ backwardEdge[flowNetwork[i].to].size()-1 ].to = backwardEdge[flowNetwork[i].to][ backwardEdge[flowNetwork[i].to].size()-1 ].from;
        backwardEdge[flowNetwork[i].to][ backwardEdge[flowNetwork[i].to].size()-1 ].from = temp;
            

       
        maxFlow.push_back( flowNetwork[i] );
        maxFlow[i].weight = 0;


        sourceArr[flowNetwork[i].to] = false;
        sinkArr[flowNetwork[i].from] = false;
    }

    unsigned numSource = 0;
    unsigned numSink = 0;
    unsigned source;
    unsigned sink;

    for(unsigned i = 0; i < numVertices; i++)
    {
        if(sourceArr[i] == true)
        {
            numSource++;
            source = i;
        }

        if(sinkArr[i] == true)
        {
            numSink++;
            sink = i;
        }
    }

    if(numSource == 0 || numSource > 1) //7
        throw std::runtime_error(NOT_ONE_SRC);

    if(numSink == 0 || numSink > 1) //8
        throw std::runtime_error(NOT_ONE_SINK); 


    //choose augmenting path
    std::vector<unsigned> path;
    unsigned bottleneck = UINT_MAX;


    while( DFS(residual, backwardEdge, source, sink, numVertices, path, bottleneck) ) 
    {   
        /*
        std::cout << "PATH\n";
        for(unsigned i = 0; i < path.size(); i++)
        {
            std::cout << path[i] << std::endl;
        }

        std::cout << "\nBottleneck: " << bottleneck << std::endl;
        
        */

        //update maxFlow, residual, backward edges
        for(unsigned i = 0; i < path.size()-1; i++)
        {
            for(unsigned j = 0; j < residual[path[i]].size(); j++)
            {
                if(residual[path[i]][j].from == path[i] && residual[path[i]][j].to == path[i+1])
                {
                    residual[path[i]][j].weight -= bottleneck;
                    for(unsigned l = 0; l < backwardEdge[residual[path[i]][j].to].size(); l++)
                    {
                        if(residual[path[i]][j].to == backwardEdge[residual[path[i]][j].to][l].from && residual[path[i]][j].from == backwardEdge[residual[path[i]][j].to][l].to)
                            backwardEdge[residual[path[i]][j].to][l].weight += bottleneck;
                    }

                    for(unsigned k = 0; k < maxFlow.size(); k++)
                    {
                        if(maxFlow[k].from == residual[path[i]][j].from && maxFlow[k].to == residual[path[i]][j].to)
                        {
                            maxFlow[k].weight += bottleneck;
                            break;
                        }
                    }

                break;
                }  
            }

            for(unsigned j = 0; j < backwardEdge[path[i]].size(); j++)
            {
                if(backwardEdge[path[i]][j].from == path[i] && backwardEdge[path[i]][j].to == path[i+1])
                {
                    for(unsigned l = 0; l < residual[backwardEdge[path[i]][j].to].size(); l++)
                    {
                        if(backwardEdge[path[i]][j].to == residual[backwardEdge[path[i]][j].to][l].from && backwardEdge[path[i]][j].from == residual[backwardEdge[path[i]][j].to][l].to )
                            residual[backwardEdge[path[i]][j].to][l].weight += backwardEdge[path[i]][j].weight;
                    }

                    for(unsigned k = 0; k < maxFlow.size(); k++)
                    {
                        if(maxFlow[k].from == backwardEdge[path[i]][j].to && maxFlow[k].to == backwardEdge[path[i]][j].from)
                        {
                            maxFlow[k].weight -= backwardEdge[path[i]][j].weight;
                            break;
                        }
                    }

                    backwardEdge[path[i]][j].weight = 0;
                }  
            }
        }

        path.clear();

        
        /*
        std::cout << "RESIDUAL\n";
        for(unsigned i = 0; i < residual.size(); i++)
        {
            for(unsigned j = 0; j < residual[i].size(); j++)
            {
                std::cout << "From: " << residual[i][j].from << " To: " << residual[i][j].to << " Weight: " << residual[i][j].weight << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;


        std::cout << "BACKWARD EDGE\n";
        for(unsigned i = 0; i < backwardEdge.size(); i++)
        {
            for(unsigned j = 0; j < backwardEdge[i].size(); j++)
            {
                std::cout << "From: " << backwardEdge[i][j].from << " To: " << backwardEdge[i][j].to << " Weight: " << backwardEdge[i][j].weight << std::endl;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        

        std::cout << "MAXFLOW\n";

        for(unsigned i = 0; i < maxFlow.size(); i++)
            std::cout << "From: " << maxFlow[i].from << " To: " << maxFlow[i].to << " Weight: " << maxFlow[i].weight << std::endl;

        std::cout << std::endl;
        */
        
    }
    return maxFlow;
}


void assignCourses(
    std::vector<Instructor>& instructors,
    const std::vector<std::string>& courses)
{
    
    std::vector<Edge> graph;

    //instructor id on graph = position in instructor vector + 1
    //course if on graph = position in course vector + instructor.size() + 1

    for(unsigned i = 0; i < instructors.size(); i++)
    {
        graph.push_back( {0, i+1, (unsigned)instructors[i].maxCourses} );
        for(unsigned j = 0; j < instructors[i].preferences.size(); j++)
        {
            for(unsigned k = 0; k < courses.size(); k++)
            {
                if(instructors[i].preferences[j] == courses[k])
                    graph.push_back( {i+1, (unsigned)instructors.size() + k + 1, 1} );
            }
        }
    }

    for(unsigned i = 0; i < courses.size(); i++)
        graph.push_back( {(unsigned)instructors.size() + i + 1, (unsigned)instructors.size() + (unsigned)courses.size() + 1, 1 });

    
    /*
    for(unsigned i = 0; i < graph.size(); i++)
        std::cout << "From: " << graph[i].from << " To: " << graph[i].to << " Weight: " << graph[i].weight << std::endl; 
    */
    

    graph = solveNetworkFlow(graph, instructors.size() + courses.size() + 2);

    for(unsigned k = 0; k < graph.size(); k++)
    {
        for(unsigned i = 0; i < instructors.size(); i++)        
        {
            for(unsigned j = 0; j < courses.size(); j++)
            {

                if(graph[k].weight > 0)
                {
                    if(graph[k].from == i + 1)
                    {
                        if(graph[k].to == (unsigned)instructors.size() + j + 1)
                        {
                            instructors[i].assignedCourses.push_back(courses[j]);
                            break;
                        }
                    }
                }
            }
        }
    }

    /*
    unsigned numAssigned = 0;

    for (const Instructor& ins : instructors)
        numAssigned += ins.assignedCourses.size();

    std::cout << numAssigned << std::endl;

    for(unsigned i = 0; i < graph.size(); i++)
        std::cout << "From: " << graph[i].from << " To: " << graph[i].to << " Weight: " << graph[i].weight << std::endl; 
    */
}

























