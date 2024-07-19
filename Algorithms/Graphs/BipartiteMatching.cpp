bool _findMatch(ll i, vb &visited, v &match, vv &graph)
{
    for (ll x : graph[i])
    {
        if (!visited[x])
        {
            visited[x] = true;
            if (match[x] == -1 || _findMatch(match[x],visited,match,graph))
            {
                match[x] = i;
                return true;
            }
        }
    }
    return false;
}

pair<v, v> _splitBipartite(vv &graph)
{
    ll n = graph.size();
    v coloring(n, -1);
    for (ll i = 0; i < n; i++)
    {
        if (coloring[i] != -1) continue;
        stack<p> dfs;
        dfs.emplace(i, 0);
        while (!dfs.empty())
        {
            auto top = dfs.top();
            dfs.pop();
            if (coloring[top.f] != -1) continue;
            coloring[top.f] = top.s;
            for (ll x : graph[top.f]) dfs.emplace(x, 1 - top.s);
        }
    }
    vv res(2);
    for (ll i = 0; i < n; i++) res[coloring[i]].pb(i);
    return {res[0], res[1]};
}

vp maximumMatching(vv &graph, v group1 = v(), v group2 = v())
{
    if (group1.size() == 0)
    {
        auto groups = _splitBipartite(graph);
        group1 = groups.f;
        group2 = groups.s;
    }
    ll n = graph.size();
    v match(n, -1);
    for (ll x : group1)
    {
        vb visited(n, false);
        _findMatch(x, visited,match,graph);
    }
    vp edges;
    for (ll x : group2) if (match[x] != -1) edges.eb(match[x], x);
    return edges;
}
