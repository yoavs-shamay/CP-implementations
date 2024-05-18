v dijkstra(vvp &graph, ll initial)
{
    ll N = graph.size();
    v distances(N, INF);
    distances[initial] = 0;
    priority_queue<p, vp, greater<p>> pq;
    pq.emplace(0, initial);
    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        if (distances[top.second] < INF) continue;
        distances[top.second] = top.first;
        for (auto neighbor : graph[top.second])
        {
            pq.emplace(top.first + neighbor.second, neighbor.first);
        }
    }
    return distances;
}