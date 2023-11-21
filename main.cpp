#include <iostream>
#include <vector>
#include <algorithm>
#include "Graph.h"

int main() {
	Graph<int> gr;
	gr.AddVertex(10);
	gr.AddVertex(13);
	gr.AddVertex(15);
	gr.AddVertex(9);
	gr.AddVertex(14);
	gr.AddVertex(20);
	gr.AddVertex(19);
	gr.AddEdge(10, 15);
	gr.AddEdge(10, 19);
	gr.AddEdge(13, 15);
	gr.AddEdge(14, 13);
	auto it = gr.BeginVertex();
	std::for_each(it, gr.EndVertex(), [](auto& p)
		{
			std::cout << p.GetKey() << " ";
		});
	return 0;
}
