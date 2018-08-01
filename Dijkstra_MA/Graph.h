#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <queue>
#include <functional>

#include "Vertex.h"
using namespace std;
class Graph
{
	unordered_map<int, Vertex> _vertices;

public:

	void addVertex(Vertex vertex)
	{
		_vertices[vertex.getId()] = vertex;
	}

	//MA #12 TODO: IMPLEMENT!
	unordered_map<Vertex, int> computeShortestPath(Vertex *start)
	{
		if (start != nullptr)
		{
			//holds known distances
			unordered_map<Vertex, int> distances;

			//set the distance equal to infinity
			for (const std::pair<int, Vertex>& pair : _vertices)
			{
				//set the size of the int
				distances[pair.second] = INT_MAX;
			}
			//underlying heap
			priority_queue<Vertex, vector<Vertex>, PathWeightComparer> dijkstra_queue{};
			
			//reset start's path weight
			start->setPathWeight(0);
			distances[*start] = 0;
			//push on starting vertex
			dijkstra_queue.push(*start);
			//while queue not empty
			while (!dijkstra_queue.empty())
			{
				//Top of heap not known (in distances)?
				Vertex size = dijkstra_queue.top();
				//pop to remove it from queue
				dijkstra_queue.pop();
				//push on outgoing edges
				std::unordered_map<Vertex *, int>& vertices = size.getEdges();
				//iterator
				std::unordered_map<Vertex *, int>::iterator adjacentVertices;
				//loop through all edges
				for (adjacentVertices = vertices.begin(); adjacentVertices != vertices.end(); ++adjacentVertices)
				{
					Vertex* adjacentVertex = adjacentVertices->first;
					int weight = adjacentVertices->second;
					//calculate the path weight
					int pathWeight = size.getPathWeight() + weight;
					//updating path weight
					if (distances[*adjacentVertex] > pathWeight)
					{
						adjacentVertex->setPathWeight(pathWeight);
						//update the distances
						distances[*adjacentVertex] = pathWeight;
						dijkstra_queue.push(*adjacentVertex);
					}
				}
			}
			return distances;
		}
	}
};

#endif
